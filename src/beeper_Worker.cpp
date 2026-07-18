#include "externals/beeper/Worker.hpp"
#include "driver/rtc_io.h"
#include "core/Polling.hpp"

beeper::Worker::Worker()
{
    // gpio_set_level((gpio_num_t)ESP_EXTERNAL_BEEPER_PIN, BEEPER_DIGITAL_OFF_OUTPUT);
    // gpio_set_direction((gpio_num_t)ESP_EXTERNAL_BEEPER_PIN, GPIO_MODE_OUTPUT);
    //gpio_set_direction((gpio_num_t)ESP_EXTERNAL_BEEPER_PIN, GPIO_MODE_OUTPUT);
    //gpio_set_pull_mode((gpio_num_t)ESP_EXTERNAL_BEEPER_PIN, gpio_pull_mode_t::GPIO_PULLUP_ONLY);

    // pinMode(ESP_EXTERNAL_BEEPER_PIN, OUTPUT);
    // rtc_gpio_pullup_dis((gpio_num_t)ESP_EXTERNAL_BEEPER_PIN);
    // rtc_gpio_pulldown_en((gpio_num_t)ESP_EXTERNAL_BEEPER_PIN);

    pinMode(ESP_EXTERNAL_BEEPER_PIN, OUTPUT);
    digitalWrite(ESP_EXTERNAL_BEEPER_PIN, BEEPER_DIGITAL_OFF_OUTPUT);
}

void beeper::Worker::changeWorkState(bool state)
{
    this->state = state;
    if (!state) {
        digitalWrite(ESP_EXTERNAL_BEEPER_PIN, BEEPER_DIGITAL_OFF_OUTPUT);
        active = false;
    }
}

void beeper::Worker::beepSeconds(esp_time_t time)
{
    if (time == 0) return;

    if (active)
    {
        return;
    }
    

    m_time = time;
    start_time = millis();
    active = true;
    state = true;

    digitalWrite(ESP_EXTERNAL_BEEPER_PIN, BEEPER_DIGITAL_ON_OUTPUT);
}

void beeper::Worker::singleBeep(esp_time_t time)
{
    const uint32_t now = millis();
    if (active)
    {
        return;
    }

    if ((now - last_single_beep_request_time) < time)
    {
        return;
    }

    last_single_beep_request_time = now;
    beepSeconds(time);
}

void beeper::Worker::update()
{
    if (!active) 
        return;

    if ((millis() - start_time) >= m_time)
    {
        digitalWrite(ESP_EXTERNAL_BEEPER_PIN, BEEPER_DIGITAL_OFF_OUTPUT);
        state = false;
        active = false;
    }
}