#include "externals/lora/Worker.hpp"

namespace lora {

Worker::Worker()
{
    pinMode(ESP_EXTERNAL_LORA_M0_PIN, OUTPUT);
    pinMode(ESP_EXTERNAL_LORA_M1_PIN, OUTPUT);
    pinMode(ESP_EXTERNAL_LORA_AUX_PIN, INPUT);

    digitalWrite(ESP_EXTERNAL_LORA_M0_PIN, LOW);
    digitalWrite(ESP_EXTERNAL_LORA_M1_PIN, LOW);

    LoRaSerial.begin(9600, SERIAL_8N1,
        ESP_EXTERNAL_LORA_RX_PIN,
        ESP_EXTERNAL_LORA_TX_PIN);

    waitForAuxReady();
}

Worker::~Worker()
{
    LoRaSerial.end();
}

void Worker::update()
{
    processReceivedData();
}

void Worker::sendAllMessages()
{
    for (auto* syncable : m_classes)
    {
        send(syncable, 0xFFFF);
    }
}

void Worker::addISyncableClass(ISyncable* class_to_add)
{
    if (class_to_add != nullptr)
    {
        m_classes.push_back(class_to_add);
    }
}

bool Worker::send(ISyncable* syncable, uint16_t address)
{
    if (!syncable)
        return false;

    return send(address,
        [&](HardwareSerial& serial)
        {
            ISyncable::Data data = syncable->onSend();

            if (!data.data)
                return false;

            serial.write(data.data, data.size);

            return true;
        });
}

bool Worker::send(uint16_t address, const SendCallback& callback)
{
    // if (!callback)
    //     return false;

    // if (!setMode(HIGH, LOW))
    //     return false;

    // const uint8_t header[]
    // {
    //     static_cast<uint8_t>(address >> 8),
    //     static_cast<uint8_t>(address)
    // };

    // LoRaSerial.write(header, sizeof(header));

    // if (!callback(LoRaSerial))
    // {
    //     setMode(LOW, LOW);
    //     return false;
    // }

    // LoRaSerial.flush();

    // if (!waitForAuxReady())
    // {
    //     setMode(LOW, LOW);
    //     return false;
    // }

    // setMode(LOW, LOW);
    // return true;

    if (!callback)
        return false;

    return callback(LoRaSerial);
}

void Worker::processReceivedData()
{
    // if (LoRaSerial.available() < 3)
    //     return;

    // uint8_t header[2];

    // LoRaSerial.readBytes(header, 2);

    // uint16_t sender_address = (header[0] << 8) | header[1];

    // if (m_targetAddress != 0xFFFF &&
    //     sender_address != m_targetAddress)
    // {
    //     while (LoRaSerial.available())
    //         LoRaSerial.read();

    //     return;
    // }

    // size_t size = LoRaSerial.available();

    // if (size == 0)
    //     return;

    // std::vector<uint8_t> buffer(size);

    // size_t read = LoRaSerial.readBytes(
    //     buffer.data(),
    //     buffer.size()
    // );

    // ISyncable::Data data
    // {
    //     buffer.data(),
    //     read
    // };

    // if (m_receiveCallback)
    //     m_receiveCallback(data, sender_address);

    // for (auto* syncable : m_classes)
    // {
    //     if (syncable)
    //         syncable->onRecive(data);
    // }

    if (!LoRaSerial.available())
        return;

    std::vector<uint8_t> buffer;

    size_t read = LoRaSerial.readBytes(
        buffer.data(),
        buffer.size()
    );

    ISyncable::Data data
    {
        buffer.data(),
        read
    };

    while (LoRaSerial.available())
        buffer.push_back(LoRaSerial.read());

    if (m_receiveCallback)
        m_receiveCallback(data, 0);

    for (auto* syncable : m_classes)
        if (syncable)
            syncable->onRecive(data);
}

bool Worker::setMode(uint8_t m0, uint8_t m1)
{
    digitalWrite(ESP_EXTERNAL_LORA_M0_PIN, m0);
    digitalWrite(ESP_EXTERNAL_LORA_M1_PIN, m1);

    delay(10);

    return waitForAuxReady();
}

bool Worker::waitForAuxReady(unsigned long timeout)
{
    const unsigned long start = millis();

    while (digitalRead(ESP_EXTERNAL_LORA_AUX_PIN) == LOW)
    {
        if (millis() - start >= timeout)
            return false;

        delay(1);
    }

    return true;
}

void Worker::setReceiveCallback(ReceiveCallback callback)
{
    m_receiveCallback = callback;
}

void Worker::setTargetAddress(uint16_t address)
{
    m_targetAddress = address;
}

uint16_t Worker::getTargetAddress() const
{
    return m_targetAddress;
}

} // namespace lora