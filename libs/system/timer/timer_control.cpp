#include "timer_control.h"
#include <Arduino.h>

TimerControl::TimerControl() : handler_micros_count(0), handler_millis_count(0) {
}

void TimerControl::add_microsecond_handler(TimerHandler *handler) {
  if (handler_micros_count < MAX_TIMER_HANDLERS) {
      handlers_micros[handler_micros_count] = handler;
      handler->setElapsed(micros());
      handler_micros_count++;
  }
}

void TimerControl::add_millisecond_handler(TimerHandler *handler) {
  if (handler_millis_count < MAX_TIMER_HANDLERS) {
      handlers_millis[handler_millis_count] = handler;
      handler->setElapsed(millis());
      handler_millis_count++;
  }
}

void TimerControl::remove_microsecond_handler(TimerHandler *handler) {
  for (int i = 0; i < handler_micros_count; ++i) {
    if (handlers_micros[i] == handler) {
      // Shift remaining handlers down
      for (int j = i; j < handler_micros_count - 1; ++j) {
        handlers_micros[j] = handlers_micros[j + 1];
      }
      handler_micros_count--;
      break;
    }
  }
}

void TimerControl::remove_millisecond_handler(TimerHandler *handler) {
  for (int i = 0; i < handler_millis_count; ++i) {
    if (handlers_millis[i] == handler) {
      // Shift remaining handlers down
      for (int j = i; j < handler_millis_count - 1; ++j) {
        handlers_millis[j] = handlers_millis[j + 1];
      }
      handler_millis_count--;
      break;
    }
  }
}

void TimerControl::loop() {
  // Handle microsecond timers
  for (int i = 0; i < handler_micros_count; ++i) {
    TimerHandler* handler = handlers_micros[i];
    unsigned long now = micros();
    if (now - handler->getElapsed() >= handler->getDelay()) {
      handler->setElapsed(now);
      handler->handleTimerEvent();
    }
  }

  // Handle millisecond timers
  for (int i = 0; i < handler_millis_count; ++i) {
    TimerHandler* handler = handlers_millis[i];
    unsigned long now = millis();
    if (now - handler->getElapsed() >= handler->getDelay()) {
      handler->setElapsed(now);
      handler->handleTimerEvent();
    }
  }
}