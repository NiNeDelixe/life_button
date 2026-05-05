#include "web/WifiSync.hpp"

#include "core/Polling.hpp"

web::WifiSync* web::WifiSync::instance = nullptr;

uint8_t receiverMac[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};

web::WifiSync::WifiSync()
{
    instance = this;
}

void web::WifiSync::onStart()
{
    //Transmeter
    if (is_transmitter)
    {
        WiFi.mode(WIFI_STA);
        esp_now_init();

        esp_now_peer_info_t peer = {};
        memcpy(peer.peer_addr, receiverMac, 6);
        esp_now_add_peer(&peer);
    }

    //Reciver
    if (!is_transmitter)
    {
        WiFi.mode(WIFI_STA);
        esp_now_init();
        esp_now_register_recv_cb(onReceiveStatic);
    }
}

void web::WifiSync::update()
{
    if (!is_transmitter)
    {
        return;
    }
    
    m_data.value = 123;
    esp_now_send(receiverMac, (uint8_t*)&m_data, sizeof(m_data));
}

void web::WifiSync::onReceiveStatic(const uint8_t * mac, const uint8_t *incomingData, int len)
{
    if (instance) 
    {
        instance->onReceive(mac, incomingData, len);
    }
}

void web::WifiSync::onReceive(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&m_data, incomingData, sizeof(m_data));
}
