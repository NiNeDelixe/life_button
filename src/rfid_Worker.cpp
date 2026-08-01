#include "externals/rfid/Worker.hpp"

#include "core/Polling.hpp"

rfid::Worker::Worker()
{
    SPI.begin(ESP_EXTERNAL_RFID_SPI_SCK_PIN, ESP_EXTERNAL_RFID_SPI_MISO_PIN, ESP_EXTERNAL_RFID_SPI_MOSI_PIN, ESP_EXTERNAL_RFID_SS_PIN);
    m_rfid = MFRC522(ESP_EXTERNAL_RFID_SS_PIN, ESP_EXTERNAL_RFID_RST_PIN);
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
        digitalWrite(ESP_EXTERNAL_RFID_RST_PIN, HIGH);
        digitalWrite(ESP_EXTERNAL_RFID_RST_PIN, LOW);
        m_rfid.PCD_Init();
    }

    if (!m_rfid.PICC_IsNewCardPresent() || !m_rfid.PICC_ReadCardSerial()) 
    {
        tag_detected = false;
        return;
    }

    tag_detected = true;
}

bool rfid::Worker::tagDetected()
{
    return tag_detected;
}

MFRC522::MIFARE_Key rfid::Worker::getDetectedCard()
{
    if (tagDetected())
    {
        return m_key;
    }
    
    return MFRC522::MIFARE_Key();
}

rfid::Worker::UID rfid::Worker::getUIDCard()
{
    auto uid = rfid::Worker::UID();
    //uid.raw_data = {m_key.keyByte[0], m_key.keyByte[1], m_key.keyByte[2], m_key.keyByte[3], m_key.keyByte[4], m_key.keyByte[5]};
    uid.raw_data = 
    {
        m_rfid.uid.uidByte[0], m_rfid.uid.uidByte[1], m_rfid.uid.uidByte[2], 
        m_rfid.uid.uidByte[3], m_rfid.uid.uidByte[4], m_rfid.uid.uidByte[5], 
        m_rfid.uid.uidByte[6], m_rfid.uid.uidByte[7], m_rfid.uid.uidByte[8], 
        m_rfid.uid.uidByte[9]
    };
    return uid;
}
