#include "timer_control.h"
#include <Arduino.h>

TimerControl::TimerControl() : handler_micros_count(0), handler_millis_count(0) {
  for (int i = 0; i < MAX_TIMER_HANDLERS; ++i) {
      last_step_micros[i] = 0;
      delays_micros[i] = 0;
      last_step_millis[i] = 0;
      delays_millis[i] = 0;
  }
}

void TimerControl::add_microsecond_handler(TimerHandler *handler, int delay) {
  if (handler_micros_count < MAX_TIMER_HANDLERS) {
      handlers_micros[handler_micros_count] = handler;
      delays_micros[handler_micros_count] = delay;
      last_step_micros[handler_micros_count] = micros();
      handler_micros_count++;
  }
}

void TimerControl::add_millisecond_handler(TimerHandler *handler, int delay) {
  if (handler_millis_count < MAX_TIMER_HANDLERS) {
      handlers_millis[handler_millis_count] = handler;
      delays_millis[handler_millis_count] = delay;
      last_step_millis[handler_millis_count] = millis();
      handler_millis_count++;
  }
}

void TimerControl::loop() {
  // Handle microsecond timers
  for (int i = 0; i < handler_micros_count; ++i) {      
    unsigned long now = micros();
    if (now - last_step_micros[i] >= delays_micros[i]) {
      last_step_micros[i] = now;
      handlers_micros[i]->handleTimerEvent();
    }
  }

  // Handle millisecond timers
  for (int i = 0; i < handler_millis_count; ++i) {
    unsigned long now = millis();
    if (now - last_step_millis[i] >= delays_millis[i]) {
      last_step_millis[i] = now;
      handlers_millis[i]->handleTimerEvent();
    }
  }
}