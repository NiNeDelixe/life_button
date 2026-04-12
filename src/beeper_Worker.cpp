#include "externals/beeper/Worker.hpp"

#include "core/Polling.hpp"

beeper::Worker::Worker()
{
    pinMode(ESP_EXTERNAL_BEEPER_PIN, OUTPUT);
    digitalWrite(ESP_EXTERNAL_BEEPER_PIN, LOW);
}

void beeper::Worker::changeWorkState(bool state)
{
    this->state = state;
}

void beeper::Worker::beepSeconds(esp_time_t time)
{
    m_time = time;
    start_time = millis();
    active = true;
    state = true;

    digitalWrite(ESP_EXTERNAL_BEEPER_PIN, BEEPER_DIGITAL_OUTPUT);
}

void beeper::Worker::singleBeep(esp_time_t time)
{
    beepSeconds(time);
}

void beeper::Worker::update()
{
    if (!active) 
        return;

    if (millis() - start_time >= m_time)
    {
        digitalWrite(ESP_EXTERNAL_BEEPER_PIN, LOW);
        state = false;
        active = false;
    }
}