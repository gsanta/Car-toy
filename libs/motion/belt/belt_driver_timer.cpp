#include "belt_driver_timer.h"
#include "belt_driver.h"

BeltDriverTimer::BeltDriverTimer(BeltDriver& beltDriver)
  : TimerHandler(beltDriver.getDelay()), beltDriver(beltDriver) {}

void BeltDriverTimer::handleTimerEvent() {
    if (beltDriver.isMovementBlocked()) {
        return;
    }

    setDelay(beltDriver.getDelay());

    beltDriver.pulse();
}
