#include <Arduino.h>
#include "../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"
#include "../lib/motors/stepper_motor/stepper_command_handler.h"
#include "../lib/system/timer/timer_control.h"
#include "../lib/input/remote_control/remote_control.h"

// Define motor pins
#define STEP_PIN 2
#define DIR_PIN 3

// Create motor instance
MotorDriverA4988 motor(STEP_PIN, DIR_PIN);

TimerControl timerControl;

RemoteControl remote(11);

StepperMotorTimerAdapter motorTimerAdapter(&motor);

StepperCommandHandler stepperCommandHandler(motor);

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  delay(2000);
  timerControl.add_microsecond_handler(&motorTimerAdapter, 1000);
  remote.setup_remote_control();
  remote.add_command_handler(&stepperCommandHandler);

  
  // Motor is initialized by constructor
  Serial.println("Motor initialized");
}

void loop() {
  // Add your main code here, to run repeatedly
  remote.receive_remote_control_signal();
}
