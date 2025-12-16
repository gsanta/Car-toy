#ifndef MOTOR_DRIVER_A4988_H
#define MOTOR_DRIVER_A4988_H

#include "stepper_motor_driver.h"

class MotorDriverA4988 : public StepperMotorDriver {
  public:
    MotorDriverA4988(uint8_t stepPin, uint8_t dirPin);

    void setDirection(uint8_t direction) override;

    void rotate();

    void stop() override;

    ~MotorDriverA4988() override {}

  private:
    uint8_t stepPin;
    uint8_t dirPin;
    uint8_t lastStepVoltage = LOW;
};

#endif