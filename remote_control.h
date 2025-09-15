#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include "command_handler.h"

#define MAX_COMMAND_HANDLERS 5

class RemoteControl {
  public:
    RemoteControl(int receiverPin = 11);

    void setup_remote_control();

    void add_command_handler(CommandHandler *handler);

    void receive_remote_control_signal();

  private:              
    int pin;
    CommandHandler* handlers[MAX_COMMAND_HANDLERS];
    int handlerCount;
};

void setup_remote_control();

void receive_remote_control_signal(CommandHandler &handler);

#endif