#include <Arduino.h>
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter_manager.h"
#include "../../lib/motors/stepper_motor/stepper_motor_radio_controller.h"
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/input/joystick/joystick_updater.h"
#include "joystick_command_director.h"

// Motor 1 pins (X axis)
constexpr uint8_t MOTOR_X_STEP_PIN = 5;
constexpr uint8_t MOTOR_X_DIR_PIN = 4;

// Motor 2 pins (Y axis)
constexpr uint8_t MOTOR_Y_STEP_PIN = 3;
constexpr uint8_t MOTOR_Y_DIR_PIN = 2;

// Joystick pins (only used in joystick control mode, see setup())
constexpr uint8_t JOYSTICK_X_PIN = A5;
constexpr uint8_t JOYSTICK_Y_PIN = A6;
constexpr uint8_t JOYSTICK_BUTTON_PIN = 7;
constexpr bool JOYSTICK_DEBUG = false;

// Global objects
TimerControl timerControl;
MotorDriverA4988 motorX(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
MotorDriverA4988 motorY(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);
StepperMotorTimerAdapter motorXAdapter(motorX);
StepperMotorTimerAdapter motorYAdapter(motorY);

// Radio transmitter (receiver) setup
const byte address[5] = {0x30, 0x30, 0x30, 0x30, 0x31};
RF24RadioTransmitterManager radioTransmitter(8, 9, address, timerControl, true);

StepperMotorRadioController stepperMotorRadioController1(motorX, CONTROL_X);
StepperMotorRadioController stepperMotorRadioController2(motorY, CONTROL_Y);

// Joystick control setup (alternative to radio control)
Joystick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, JOYSTICK_BUTTON_PIN, JOYSTICK_DEBUG);
JoystickUpdater joystickUpdater(joystick, timerControl);
JoystickCommandDirector joystickCommandDirector(joystick, motorX, motorY, timerControl);

void setupRadioControl() {
  radioTransmitter.setup(true);
  radioTransmitter.addCommandHandler(&stepperMotorRadioController1);
  radioTransmitter.addCommandHandler(&stepperMotorRadioController2);
  if (radioTransmitter.getRadioTransmitter().isReady()) {
    Serial.println("Radio control initialized");
  } else {
    Serial.println("Radio control unavailable: RF24 initialization failed");
  }
}

void setupJoystickControl() {
  joystick.setup();
  joystickUpdater.setup();
  joystickCommandDirector.setup();
  Serial.println("Joystick control initialized");
}

void setup() {
  Serial.begin(9600);
  Serial.print("CPU Frequency: ");
  Serial.println(F_CPU);
  Serial.println("Box2 - Motor Control!");

  motorX.setIsRunning(false);
  motorY.setIsRunning(false);
  timerControl.add_microsecond_handler(&motorXAdapter);
  timerControl.add_microsecond_handler(&motorYAdapter);

  // Uncomment ONE of the following two lines to choose the control mode.
  setupRadioControl();
  // setupJoystickControl();
}

void loop() {
  timerControl.loop();
}

