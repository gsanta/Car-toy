#ifndef RF24_RADIO_TRANSMITTER_MANAGER_H
#define RF24_RADIO_TRANSMITTER_MANAGER_H

#include "radio_transmitter.h"
#include "radio_read_command_handler.h"
#include "rf24_radio_transmitter.h"
#include "../../system/timer/timer_control.h"

#define MAX_COMMAND_HANDLERS 5

class RF24RadioTransmitterManager;

class RadioTimerListener : public TimerHandler {
private:
  RF24RadioTransmitterManager& manager;

public:
  RadioTimerListener(RF24RadioTransmitterManager& manager);

  void handleTimerEvent() override;
};


class RF24RadioTransmitterManager {
  friend class RadioTimerListener;
  public:
    RF24RadioTransmitterManager(uint8_t ce, uint8_t csn, const byte* addr, TimerControl& timerControl);

    void setup(bool read);

    void addCommandHandler(RadioReadCommandHandler *handler);

    RF24RadioTransmitter& getRadioTransmitter() { return radio; }

  private:
    void update();

    RF24RadioTransmitter radio;
    TimerControl& timerControl;
    RadioTimerListener timerListener;

    RadioReadCommandHandler* handlers[MAX_COMMAND_HANDLERS];
    int handlerCount = 0;
};

inline RadioTimerListener::RadioTimerListener(RF24RadioTransmitterManager& manager) : TimerHandler(20), manager(manager) {}

inline void RadioTimerListener::handleTimerEvent() {
  manager.update();
}


#endif