#ifndef TIMER_CONTROL_H
#define TIMER_CONTROL_H

#include <Arduino.h>  
#include "timer_handler.h"

#define MAX_TIMER_HANDLERS 5

class TimerControl {
  public:
    TimerControl();

    void add_microsecond_handler(TimerHandler *handler, int delay);
    void add_millisecond_handler(TimerHandler *handler, int delay);

    void loop();

  private:              
    TimerHandler* handlers_micros[MAX_TIMER_HANDLERS];
    int delays_micros[MAX_TIMER_HANDLERS];
    unsigned long last_step_micros[MAX_TIMER_HANDLERS];
    int handler_micros_count;

    TimerHandler* handlers_millis[MAX_TIMER_HANDLERS];
    int delays_millis[MAX_TIMER_HANDLERS];
    unsigned long last_step_millis[MAX_TIMER_HANDLERS];
    int handler_millis_count;
};


#endif