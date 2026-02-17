#include <Arduino.h>

#include "../../lib/input/joystick/joystick_updater.h"
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "control_stepper_motor_with_radio.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter_manager.h"
#include "../../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"
#include "../../lib/motors/stepper_motor/stepper_motor_radio_controller.h"
#include "../../lib/motion/belt/belt_driver.h"

const uint8_t LIMIT_SWITCH_PIN_1 = A2;
const uint8_t LIMIT_SWITCH_PIN_2 = A3;
const uint8_t LIMIT_SWITCH_PIN_3 = A4;
const uint8_t LIMIT_SWITCH_PIN_4 = A5;

TimerControl timerControl;

MotorDriverA4988 motor(2, 3);
MotorDriverA4988 motor2(4, 5);
// StepperMotorTimerAdapter motorTimerAdapter(motor);
// StepperMotorTimerAdapter motorTimerAdapter2(motor2);

StepperMotorRadioController stepperMotorRadioController1(motor, CONTROL_X);
StepperMotorRadioController stepperMotorRadioController2(motor2, CONTROL_Y);

const byte address[6] = "00001";
RF24RadioTransmitterManager radioTransmitter(8, 9, address, timerControl);

// ControlStepperMotorWithRadio controlStepperMotorWithRadio(motor, motor2);

BeltDriver belt(LIMIT_SWITCH_PIN_1, LIMIT_SWITCH_PIN_2, timerControl, motor);
BeltDriver belt2(LIMIT_SWITCH_PIN_3, LIMIT_SWITCH_PIN_4, timerControl, motor2);

void setup() {
  Serial.begin(9600);
  
  radioTransmitter.setup(true);
  radioTransmitter.addCommandHandler(&stepperMotorRadioController1);
  radioTransmitter.addCommandHandler(&stepperMotorRadioController2);
  // radioTransmitter.addCommandHandler(&controlStepperMotorWithRadio);
  // timerControl.add_millisecond_handler(&controlStepperMotorWithRadio);
  // timerControl.add_microsecond_handler(&motorTimerAdapter);
  // timerControl.add_microsecond_handler(&motorTimerAdapter2);
}

void loop() {
  timerControl.loop();
}
