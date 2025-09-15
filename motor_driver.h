#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Adafruit_MotorShield.h>
#include <Arduino.h>
#include "directions.h"

class MotorDriver {
  public:
    MotorDriver();
    void setup();
    void run(uint8_t direction);
    void turn(uint8_t direction);

  private:
    static const uint8_t NUM_MOTORS = 2;
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor* motors[NUM_MOTORS];
};

#endif