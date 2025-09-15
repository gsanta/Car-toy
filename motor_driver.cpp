#include "motor_driver.h"

MotorDriver::MotorDriver()
  : AFMS(Adafruit_MotorShield()) {
  for (uint8_t m = 0; m < NUM_MOTORS; m++) {
    motors[m] = nullptr;
  }
}

void MotorDriver::setup() {
  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  motors[0] = AFMS.getMotor(1);
  motors[1] = AFMS.getMotor(2);
}

void MotorDriver::run(uint8_t direction) {
  for (uint8_t m = 0; m < NUM_MOTORS; m++) {
    if (motors[m]) { // check pointer is valid
      motors[m]->run(direction);
      motors[m]->setSpeed(100);
    }
  }
}

void MotorDriver::turn(uint8_t direction) {
  if (direction == LEFT) {
    motors[0]->run(FORWARD);  // Left motor forward
    motors[1]->run(BACKWARD); // Right motor backward
  } else if (direction == RIGHT) {
    motors[0]->run(BACKWARD); // Left motor backward
    motors[1]->run(FORWARD);  // Right motor forward
  }
}
