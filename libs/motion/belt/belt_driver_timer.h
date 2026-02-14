#ifndef BELT_LIMITER_TIMER_ADAPTER_H
#define BELT_LIMITER_TIMER_ADAPTER_H

#include "belt_limiter.h"
#include "../../system/timer/timer_handler.h"

class BeltDriver;

class BeltDriverTimer : public TimerHandler {
private:
  BeltDriver& beltDriver;

public:
  BeltDriverTimer(BeltDriver& beltDriver);
  void handleTimerEvent() override;
};

#endif
