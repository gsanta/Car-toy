#ifndef IR_OBSTACLE_DETECTOR_TIMER_ADAPTER_H
#define IR_OBSTACLE_DETECTOR_TIMER_ADAPTER_H

#include "../../system/timer/timer_handler.h"
#include "stepper_motor_driver.h"

class StepperMotorTimerAdapter : public TimerHandler {
public:
  StepperMotorTimerAdapter(class StepperMotorDriver& driver) : TimerHandler(driver.getDelay()), driver(driver) {}

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

    // Update delay based on current speed
    setDelay(driver.getDelay());

    static bool pulseState = false;
    
    if (!pulseState) {
      driver.rotate();
      pulseState = true;
    } else {
      driver.stop();
      pulseState = false;
    }
  }

private:
  class StepperMotorDriver& driver;

  bool stopped = false;
};

#endif
