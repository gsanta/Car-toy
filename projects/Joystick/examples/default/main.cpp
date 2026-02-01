#include <Arduino.h>

#include "../../lib/system/timer/timer_control.h"
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/input/joystick/joystick_updater.h"
#include "../../src/test_staged_joystick_reader.h"

TimerControl timerControl;

Joystick joystick(A0, A1, 7);

JoystickUpdater joystickUpdater(joystick, timerControl);


TestStagedJoystickReader testReader(joystick);

void setup() {
  Serial.begin(9600);

  joystickUpdater.setup();
  timerControl.add_millisecond_handler(&testReader);
}

void loop() {
  timerControl.loop();
}
