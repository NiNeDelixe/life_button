#include "externals/led_bar/Worker.hpp"

led_bar::Worker::Worker()
{
    pinMode(ESP_EXTERNAL_LED_BAR_PIN, OUTPUT);
    digitalWrite(ESP_EXTERNAL_LED_BAR_PIN, LOW);
}

void led_bar::Worker::turnOn()
{
    state = true;
}

void led_bar::Worker::turnOff()
{
    state = false;
}

void led_bar::Worker::changeState()
{
    state = !state;
}

void led_bar::Worker::update() 
{
    if (state)
    {
        digitalWrite(ESP_EXTERNAL_LED_BAR_PIN, HIGH);
    }
    else
    {
        digitalWrite(ESP_EXTERNAL_LED_BAR_PIN, LOW);
    }
    
}