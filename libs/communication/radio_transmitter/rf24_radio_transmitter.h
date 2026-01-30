#ifndef RF24_RADIO_TRANSMITTER_H
#define RF24_RADIO_TRANSMITTER_H

#include "radio_transmitter.h"
#include <RF24.h>

class RF24RadioTransmitter : public RadioTransmitter {
private:
  RF24 radio;
  uint8_t cePin;
  uint8_t csnPin;
  byte address[6];
  char receivedText[32];
    
public:
  RF24RadioTransmitter(uint8_t ce, uint8_t csn, const byte* addr);

  ~RF24RadioTransmitter() override;
  
  void setup(bool read) override;
  bool read() override;
  void write(const char* text, size_t length) override;
  const char* getReceivedText() override;
  const void clearReceivedText() override;
};

#endif
