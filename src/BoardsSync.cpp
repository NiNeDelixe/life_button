#include "web/BoardsSync.hpp"

#include "core/Polling.hpp"

uint8_t receiverMac[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};

web::BoardsSync::BoardsSync()
{
}

void web::BoardsSync::onStart()
{
    if (m_mode == BoardSyncMode::OFF)
    {
        return;
    }
    
    // WiFi.mode(WIFI_STA);
    // esp_now_init();

    //Transmeter
    if (m_mode == BoardSyncMode::TRANSMIT)
    {
        // esp_now_peer_info_t peer = {};
        // memcpy(peer.peer_addr, receiverMac, 6);
        // esp_now_add_peer(&peer);
    }

    //Reciver
    if (m_mode == BoardSyncMode::RECIVE)
    {
        //esp_now_register_recv_cb(onReceiveStatic);
    }
}

void web::BoardsSync::update()
{
    if (m_mode != BoardSyncMode::TRANSMIT)
    {
        return;
    }
    
    //esp_now_send(receiverMac, (uint8_t*)&m_data, sizeof(m_data));
}

void web::BoardsSync::changeMode(BoardSyncMode mode)
{
    if (m_mode == mode)
    {
        return;
    }
    
    m_mode = mode;

    onStart();
}

void web::BoardsSync::sendRawData(void *data, size_t size)
{
    struct Data
    {
        void* data;
    } data_to_send;
    
    data_to_send.data = data;

    //send
}

void web::BoardsSync::onReceiveStatic(const uint8_t * mac, const uint8_t *incomingData, int len)
{
    getInstance().onReceive(mac, incomingData, len);
}

void web::BoardsSync::onReceive(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&m_data, incomingData, sizeof(m_data));
}
