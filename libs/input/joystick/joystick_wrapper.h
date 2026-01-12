#ifndef JOYSTICK_WRAPPER_H
#define JOYSTICK_WRAPPER_H

#include "../../system/timer/timer_control.h"
#include "joystick_timer_listener.h"
#include "joystick.h"

class JoystickWrapper {
  public:
    JoystickWrapper(int xPin, int yPin, int buttonPin, TimerControl& timerControl);
    void setup();

  private:
    Joystick joystick;
    TimerControl& timerControl;
    JoystickTimerListener timerListener;
};

#endif