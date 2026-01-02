#ifndef BELT_LIMITER_TIMER_ADAPTER_H
#define BELT_LIMITER_TIMER_ADAPTER_H

#include "belt_limiter.h"
#include "../../system/timer/timer_handler.h"

class BeltDriver;

class BeltLimiterTimerAdapter : public TimerHandler {
private:
  BeltLimiter& beltLimiter;
  BeltDriver& beltDriver;

public:
  BeltLimiterTimerAdapter(BeltLimiter& beltLimiter, BeltDriver& beltDriver);
  void handleTimerEvent() override;
};

#endif
