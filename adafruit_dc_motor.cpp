#include "adafruit_dc_motor.h"

AdafruitDCMotor::AdafruitDCMotor(uint8_t motorId, Adafruit_MotorShield* shield) : motorId(motorId), shield(shield) {
  motor = nullptr; // Initialize motor pointer to null
}

void AdafruitDCMotor::setSpeed(uint8_t speed) {
  if (motor) motor->setSpeed(speed);
}

void AdafruitDCMotor::run(uint8_t direction) {
  if (motor) motor->run(direction);
}

void AdafruitDCMotor::setup() {
    if (!shield->begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  motor = shield->getMotor(motorId);
}
