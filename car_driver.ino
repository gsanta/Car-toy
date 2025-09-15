#include <Adafruit_MotorShield.h>
#include "remote_control.h"
#include "motor_driver.h"
#include "motor_command_handler.h"

MotorDriver driver;

MotorCommandHandler motorHandler(driver);

RemoteControl remote(11);

void setup() {
  remote.setup_remote_control();
  remote.add_command_handler(&motorHandler);
  driver.setup();
}

void loop() {
  remote.receive_remote_control_signal();
  // receive_remote_control_signal(manager);
  // driver.run(FORWARD);
  // delay(1000);
  // driver.run(BACKWARD);
  // delay(1000);
}
