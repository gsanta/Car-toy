#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

class TimerHandler {
private:
    int delay;
    unsigned long elapsed;

public:
    TimerHandler(int delay) : delay(delay), elapsed(0) {}
    
    virtual void handleTimerEvent() = 0;
    virtual ~TimerHandler() {}
    
    int getDelay() const { return delay; }
    void setDelay(int value) { delay = value; }
    unsigned long getElapsed() const { return elapsed; }
    void setElapsed(unsigned long value) { elapsed = value; }
};

#endif