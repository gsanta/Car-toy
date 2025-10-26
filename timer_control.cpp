#include "timer_control.h"

TimerControl::TimerControl() : handlerCount(0) {
  for (int i = 0; i < MAX_TIMER_HANDLERS; ++i) {
      last_step_micros[i] = 0;
      delays_micros[i] = 0;
  }
}

void TimerControl::add_microsecond_handler(TimerHandler *handler, int delay) {
  if (handlerCount < MAX_TIMER_HANDLERS) {
      handlers[handlerCount] = handler;
      delays_micros[handlerCount] = delay;
      last_step_micros[handlerCount] = millis();
      handlerCount++;
  }
}

void TimerControl::loop() {
  for (int i = 0; i < handlerCount; ++i) {      

    unsigned long now = millis();
    if (now - last_step_micros[i] >= delays_micros[i]) {
      last_step_micros[i] = now;
      handlers[i]->handleTimerEvent();
    }
  }
}