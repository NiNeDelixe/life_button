#include "externals/button/Worker.hpp"

button::Worker::Worker(callback_t on_press, callback_t on_release)
    : on_press(on_press), on_release(on_release)
{
    pinMode(ESP_EXTERNAL_BUTTON_PIN, INPUT_PULLUP);
    last_state = digitalRead(ESP_EXTERNAL_BUTTON_PIN);
}

button::Worker::Worker()
    : Worker(nullptr, nullptr)
{
}

void button::Worker::update()
{
    bool currentState = digitalRead(ESP_EXTERNAL_BUTTON_PIN);

    if (currentState != last_state) 
    {
        if (currentState == LOW) 
        {
            if (on_press) 
            {
                Serial.print("button pressed");
                is_pressed = true;
                is_released = false;
                on_press();
            }
        } 
        else 
        {
            if (on_release) 
            {
                Serial.print("button release");
                is_pressed = false;
                is_released = true;
                on_release();
            }
        }
        last_state = currentState;
    }
}