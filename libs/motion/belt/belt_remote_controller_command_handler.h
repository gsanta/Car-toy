#ifndef BELT_REMOTE_CONTROLLER_COMMAND_HANDLER_H
#define BELT_REMOTE_CONTROLLER_COMMAND_HANDLER_H

#include <Arduino.h>
#include "../../input/command_handler.h"

class BeltRemoteController;

class BeltRemoteControllerCommandHandler : public CommandHandler {
private:
  BeltRemoteController* remoteController;

public:
  BeltRemoteControllerCommandHandler(int delay);
  void setController(BeltRemoteController* controller);
  void handleCommand(const char* command) override;
};

#endif
