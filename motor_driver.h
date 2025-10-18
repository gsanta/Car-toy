#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>
#include "directions.h"
#include "dc_motor.h"

class MotorDriver {
  public:
    MotorDriver();
    void setup();
    void run(uint8_t direction);
    void turn(uint8_t direction);
    void setMotor(uint8_t index, DCMotor* motor);

  private:
    static const uint8_t NUM_MOTORS = 2;
    DCMotor* motors[NUM_MOTORS];
};

#endif