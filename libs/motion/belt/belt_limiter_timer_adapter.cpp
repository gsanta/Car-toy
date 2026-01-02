#include "belt_limiter_timer_adapter.h"
#include "belt_driver.h"

BeltLimiterTimerAdapter::BeltLimiterTimerAdapter(BeltLimiter& beltLimiter, BeltDriver& beltDriver)
  : TimerHandler(100), beltLimiter(beltLimiter), beltDriver(beltDriver) {}

void BeltLimiterTimerAdapter::handleTimerEvent() {
  beltLimiter.checkLimits();
  
  if (beltLimiter.getLeftLimit().isTriggered() || beltLimiter.getRightLimit().isTriggered()) {
    beltDriver.stopMotor();
  }
}
