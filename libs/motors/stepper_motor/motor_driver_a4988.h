#ifndef MOTOR_DRIVER_A4988_H
#define MOTOR_DRIVER_A4988_H

#include "stepper_motor_driver.h"

class MotorDriverA4988 : public StepperMotorDriver {
  public:
    MotorDriverA4988(uint8_t stepPin, uint8_t dirPin);
    
    void setDirection(uint8_t direction) override;
    uint8_t getDirection() override;

    void high() override;

    void low() override;

    bool isRunning() override;

    void pulse() override;
    
    void setIsRunning(bool running) override;

    void setSpeed(int speed) override;
    int getSpeed() override;
    
    int getDelay() override;
    

    ~MotorDriverA4988() override {}

  private:
    uint8_t stepPin;
    uint8_t dirPin;
    uint8_t lastStepVoltage = LOW;
    int speed = 1;
    bool is_running = false;
    uint8_t direction = UP;
};

#endif