#ifndef LORA_WORKER_HPP_
#define LORA_WORKER_HPP_

#include "core/core.hpp"

#include <vector>

#include <SPI.h>
#include <RadioLib.h>

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
    ~Worker();

    using ReceiveCallback = std::function<void(const ISyncable::Data &, uint16_t)>;
    using SendCallback = std::function<bool(HardwareSerial&)>;

public:
    void update();
    void sendAllMessages();
    void addISyncableClass(ISyncable* class_to_add);
    bool send(ISyncable* class_from_send, uint16_t target_address = 0xFFFF);
    bool send(uint16_t address, const SendCallback& callback);
    
    void setReceiveCallback(ReceiveCallback callback);
    void setTargetAddress(uint16_t address);
    uint16_t getTargetAddress() const;
    
private:
    std::vector<ISyncable*> m_classes;
    ReceiveCallback m_receiveCallback;
    uint16_t m_targetAddress = 0xFFFF;

    HardwareSerial LoRaSerial = HardwareSerial(2);
    
    void processReceivedData();
    bool setMode(uint8_t m0, uint8_t m1);
    bool waitForAuxReady(unsigned long timeout_ms = 5000);
};

#endif // LORA_WORKER_HPP_
