#include <Arduino.h>
#include "../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"
#include "../lib/motors/stepper_motor/stepper_command_handler.h"
#include "../lib/system/timer/timer_control.h"
#include "../lib/input/remote_control/remote_control.h"
#include "../lib/input/remote_control/remote_control_timer_adapter.h"
#include "../lib/input/limit_switch/belt_limiter.h"
#include "../lib/input/limit_switch/limit_reached_command.h"
#include "../lib/input/limit_switch/belt_limiter_timer_adapter.h"

// Define motor pins
#define STEP_PIN 2
#define DIR_PIN 3

const int LEFT_LIMIT = 4;
const int RIGHT_LIMIT = 5;

// Create motor instance
MotorDriverA4988 motor(STEP_PIN, DIR_PIN);

TimerControl timerControl;

RemoteControl remote(11);

StepperMotorTimerAdapter motorTimerAdapter(&motor);

StepperCommandHandler stepperCommandHandler(motor);

BeltLimiter beltLimiter(LEFT_LIMIT, RIGHT_LIMIT);

class StopMotorCommand : public LimitReachedCommand {
public:
  void execute(LimitSide side) override {
    motorTimerAdapter.stop();
  }
};

StopMotorCommand stopMotorCommand;

BeltLimiterTimerAdapter beltLimiterTimerAdapter(beltLimiter, stopMotorCommand);
RemoteControlTimerAdapter remoteControlTimerAdapter(remote);

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  delay(2000);
  timerControl.add_microsecond_handler(&motorTimerAdapter, 1000);
  timerControl.add_millisecond_handler(&beltLimiterTimerAdapter, 100);
  timerControl.add_millisecond_handler(&remoteControlTimerAdapter, 20);
  remote.setup_remote_control();
  remote.add_command_handler(&stepperCommandHandler);

  motorTimerAdapter.start();

  motor.setDirection(1); // Set initial direction

  // motor.rotate();

  beltLimiter.setup();

  
  // Motor is initialized by constructor
  Serial.println("Motor initialized");
}

void loop() {
  // Add your main code here, to run repeatedly
  timerControl.loop();
}
