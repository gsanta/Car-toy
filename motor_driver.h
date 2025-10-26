#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>
#include "directions.h"
#include "dc_motor.h"

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

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