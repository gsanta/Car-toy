#include <Arduino.h>

#include "../lib/system/timer/timer_control.h"
#include "../lib/communication/radio_transmitter/rf24_radio_transmitter.h"

TimerControl timerControl;

const byte address[6] = "00001";
RF24RadioTransmitter radioTransmitter(7, 8, address);

void setup() {
  Serial.begin(9600);

  radioTransmitter.setup(false);
}

void loop() {
  const char text[] = "Hello World";
  radioTransmitter.write(text, sizeof(text));
  delay(1000);
}
