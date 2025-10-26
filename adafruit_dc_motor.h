#ifndef ADAFRUIT_DC_MOTOR_H
#define ADAFRUIT_DC_MOTOR_H

#include <Adafruit_MotorShield.h>
#include "dc_motor.h"

class AdafruitDCMotor : public DCMotor {
  public:
    AdafruitDCMotor(uint8_t motorId, Adafruit_MotorShield* shield);

    void setup() override;

    void setSpeed(uint8_t speed) override;

    void run(uint8_t direction) override;

  private:
    uint8_t motorId;
    Adafruit_DCMotor* motor;
    Adafruit_MotorShield* shield;
};

#endif