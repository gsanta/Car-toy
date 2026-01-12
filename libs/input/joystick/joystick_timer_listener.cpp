#include "joystick_timer_listener.h"
#include "joystick.h"

JoystickTimerListener::JoystickTimerListener(Joystick& joystick)
  : TimerHandler(20), joystick(joystick) {}

void JoystickTimerListener::handleTimerEvent() {
  joystick.read();
}
