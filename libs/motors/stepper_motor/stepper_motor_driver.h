#ifndef STEPPER_MOTOR_DRIVER_H
#define STEPPER_MOTOR_DRIVER_H

#include <Arduino.h>

#define UP 1
#define DOWN 2

class StepperMotorDriver {
  public:
    virtual void setDirection(uint8_t direction) = 0;
    virtual void rotate() = 0;
    virtual void stop() = 0;
    virtual ~StepperMotorDriver() {}
};

#endif
