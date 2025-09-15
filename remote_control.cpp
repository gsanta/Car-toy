#include <Arduino.h>
#include <Arduino.h>
#include <IRremote.hpp>
#include "remote_control.h"
#include "command_handler.h"

#define DECODE_NEC

RemoteControl::RemoteControl(int receiverPin) : pin(receiverPin), handlerCount(0) {}

void RemoteControl::setup_remote_control() {
    Serial.begin(9600);
    IrReceiver.begin(pin, true);
}

void RemoteControl::add_command_handler(CommandHandler *handler) {
    if (handlerCount < MAX_COMMAND_HANDLERS) {
        handlers[handlerCount++] = handler;
    }
}

void RemoteControl::receive_remote_control_signal() {
    if (IrReceiver.decode()) {
        IrReceiver.resume();

        IrReceiver.printIRResultShort(&Serial);

        for (int i = 0; i < handlerCount; ++i) {
            if (IrReceiver.decodedIRData.command == 0x5) {
                handlers[i]->handleCommand("Forward");
            } else if (IrReceiver.decodedIRData.command == 0xD) {
                handlers[i]->handleCommand("Backward");
            } else if (IrReceiver.decodedIRData.command == 0x8) {
                handlers[i]->handleCommand("Left");
            } else if (IrReceiver.decodedIRData.command == 0xA) {
                handlers[i]->handleCommand("Right");
            } else if (IrReceiver.decodedIRData.command == 0x6) {
                handlers[i]->handleCommand("Stop");
            }

        }
    }
}


// void setup_remote_control() {
//   Serial.begin(9600);
//   IrReceiver.begin(11, true);
// }

// void receive_remote_control_signal(SignalManager &manager) {
//   if (IrReceiver.decode()) {
//     IrReceiver.resume();

//     if (IrReceiver.decodedIRData.command == 0x5) {
//         manager.handleSignal("Forward");
//     } else if (IrReceiver.decodedIRData.command == 0xD) {
//         manager.handleSignal("Stop");
//     }
//   }
// }