#ifndef JOYSTICK_COMMAND_TRANSMITTER_H
#define JOYSTICK_COMMAND_TRANSMITTER_H

#include <Arduino.h>
#include <string.h>
#include "../../../libs/input/joystick/staged_joystick_reader.h"
#include "../../../libs/system/timer/timer_handler.h"
#include "../../../libs/system/timer/timer_control.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"

class JoystickCommandTransmitter : public TimerHandler, public StagedJoystickReader {
public:
  JoystickCommandTransmitter(Joystick& joystick, RF24RadioTransmitter& transmitter, TimerControl& timerControl) 
    : TimerHandler(100), StagedJoystickReader(3, joystick), transmitter(transmitter), timerControl(timerControl),
      lastXStage(99), lastYStage(99), lastSentAt(0) {}

  void setup() {
    timerControl.add_millisecond_handler(this);
  }

  void handleTimerEvent() override {
    handleMove(getJoystick().getXVal(), getJoystick().getYVal());
  }


  void handleClick(int buttonState) override {
    // No action needed for click right now
  }

  void handleStagedMove(int xStage, int yStage) override {
    const unsigned long now = millis();
    const bool changed = (xStage != lastXStage || yStage != lastYStage);
    const bool resendDue = (now - lastSentAt) >= RESEND_INTERVAL_MS;

    if (changed || resendDue) {
      sendStageMessage(xStage, yStage, changed);
      lastXStage = xStage;
      lastYStage = yStage;
      lastSentAt = now;
    }
  }

private:
  void sendStageMessage(int xStage, int yStage, bool changed) {
    char text[32] = {0};
    snprintf(text, sizeof(text), "Move X Stage: %d, Y Stage: %d", xStage, yStage);
    transmitter.write(text, sizeof(text));
  }

  static const unsigned long RESEND_INTERVAL_MS = 1000;

  RF24RadioTransmitter& transmitter;
  TimerControl& timerControl;

  int lastXStage;
  int lastYStage;
  unsigned long lastSentAt;
};

#endif
