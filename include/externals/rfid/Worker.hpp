#ifndef RFID_WORKER_HPP_
#define RFID_WORKER_HPP_

#include "core/core.hpp"

#include <SPI.h>
#include <MFRC522.h>

#include "externals/IWorker.hpp"

namespace rfid
{
    class Worker;
}

class rfid::Worker : public IWorker
{
    DECLARE_CLASS(Worker)

public:
    struct UID
    {
        UID() = default;

        byte* raw_data = nullptr;
        size_t uid_size = 6;

        bool operator==(const UID& left) const
        {
            for (size_t i = 0; i < 6; i++)
            {
                if (raw_data[i] != left.raw_data[i])
                {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const UID& left) const
        {
            return !(*this == left);
        }
    };

public:
    struct UIDHash
    {
        size_t operator()(const UID& uid) const
        {
            size_t hash;
            for (size_t i = 0; i < uid.uid_size; i++)
            {
                hash ^= std::hash<byte>{}(uid.raw_data[i]) + 0xFF + (hash << 6) + (hash >> 2);
            }
            
            return hash;
        }
    };

private:
    Worker();

public:
    ~Worker() = default;

public:
    void update() override;

public:
    bool tagDetected();
    MFRC522::MIFARE_Key getDetectedCard();
    UID getUIDCard();

private:
    MFRC522 m_rfid; //= MFRC522(ESP_EXTERNAL_RFID_SS_PIN, ESP_EXTERNAL_RFID_RST_PIN);
    MFRC522::MIFARE_Key m_key;
    MFRC522::StatusCode m_status;

    bool tag_detected = false;
};

#endif  // RFID_WORKER_HPP_
