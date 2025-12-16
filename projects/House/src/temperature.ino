#include <Arduino.h>

// Pin where the LED is connected
const int ledPin = 13;  // change to the GPIO you used

void setup() {
  // Set the pin as an output
  pinMode(ledPin, OUTPUT);

  // Turn the LED on
  digitalWrite(ledPin, HIGH);
}

void loop() {
  // Nothing needed here, LED stays on
}