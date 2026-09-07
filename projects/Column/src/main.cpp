#include <Arduino.h>

#include "../../lib/system/timer/timer_control.h"
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/input/joystick/joystick_updater.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"

// Motor pins (Stepper)
constexpr uint8_t MOTOR_STEP_PIN = 2;
constexpr uint8_t MOTOR_DIR_PIN = 3;

// Joystick pins
constexpr uint8_t JOYSTICK_X_PIN = A5;
constexpr uint8_t JOYSTICK_Y_PIN = A6;
constexpr uint8_t JOYSTICK_BUTTON_PIN = 7;

// Joystick dead zone threshold
constexpr int JOYSTICK_THRESHOLD = 150;

// Global objects
TimerControl timerControl;
Joystick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, JOYSTICK_BUTTON_PIN);
JoystickUpdater joystickUpdater(joystick, timerControl);
MotorDriverA4988 motor(MOTOR_STEP_PIN, MOTOR_DIR_PIN);
StepperMotorTimerAdapter motorAdapter(motor);

// Motor controller that reads joystick X and controls motor direction
class JoystickMotorController : public TimerHandler {
public:
  JoystickMotorController(Joystick& joystick, MotorDriverA4988& motor, TimerControl& timerControl)
    : TimerHandler(50), joystick(joystick), motor(motor), timerControl(timerControl),
      joystickCenter(0) {}

  void setup() {
    // Calculate center from joystick's calibration
    joystickCenter = (joystick.getXMin() + joystick.getXMax()) / 2;
    Serial.print("Joystick X center: ");
    Serial.println(joystickCenter);
    timerControl.add_millisecond_handler(this);
  }

  void handleTimerEvent() override {
    int xVal = joystick.getXVal();
    
    // Debug output
    Serial.print("X: ");
    Serial.print(xVal);
    Serial.print(" | Center: ");
    Serial.print(joystickCenter);
    Serial.print(" | Range: ");
    Serial.print(joystickCenter - JOYSTICK_THRESHOLD);
    Serial.print("-");
    Serial.print(joystickCenter + JOYSTICK_THRESHOLD);
    
    // Check if joystick is near center (stop motor)
    if (xVal >= (joystickCenter - JOYSTICK_THRESHOLD) && 
        xVal <= (joystickCenter + JOYSTICK_THRESHOLD)) {
      motor.setIsRunning(false);
      Serial.println(" | STOPPED");
      return;
    }
    
    // Set direction based on X value
    if (xVal < joystickCenter) {
      // Negative X - move up
      motor.setDirection(UP);
      Serial.println(" | UP");
    } else {
      // Positive X - move down
      motor.setDirection(DOWN);
      Serial.println(" | DOWN");
    }
    
    // Turn on motor with constant speed
    motor.setIsRunning(true);
    motor.setSpeed(1); // Constant speed
  }

private:
  Joystick& joystick;
  MotorDriverA4988& motor;
  TimerControl& timerControl;
  int joystickCenter;
};

JoystickMotorController joystickMotorController(joystick, motor, timerControl);

void setup() {
  Serial.begin(9600);
  Serial.println("Column - Joystick Motor Control!");
  Serial.println("Move joystick X to control stepper motor direction");
  
  joystickUpdater.setup();
  joystickMotorController.setup();
  
  // Add motor timer adapter to handle step pulses
  timerControl.add_microsecond_handler(&motorAdapter);
  
  motor.setIsRunning(false);
  Serial.println("Setup complete");
}

void loop() {
  timerControl.loop();
}
