#ifndef IR_OBSTACLE_DETECTOR_TIMER_ADAPTER_H
#define IR_OBSTACLE_DETECTOR_TIMER_ADAPTER_H

#include "../../system/timer/timer_handler.h"
#include "stepper_motor_driver.h"

class StepperMotorTimerAdapter : public TimerHandler {
public:
  StepperMotorTimerAdapter(class StepperMotorDriver* driver) : driver(driver) {}

  void stop() {
    stopped = true;
  }

  void start() {
    stopped = false;
  }

  void handleTimerEvent() override {
    if (stopped) {
        return;
    }
    driver->rotate();
    delayMicroseconds(2);
    driver->stop();
  }

private:
  class StepperMotorDriver* driver;

  bool stopped = true;
};

#endif
