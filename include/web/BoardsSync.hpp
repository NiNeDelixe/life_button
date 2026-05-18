#ifndef WEB_WIFISYNC_HPP_
#define WEB_WIFISYNC_HPP_

#include "core/core.hpp"

#include <esp_now.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

namespace web
{
    class BoardsSync;
};

class web::BoardsSync
{
    DECLARE_CLASS(BoardsSync)

private:
    struct Data
    {
        int value;
    };

public:
    enum class BoardSyncMode : uint8_t
    {
        OFF,
        TRANSMIT,
        RECIVE
    };

private:
    BoardsSync();

public:
    ~BoardsSync() = default;

public:
    void onStart();
    void update();

    void changeMode(BoardSyncMode mode);
    void changeMode(uint8_t mode) { changeMode((BoardSyncMode)mode); }

    void sendRawData(void* data, size_t size);

public:
    static void onReceiveStatic(const uint8_t * mac, const uint8_t *incomingData, int len);
    void onReceive(const uint8_t * mac, const uint8_t *incomingData, int len);

private:
    const char* ssid = "ESP32";
    const char* password = "12345678";

    Data m_data;

    BoardSyncMode m_mode = BoardSyncMode::RECIVE;
};

#endif  // WEB_WIFISYNC_HPP_
