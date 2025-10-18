#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <Arduino.h>

class DCMotor {
  public:
    virtual void setup() = 0;
    virtual void setSpeed(uint8_t speed) = 0;
    virtual void run(uint8_t direction) = 0;
    virtual ~DCMotor() {}
};

#endif
