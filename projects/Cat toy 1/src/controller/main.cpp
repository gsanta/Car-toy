// #include <Arduino.h>

// #include "../../lib/input/joystick/joystick_updater.h"
// #include "../../lib/system/timer/timer_control.h"
// #include "../../lib/input/joystick/joystick.h"
// #include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"
// #include "joystick_command_transmitter.h"

// TimerControl timerControl;

// Joystick joystick(A5, A6, 7);

// const byte address[5] = {0x30, 0x30, 0x30, 0x30, 0x31};
// RF24RadioTransmitter radioTransmitter(8, 9, address, true);

// JoystickUpdater joystickUpdater(joystick, timerControl);
// JoystickCommandTransmitter joystickCommandTransmitter(joystick, radioTransmitter, timerControl);

// void setup() {
//   Serial.begin(9600);
  
//   joystickUpdater.setup();
//   radioTransmitter.setup(false);
//   Serial.println("Radio transmitter initialized");
//   joystickCommandTransmitter.setup();
// }

// void loop() {
//   timerControl.loop();
// }

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
RF24 radio(8, 9);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int SW1 = 7;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.stopListening();  // ← ADD THIS LINE! Switch to TX mode
}

void loop() {
  if (digitalRead(SW1) == HIGH) {
    msg[0] = 111;
    radio.write(msg, 1);
  }
}