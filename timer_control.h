#ifndef TIMER_CONTROL_H
#define TIMER_CONTROL_H

#include <Arduino.h>  
#include "timer_handler.h"

#define MAX_TIMER_HANDLERS 5

class TimerControl {
  public:
    TimerControl();

    void add_microsecond_handler(TimerHandler *handler, int delay);

    void loop();

  private:              
    TimerHandler* handlers[MAX_TIMER_HANDLERS];
    int delays_micros[MAX_TIMER_HANDLERS];
    int last_step_micros[MAX_TIMER_HANDLERS];
    int handlerCount;
};

#endif