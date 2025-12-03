#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

class TimerHandler {
public:
    virtual void handleTimerEvent() = 0;
    virtual ~TimerHandler() {}
};

#endif