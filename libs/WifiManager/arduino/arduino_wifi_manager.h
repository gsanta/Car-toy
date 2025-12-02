#ifndef ARDUINO_WIFI_MANAGER_H
#define ARDUINO_WIFI_MANAGER_H

#include <WiFiS3.h>
#include "../wifi_manager.h"

class ArduinoWiFiManager : public WiFiManager {
private:
  const char* ssid;
  const char* password;
  const char* server;
  int port;
  WiFiClient client;

public:
  ArduinoWiFiManager(const char* ssid, const char* password, const char* server, int port = 80);
  bool connect() override;
  bool sendHttpRequest(float temperature, float humidity) override;
};

#endif
