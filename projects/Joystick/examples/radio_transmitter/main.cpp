#include <Arduino.h>

#include "../../lib/input/joystick/joystick_updater.h"
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"
#include "test_joystick_radio_transmitter.h"

TimerControl timerControl;

Joystick joystick(A5, A6, 7);
JoystickUpdater joystickUpdater(joystick, timerControl);

const byte address[6] = "00001";
RF24RadioTransmitter radioTransmitter(8, 9, address);

TestJoystickRadioTransmitter testTransmitter(joystick, radioTransmitter);

void setup() {
  Serial.begin(9600);
  
  joystickUpdater.setup();
  radioTransmitter.setup(false);
  timerControl.add_millisecond_handler(&testTransmitter);
}

void loop() {
  timerControl.loop();
  // joystick.read();
  // Serial.println("X: " + String(joystick.getXVal()) + ", Y: " + String(joystick.getYVal()));
  // delay(500);
}
