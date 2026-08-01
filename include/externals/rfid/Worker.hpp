#ifndef RFID_WORKER_HPP_
#define RFID_WORKER_HPP_

#include "core/core.hpp"

#include <cstdint>
#include <cstring>
#include <array>

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

        // byte* raw_data = nullptr;
        // size_t uid_size = 6;
        std::array<byte, 10> raw_data{};

        bool operator==(const UID& left) const
        {
            if (raw_data.size() != left.raw_data.size())
                return false;

            for (size_t i = 0; i < raw_data.size(); i++)
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

        const char* toString() const
        {
            String result;

            for (size_t i = 0; i < raw_data.size(); i++)
            {
                char buffer[3];
                snprintf(buffer, sizeof(buffer), "%02X", raw_data[i]);
                result += buffer;

                if (i + 1 < raw_data.size())
                {
                    result += ":";
                }
            }

            return result.c_str();
        }
    };

public:
    struct UIDHash
    {
        size_t operator()(const UID& uid) const
        {
            // size_t hash;
            // for (size_t i = 0; i < uid.uid_size; i++)
            // {
            //     hash ^= std::hash<byte>{}(uid.raw_data[i]) + 0xFF + (hash << 6) + (hash >> 2);
            // }
            
            // return hash;

            // size_t hash = 0;

            // for (size_t i = 0; i < uid.raw_data.size(); i++)
            // {
            //     hash ^= static_cast<size_t>(uid.raw_data[i])
            //         + 0xFFFF
            //         + (hash << 6)
            //         + (hash >> 2);
            // }

            // return hash;

            size_t hash = 0;

            for (const auto& byte : uid.raw_data)
            {
                hash ^= static_cast<size_t>(byte) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
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
    MFRC522 m_rfid;
    MFRC522::MIFARE_Key m_key;
    MFRC522::StatusCode m_status;

    bool tag_detected = false;

    UID last_uid;
    bool has_last_uid = false;
};

#endif  // RFID_WORKER_HPP_
