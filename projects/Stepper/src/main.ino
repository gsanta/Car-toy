#include <Arduino.h>

const int dirPin = 2;
const int stepPin = 3; 

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  delay(1000); 

  digitalWrite(dirPin, HIGH);
}

void loop() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(5000); 
  digitalWrite(stepPin, LOW);
  delayMicroseconds(5000);
}
