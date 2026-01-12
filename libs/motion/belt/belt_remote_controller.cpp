#include "belt_remote_controller.h"
#include "belt_remote_controller_command_handler.h"

BeltRemoteController::BeltRemoteController(BeltDriver& beltDriver, RemoteControl& remoteControl) 
  : beltDriver(beltDriver), remoteControl(remoteControl), commandHandler(100) {
  commandHandler.setController(this);
  remoteControl.add_command_handler(&commandHandler);
}

BeltRemoteController::~BeltRemoteController() {
}

BeltDriver& BeltRemoteController::getBeltDriver() {
  return beltDriver;
}