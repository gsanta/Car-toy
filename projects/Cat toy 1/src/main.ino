#include <Arduino.h>
#include "../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"
#include "../lib/motors/stepper_motor/stepper_command_handler.h"
#include "../lib/system/timer/timer_control.h"
#include "../lib/input/remote_control/remote_control.h"
#include "../lib/motion/belt/belt_driver.h"
#include "../lib/motion/belt/belt_remote_controller.h"
#include "../lib/input/joystick/joystick_wrapper.h"

// Define motor pins
#define STEP_PIN 2
#define DIR_PIN 3

const int LEFT_LIMIT = 4;
const int RIGHT_LIMIT = 5;

// Create motor instance
MotorDriverA4988 motor(STEP_PIN, DIR_PIN);

TimerControl timerControl;

RemoteControl remote(11, timerControl);

JoystickWrapper joystick(A0, A1, 7, timerControl);

BeltDriver beltDriver(LEFT_LIMIT, RIGHT_LIMIT, timerControl, motor);

BeltRemoteController beltRemoteController(beltDriver, remote);

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  delay(2000);
  remote.setup_remote_control();

  Serial.println("Motor initialized");
}

void loop() {
  // Add your main code here, to run repeatedly
  timerControl.loop();
}
