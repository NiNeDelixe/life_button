#include "externals/rfid/Worker.hpp"

#include "core/Polling.hpp"

rfid::Worker::Worker()
{
    //SPI.begin(ESP_EXTERNAL_RFID_SPI_SCK_PIN, ESP_EXTERNAL_RFID_SPI_MISO_PIN, ESP_EXTERNAL_RFID_SPI_MOSI_PIN, ESP_EXTERNAL_RFID_SS_PIN);
    SPI.begin();
    m_rfid.PCD_Init(); 
    m_rfid.PCD_SetAntennaGain(m_rfid.RxGain_max);
    m_rfid.PCD_AntennaOff(); 
    m_rfid.PCD_AntennaOn();

    for (byte i = 0; i < 6; ++i) 
    {
        m_key.keyByte[i] = 0xFF; // 0xFFFFFFFFFFFF
    }
}

void rfid::Worker::update()
{
    EVERY_S(1) 
    {
        // digitalWrite(ESP_EXTERNAL_RFID_RST_PIN, HIGH);
        // delayMicroseconds(2);
        // digitalWrite(ESP_EXTERNAL_RFID_RST_PIN, LOW);
        // m_rfid.PCD_Init();
    }

    if (!m_rfid.PICC_IsNewCardPresent()) 
    {
        tag_detected = false;
        return;
    }
    if (!m_rfid.PICC_ReadCardSerial()) 
    {
        tag_detected = false;
        return;
    }

    tag_detected = true;

    led_circuit::Worker::getInstance().singleRun();
}

bool rfid::Worker::tagDetected()
{
    return tag_detected;
}

MFRC522::MIFARE_Key rfid::Worker::getDetectedCard()
{
    if (tagDetected())
    {
        /* code */
    }
    
    return MFRC522::MIFARE_Key();
}

rfid::Worker::UID rfid::Worker::getUIDCard()
{
    if (tagDetected())
    {
        auto uid = rfid::Worker::UID();
        uid.raw_data = m_key.keyByte;
        return uid;
    }

    return rfid::Worker::UID();
}
