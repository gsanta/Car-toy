#include "belt_limiter_timer_adapter.h"

BeltLimiterTimerAdapter::BeltLimiterTimerAdapter(BeltLimiter& beltLimiter, LimitReachedCommand& command)
  : beltLimiter(beltLimiter), command(command) {}

void BeltLimiterTimerAdapter::handleTimerEvent() {
  beltLimiter.checkLimits(command);
}
