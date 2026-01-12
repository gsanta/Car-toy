#ifndef JOYSTICK_TIMER_LISTENER_H
#define JOYSTICK_TIMER_LISTENER_H

#include "../../system/timer/timer_handler.h"

class Joystick;

class JoystickTimerListener : public TimerHandler {
private:
  Joystick& joystick;

public:
  JoystickTimerListener(Joystick& joystick);

  void handleTimerEvent() override;
};

#endif
