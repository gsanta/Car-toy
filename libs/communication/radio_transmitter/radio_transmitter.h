#ifndef RADIO_TRANSMITTER_H
#define RADIO_TRANSMITTER_H

#include <stdint.h>
#include <stddef.h>

class RadioTransmitter {
public:
  virtual ~RadioTransmitter() = default;
  
  virtual void setup(bool read) = 0;
  virtual bool read() = 0;
  virtual void write(const char* text, size_t length) = 0;
  virtual const char* getReceivedText() = 0;
  virtual const void clearReceivedText() = 0;
};

#endif