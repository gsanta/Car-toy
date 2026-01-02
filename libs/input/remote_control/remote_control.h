#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include "../command_handler.h"
#include "../../system/timer/timer_control.h"
#include "remote_control_timer_listener.h"

#define MAX_COMMAND_HANDLERS 5

class TimerControl;

class RemoteControl {
  public:
    RemoteControl(int receiverPin, TimerControl& timerControl);

    void setup_remote_control();

    void add_command_handler(CommandHandler *handler);

    void receive_remote_control_signal();

  private:              
    int pin;
    TimerControl& timerControl;
    CommandHandler* handlers[MAX_COMMAND_HANDLERS];
    RemoteControlTimerListener timerListener;
    int handlerCount;
};

void setup_remote_control();

void receive_remote_control_signal(CommandHandler &handler);

#endif