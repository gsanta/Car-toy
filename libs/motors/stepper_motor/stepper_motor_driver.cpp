#include "stepper_motor_driver.h"

void StepperMotorDriver::setSpeed(int speed) {
    this->speed = speed;
}

int StepperMotorDriver::getSpeed() {
    return speed;
}

int StepperMotorDriver::getDelay() {
    // Higher speed = smaller delay
    // Speed 1 = 1000ms, Speed 2 = 500ms, Speed 3 = 333ms, etc.
    if (speed <= 0) {
        return 1000;
    }
    return 1000 / speed;
}
