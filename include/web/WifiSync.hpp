#ifndef WEB_WIFISYNC_HPP_
#define WEB_WIFISYNC_HPP_

#include "core/core.hpp"

#include <esp_now.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

namespace web
{
    class WifiSync;
};

class web::WifiSync
{
private:
    typedef struct Data
    {
        int value;
    };

public:
    WifiSync();
    ~WifiSync() = default;

public:
    void onStart();
    void update();

    static void onReceiveStatic(const uint8_t * mac, const uint8_t *incomingData, int len);
    void onReceive(const uint8_t * mac, const uint8_t *incomingData, int len);

private:
    const char* ssid = "ESP32";
    const char* password = "12345678";

    Data m_data;

public:
    static WifiSync* instance;
};

#endif  // WEB_WIFISYNC_HPP_
