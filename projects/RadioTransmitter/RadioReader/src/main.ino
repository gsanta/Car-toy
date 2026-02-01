#include <Arduino.h>

#include "../lib/system/timer/timer_control.h"
#include "../lib/communication/radio_transmitter/rf24_radio_transmitter.h"
#include "../lib/communication/radio_transmitter/rf24_radio_transmitter_manager.h"

TimerControl timerControl;

const byte address[6] = "00001";
RF24RadioTransmitterManager radioTransmitter(7, 8, address, timerControl);

class TestRadioReadCommandHandler : public RadioReadCommandHandler {
public:

  void handleMessageReceived(const char* message) override {
    if (message != nullptr && message[0] != '\0') {
      Serial.print("Received message: ");
      Serial.println(message);
    }
  };
};

TestRadioReadCommandHandler testHandler;

void setup() {
  Serial.begin(9600);

  radioTransmitter.addCommandHandler(&testHandler);
  radioTransmitter.setup(true);
}

void loop() {
  timerControl.loop();
}
