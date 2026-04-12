#include "externals/button/led/Worker.hpp"

button::led::Worker::Worker()
{
    pinMode(ESP_EXTERNAL_BUTTON_LED_PIN, OUTPUT);
    digitalWrite(ESP_EXTERNAL_BUTTON_LED_PIN, HIGH);
}

void button::led::Worker::update()
{
    if (!state)
    {
        digitalWrite(ESP_EXTERNAL_BUTTON_LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(ESP_EXTERNAL_BUTTON_LED_PIN, LOW);
    }
}

void button::led::Worker::setState(bool sate)
{
    this->state = state;
}

void button::led::Worker::changetState()
{
    this->state = !this->state;
}