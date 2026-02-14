#ifndef STEPPER_MOTOR_DRIVER_H
#define STEPPER_MOTOR_DRIVER_H

#include <Arduino.h>

#define UP 1
#define DOWN 2

class StepperMotorDriver {
  public:
    virtual bool isRunning();

    virtual void high() = 0;
    
    virtual void low() = 0;

    virtual void pulse();
    
    virtual void setDirection(uint8_t direction) = 0;
    virtual uint8_t getDirection() = 0;

    virtual void setIsRunning(bool running) = 0;

    virtual void setSpeed(int speed) = 0;
    virtual int getSpeed() = 0;
    
    virtual int getDelay() = 0;
    
    virtual ~StepperMotorDriver() {}
};

#endif
