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
public:
    Worker();
    ~Worker() = default;

public:
    void update() override;

public:
    bool tagDetected();
     

private:
    //MFRC522 m_rfid = MFRC522(ESP_EXTERNAL_RFID_SS_PIN, ESP_EXTERNAL_RFID_RST_PIN);
    MFRC522::MIFARE_Key m_key;
    MFRC522::StatusCode m_status;

    bool tag_detected = false;
};

extern rfid::Worker _rfid_reader;

#endif  // RFID_WORKER_HPP_
