#include <Arduino.h>
#include "joystick.h"

Joystick::Joystick(int xPin, int yPin, int buttonPin) : xPin(xPin), yPin(yPin), buttonPin(buttonPin) {}

void Joystick::setup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void Joystick::read() {
  int previousXVal = xVal;
  int previousYVal = yVal;
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  int previousButtonState = buttonState;
  buttonState = digitalRead(buttonPin) == LOW ? 1 : 0;
}

int Joystick::getXVal() const {
  return xVal;
}

int Joystick::getYVal() const {
  return yVal;
}

int Joystick::getXMin() const {
  return xMin;
}

int Joystick::getXMax() const {
  return xMax;
}

int Joystick::getYMin() const {
  return yMin;
}

int Joystick::getYMax() const {
  return yMax;
}

int Joystick::getButtonState() const {
  return buttonState;
}