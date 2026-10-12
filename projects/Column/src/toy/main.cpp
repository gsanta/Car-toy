#include <Arduino.h>

#include "../../lib/system/timer/timer_control.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter_manager.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../../lib/motors/stepper_motor/stepper_motor_radio_controller.h"
#include "../../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"

// Motor 1 pins (X axis)
constexpr uint8_t MOTOR_X_STEP_PIN = 3;
constexpr uint8_t MOTOR_X_DIR_PIN = 2;

// Motor 2 pins (Y axis)
constexpr uint8_t MOTOR_Y_STEP_PIN = 5;
constexpr uint8_t MOTOR_Y_DIR_PIN = 4;

// Radio pins
constexpr uint8_t RADIO_CE_PIN = 8;
constexpr uint8_t RADIO_CSN_PIN = 9;
constexpr bool RADIO_DEBUG = true;

// Global objects
TimerControl timerControl;
MotorDriverA4988 motorX(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
MotorDriverA4988 motorY(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);
StepperMotorTimerAdapter motorXAdapter(motorX);
StepperMotorTimerAdapter motorYAdapter(motorY);

// Radio transmitter (receiver) setup
const byte radioAddress[5] = {0x30, 0x30, 0x30, 0x30, 0x31};
RF24RadioTransmitterManager radioTransmitter(RADIO_CE_PIN, RADIO_CSN_PIN, radioAddress, timerControl, RADIO_DEBUG);

StepperMotorRadioController stepperMotorRadioControllerX(motorX, CONTROL_X);
StepperMotorRadioController stepperMotorRadioControllerY(motorY, CONTROL_Y);

void setupRadioControl() {
  radioTransmitter.setup(true);
  radioTransmitter.addCommandHandler(&stepperMotorRadioControllerX);
  radioTransmitter.addCommandHandler(&stepperMotorRadioControllerY);
  if (radioTransmitter.getRadioTransmitter().isReady()) {
    Serial.println("Radio control initialized");
  } else {
    Serial.println("Radio control unavailable: RF24 initialization failed");
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Column - Motor Control!");

  motorX.setIsRunning(false);
  motorY.setIsRunning(false);
  timerControl.add_microsecond_handler(&motorXAdapter);
  timerControl.add_microsecond_handler(&motorYAdapter);

  setupRadioControl();
}

void loop() {
  timerControl.loop();
}
