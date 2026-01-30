#ifndef RADIO_TIMER_LISTENER_H
#define RADIO_TIMER_LISTENER_H

#include "../../system/timer/timer_handler.h"
#include "radio_transmitter.h"

class RadioTimerListener : public TimerHandler {
public:
  RadioTimerListener(RadioTransmitter& transmitter, unsigned long pollingInterval) 
    : TimerHandler(pollingInterval), transmitter(transmitter) {}

  void stop() {
    stopped = true;
  }

  void start() {
    stopped = false;
  }

  void handleTimerEvent() override {
    if (stopped) {
      return;
    }

    transmitter.read();
  }

private:
  RadioTransmitter& transmitter;
  bool stopped = false;
};

#endif
