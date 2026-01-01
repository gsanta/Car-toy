#ifndef BELT_LIMITER_TIMER_ADAPTER_H
#define BELT_LIMITER_TIMER_ADAPTER_H

#include "belt_limiter.h"
#include "../../logic/limit_switch/limit_reached_command.h"
#include "../../system/timer/timer_handler.h"

class BeltLimiterTimerAdapter : public TimerHandler {
private:
  BeltLimiter& beltLimiter;
  LimitReachedCommand& command;

public:
  BeltLimiterTimerAdapter(BeltLimiter& beltLimiter, LimitReachedCommand& command);
  void handleTimerEvent() override;
};

#endif
