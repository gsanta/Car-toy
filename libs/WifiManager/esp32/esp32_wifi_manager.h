#ifndef ESP32_WIFI_MANAGER_H
#define ESP32_WIFI_MANAGER_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "../wifi_manager.h"

class ESP32WiFiManager : public WiFiManager {
private:
  const char* ssid;
  const char* password;
  const char* server;
  int port;

public:
  ESP32WiFiManager(const char* ssid, const char* password, const char* server, int port = 80);
  bool connect() override;
  bool sendHttpRequest(float temperature, float humidity) override;
};

#endif
