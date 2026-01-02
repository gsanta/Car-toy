#ifndef REMOTE_CONTROL_TIMER_LISTENER_H
#define REMOTE_CONTROL_TIMER_LISTENER_H

#include "../../system/timer/timer_handler.h"

class RemoteControl;

class RemoteControlTimerListener : public TimerHandler {
private:
  RemoteControl& remoteControl;

public:
  RemoteControlTimerListener(RemoteControl& remoteControl);
  void handleTimerEvent() override;
};

#endif
