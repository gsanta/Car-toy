#ifndef BELT_REMOTE_CONTROLLER_H
#define BELT_REMOTE_CONTROLLER_H

#include "belt_remote_controller_command_handler.h"
#include "../../input/remote_control/remote_control.h"

class BeltDriver;
class RemoteControl;

class BeltRemoteController {
    friend class BeltRemoteControllerCommandHandler;
    
private:
    BeltDriver& beltDriver;
    RemoteControl& remoteControl;
    BeltRemoteControllerCommandHandler commandHandler;

    BeltDriver& getBeltDriver();

public:
    BeltRemoteController(BeltDriver& beltDriver, RemoteControl& remoteControl);
    ~BeltRemoteController();
};

#endif // BELT_REMOTE_CONTROLLER_H
