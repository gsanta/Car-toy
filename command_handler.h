#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

class CommandHandler {
public:
    virtual void handleCommand(const char* command) = 0;
    virtual ~CommandHandler() {}
};

#endif