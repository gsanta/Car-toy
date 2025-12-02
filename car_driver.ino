// #include <Adafruit_MotorShield.h>
// #include "remote_control.h"
// #include "motor_driver.h"
// #include "motor_command_handler.h"
// #include "adafruit_dc_motor.h"

// Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// AdafruitDCMotor leftMotor(1, &AFMS);
// AdafruitDCMotor rightMotor(2, &AFMS);

// MotorDriver driver;

// MotorCommandHandler motorHandler(driver);


// RemoteControl remote(11);

// void setup() {
//   remote.setup_remote_control();
//   remote.add_command_handler(&motorHandler);
//   driver.setMotor(0, &leftMotor);
//   driver.setMotor(1, &rightMotor);
//   driver.setup();
// }

// void loop() {
//   remote.receive_remote_control_signal();
//   // receive_remote_control_signal(manager);
//   // driver.run(FORWARD);
//   // delay(1000);
//   // driver.run(BACKWARD);
//   // delay(1000);
// }

#include "remote_control.h"
#include "motor_driver_a4988.h"
#include "timer_control.h"
#include "stepper_command_handler.h"

MotorDriverA4988 driver(3, 2);

TimerControl timerControl;

RemoteControl remote(11);

StepperCommandHandler stepperHandler(driver);

void setup() {
  Serial.begin(9600);

  delay(2000);
  driver.setDirection(UP); // Set initial direction
  timerControl.add_microsecond_handler(&driver, 1000); // 1000 microseconds = 1 millisecond
  remote.setup_remote_control();
  remote.add_command_handler(&stepperHandler);
  driver.start();
//   remote.add_command_handler(&motorHandler);
//   driver.setMotor(0, &leftMotor);
//   driver.setMotor(1, &rightMotor);
//   driver.setup();
}

void loop() {
  timerControl.loop();  
  // remote.receive_remote_control_signal();
  // receive_remote_control_signal(manager);
  // driver.handleTimerEvent();
  // delayMicroseconds(1000);
  // driver.run(BACKWARD);
  // delay(1000);
}
