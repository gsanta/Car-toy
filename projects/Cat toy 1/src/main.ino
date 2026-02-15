#include <Arduino.h>

#include "../../lib/input/joystick/joystick_updater.h"
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter_manager.h"
#include "../../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"
#include "../../lib/motors/stepper_motor/stepper_motor_radio_controller.h"
#include "../../lib/motion/belt/belt_driver.h"

TimerControl timerControl;

const uint8_t STEP_PIN_MOTOR_1 = 2;
const uint8_t DIR_PIN_MOTOR_1 = 3;
const uint8_t STEP_PIN_MOTOR_2 = 4;
const uint8_t DIR_PIN_MOTOR_2 = 5;
const uint8_t CHIP_ENABLE_PIN = 7;
const uint8_t CHIP_SELECT_NOT_PIN = 8;

const uint8_t LIMIT_SWITCH_PIN_1 = A2;
const uint8_t LIMIT_SWITCH_PIN_2 = A3;
const uint8_t LIMIT_SWITCH_PIN_3 = A4;
const uint8_t LIMIT_SWITCH_PIN_4 = A5;


MotorDriverA4988 motor(STEP_PIN_MOTOR_1, DIR_PIN_MOTOR_1);
MotorDriverA4988 motor2(STEP_PIN_MOTOR_2, DIR_PIN_MOTOR_2);

BeltDriver belt(LIMIT_SWITCH_PIN_1, LIMIT_SWITCH_PIN_2, timerControl, motor);
BeltDriver belt2(LIMIT_SWITCH_PIN_3, LIMIT_SWITCH_PIN_4, timerControl, motor2);

StepperMotorRadioController stepperMotorRadioController1(motor, CONTROL_X);
StepperMotorRadioController stepperMotorRadioController2(motor2, CONTROL_Y);

const byte address[6] = "00001";
RF24RadioTransmitterManager radioTransmitter(CHIP_ENABLE_PIN, CHIP_SELECT_NOT_PIN, address, timerControl);

void setup() {
  Serial.begin(9600);
  
  radioTransmitter.setup(true);
  radioTransmitter.addCommandHandler(&stepperMotorRadioController1);
  radioTransmitter.addCommandHandler(&stepperMotorRadioController2);
}

void loop() {
  timerControl.loop();
}
