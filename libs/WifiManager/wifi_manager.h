#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

class WiFiManager {
public:
  virtual ~WiFiManager() = default;
  
  virtual bool connect() = 0;
  virtual bool sendHttpRequest(float temperature, float humidity) = 0;
};

#endif