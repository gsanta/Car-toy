#include <Arduino.h>

#include "../../lib/input/joystick/joystick_updater.h"
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"
#include "joystick_command_transmitter.h"

TimerControl timerControl;

Joystick joystick(A5, A6, 7);

const byte address[5] = {0x30, 0x30, 0x30, 0x30, 0x31};
RF24RadioTransmitter radioTransmitter(8, 9, address);

JoystickUpdater joystickUpdater(joystick, timerControl);
JoystickCommandTransmitter joystickCommandTransmitter(joystick, radioTransmitter, timerControl);

void setup() {
  Serial.begin(9600);
  
  joystickUpdater.setup();
  const bool radioOk = radioTransmitter.setup(false);
  if (!radioOk) {
    Serial.println("Radio transmitter failed to initialize");
    return;
  }

  Serial.println("Radio transmitter initialized");
  joystickCommandTransmitter.setup();
}

void loop() {
  timerControl.loop();
}
