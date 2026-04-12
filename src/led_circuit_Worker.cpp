#include "externals/led_circuit/Worker.hpp"
#include "core/Polling.hpp"

led_circuit::Worker::Worker()
{
    pinMode(ESP_CIRCUIT_BLUE_LED_PIN, OUTPUT);
    digitalWrite(ESP_CIRCUIT_BLUE_LED_PIN, HIGH);
}

void led_circuit::Worker::update()
{
    if (!active) 
        return;

    if (millis() - start_time >= m_time)
    {
        digitalWrite(ESP_CIRCUIT_BLUE_LED_PIN, HIGH);
        state = false;
        active = false;
    }
}

void led_circuit::Worker::timeRun(esp_time_t time)
{
    m_time = time;
    start_time = millis();
    active = true;
    state = true;

    digitalWrite(ESP_CIRCUIT_BLUE_LED_PIN, LOW);
}

void led_circuit::Worker::singleRun(esp_time_t time)
{
    timeRun(time);
}