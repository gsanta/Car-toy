#include "remote_control_timer_listener.h"
#include "remote_control.h"

RemoteControlTimerListener::RemoteControlTimerListener(RemoteControl& remoteControl)
  : TimerHandler(20), remoteControl(remoteControl) {}

void RemoteControlTimerListener::handleTimerEvent() {
  remoteControl.receive_remote_control_signal();
}
