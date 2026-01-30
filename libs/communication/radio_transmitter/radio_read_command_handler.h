#ifndef RADIO_READ_COMMAND_HANDLER_H
#define RADIO_READ_COMMAND_HANDLER_H

class RadioReadCommandHandler {
public:
    virtual void handleMessageReceived(const char* message) = 0;
};

#endif