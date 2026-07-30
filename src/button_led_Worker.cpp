#include "externals/button/led/Worker.hpp"

button::led::Worker::Worker()
{
    pinMode(ESP_EXTERNAL_BUTTON_LED_PIN, OUTPUT);
    digitalWrite(ESP_EXTERNAL_BUTTON_LED_PIN, HIGH);
}

void button::led::Worker::update()
{
    if (!turn_state)
    {
        digitalWrite(ESP_EXTERNAL_BUTTON_LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(ESP_EXTERNAL_BUTTON_LED_PIN, LOW);
    }
}
