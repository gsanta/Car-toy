#include <Arduino.h>
#include "joystick.h"
#include "joystick_timer_listener.h"
#include "joystick_command_handler.h"

Joystick::Joystick(int xPin, int yPin, int buttonPin) : xPin(xPin), yPin(yPin), buttonPin(buttonPin), handlerCount(0) {}

void Joystick::setup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void Joystick::addCommandHandler(JoystickCommandHandler *handler) {
  if (handlerCount < MAX_COMMAND_HANDLERS) {
      handlers[handlerCount++] = handler;
  }
}

void Joystick::read() {
  int previousXVal = xVal;
  int previousYVal = yVal;
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  int previousButtonState = buttonState;
  buttonState = digitalRead(buttonPin) == LOW ? 1 : 0;

  for (int i = 0; i < handlerCount; ++i) {
    if (xVal != previousXVal || yVal != previousYVal) {
        handlers[i]->handleMove(xVal, yVal);
    }

    if (buttonState != previousButtonState) {
        handlers[i]->handleClick(buttonState);
    }
  }
}