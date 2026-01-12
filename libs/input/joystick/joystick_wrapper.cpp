#include <Arduino.h>
#include "joystick_wrapper.h"
#include "joystick_timer_listener.h"
#include "joystick_command_handler.h"

JoystickWrapper::JoystickWrapper(int xPin, int yPin, int buttonPin, TimerControl& timerControl) : joystick(xPin, yPin, buttonPin), timerControl(timerControl), timerListener(joystick) {}

void JoystickWrapper::setup() {
  joystick.setup();
  timerControl.add_millisecond_handler(&timerListener);
}