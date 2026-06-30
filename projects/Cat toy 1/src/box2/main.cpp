#include <Arduino.h>
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter_manager.h"
#include "../../lib/motors/stepper_motor/stepper_motor_radio_controller.h"

// Motor 1 pins (X axis)
constexpr uint8_t MOTOR_X_STEP_PIN = 4;
constexpr uint8_t MOTOR_X_DIR_PIN = 5;

// Motor 2 pins (Y axis)
constexpr uint8_t MOTOR_Y_STEP_PIN = 2;
constexpr uint8_t MOTOR_Y_DIR_PIN = 3;

// Global objects
TimerControl timerControl;
MotorDriverA4988 motorX(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
MotorDriverA4988 motorY(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);
StepperMotorTimerAdapter motorXAdapter(motorX);
StepperMotorTimerAdapter motorYAdapter(motorY);

// Radio transmitter (receiver) setup
const byte address[5] = {0x30, 0x30, 0x30, 0x30, 0x31};
RF24RadioTransmitterManager radioTransmitter(8, 9, address, timerControl);

StepperMotorRadioController stepperMotorRadioController1(motorX, CONTROL_X);
StepperMotorRadioController stepperMotorRadioController2(motorY, CONTROL_Y);


void setup() {
  Serial.begin(9600);
  Serial.print("CPU Frequency: ");
  Serial.println(F_CPU);
  Serial.println("Box2 - Radio Motor Control!");

  motorX.setIsRunning(false);
  motorY.setIsRunning(false);
  timerControl.add_microsecond_handler(&motorXAdapter);
  timerControl.add_microsecond_handler(&motorYAdapter);
  
  // Initialize radio receiver
  const bool radioOk = radioTransmitter.setup(true);
  if (!radioOk) {
    Serial.println("Radio receiver failed to initialize");
    return;
  }

  radioTransmitter.addCommandHandler(&stepperMotorRadioController1);
  radioTransmitter.addCommandHandler(&stepperMotorRadioController2);
  Serial.println("Radio receiver initialized");
}

void loop() {
  timerControl.loop();
}
