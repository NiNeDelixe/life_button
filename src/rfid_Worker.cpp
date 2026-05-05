#include "externals/rfid/Worker.hpp"

#include "core/Polling.hpp"

rfid::Worker::Worker()
{
    //SPI.begin(ESP_EXTERNAL_RFID_SPI_SCK_PIN, ESP_EXTERNAL_RFID_SPI_MISO_PIN, ESP_EXTERNAL_RFID_SPI_MOSI_PIN, ESP_EXTERNAL_RFID_SS_PIN);
    // m_rfid.PCD_Init(); 
    // m_rfid.PCD_SetAntennaGain(m_rfid.RxGain_max);
    // m_rfid.PCD_AntennaOff(); 
    // m_rfid.PCD_AntennaOn();

    for (byte i = 0; i < 6; ++i) 
    {
        m_key.keyByte[i] = 0xFF; // 0xFFFFFFFFFFFF
    }
}

void rfid::Worker::update()
{
    // if (!m_rfid.PICC_IsNewCardPresent()) 
    // {
    //     tag_detected = false;
    //     return;
    // }
    // if (!m_rfid.PICC_ReadCardSerial()) 
    //     return;

    tag_detected = true;

    led_circuit::Worker::getInstance().singleRun();
}

bool rfid::Worker::tagDetected()
{
    return tag_detected;
}
