#include "externals/led_strip/Worker.hpp"

#include "core/Polling.hpp"

led_strip::Worker::Worker()
{
    // FastLED.addLeds<
    //     ESP_EXTERNAL_LED_STRIP_TYPE, 
    //     ESP_EXTERNAL_LED_STRIP_PIN, 
    //     ESP_EXTERNAL_LED_STRIP_COLOR_ORDER
    // >(leds, ESP_EXTERNAL_LED_STRIP_COUNT);
    // FastLED.setBrightness(50);
}

void led_strip::Worker::changeColor(int r, int g, int b)
{
    //fill_solid(leds, ESP_EXTERNAL_LED_STRIP_COUNT, CRGB(r, g, b));
    current_beh.color = ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

void led_strip::Worker::changeColor(int address, int r, int g, int b)
{
    //fill_solid(leds + address, ESP_EXTERNAL_LED_STRIP_COUNT, CRGB(r, g, b));
    current_beh.start_index = address;
    changeColor(r, g, b);
}

void led_strip::Worker::updateBehavor()
{
    //FastLED.setBrightness(current_beh.brightness);

    switch (current_beh.mode)
    {
    case led_strip::Behavior::Mode::BLINK :
        break;
    
    case led_strip::Behavior::Mode::FADE :
        break;

    case led_strip::Behavior::Mode::OFF :
        //FastLED.show();
        break;

    case led_strip::Behavior::Mode::PULSE :
        break;

    case led_strip::Behavior::Mode::STATIC :
        //fl::fill_solid(leds + current_beh.start_index, ESP_EXTERNAL_LED_STRIP_COUNT, CRGB(current_beh.color));
        break;

    default:
        break;
    }

    //fl::globalBrightness();
}

void led_strip::Worker::update()
{
    //updateBehavor();
    //FastLED.show();
}