#ifndef LORA_WORKER_HPP_
#define LORA_WORKER_HPP_

#include "core/core.hpp"

#include <SPI.h>
#include <vector>
#include "externals/IWorker.hpp"

#include "game_modes/ISyncable.hpp"

namespace lora
{
    class Worker;
}

class lora::Worker : public IWorker
{
    DECLARE_CLASS(Worker)

private:
    Worker();

public:
    ~Worker() = default;

public:
    void update() override;

public:
    void sendAllMessages();
    void addISyncableClass(ISyncable* class_to_add);

private:
    std::vector<ISyncable*> m_classes;

    byte m_msg_count = 0;            // count of outgoing messages
    byte m_destination = 0xFF;      // destination to send to
    long m_last_send_time = 0;        // last send time
    int m_interval = 2000;          // interval between sends

#ifdef ESP8266
    uint64_t m_local_address = ESP.getChipId();
#elif defined(ESP32)
    uint64_t m_local_address = ESP.getEfuseMac();
#endif
};

#endif LORA_WORKER_HPP_