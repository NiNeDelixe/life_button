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
    leds.Begin();
    leds.Show();
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
    uint8_t r = (current_beh.color >> 16) & 0xFF;
    uint8_t g = (current_beh.color >> 8) & 0xFF;
    uint8_t b = current_beh.color & 0xFF;
    RgbColor rgbColor = RgbColor(r, g, b);

    switch (current_beh.mode)
    {
    case led_strip::Behavior::Mode::BLINK :
        break;
    
    case led_strip::Behavior::Mode::FADE :
        break;

    case led_strip::Behavior::Mode::OFF :
        fillPixels(current_beh.start_index, current_beh.step, ESP_EXTERNAL_LED_STRIP_COUNT, RgbColor(0));
        break;

    case led_strip::Behavior::Mode::PULSE :
        break;

    case led_strip::Behavior::Mode::STATIC :
    {
        fillPixels(current_beh.start_index, current_beh.step, ESP_EXTERNAL_LED_STRIP_COUNT, rgbColor);
        break;
    }
        

    default:
        break;
    }

    //fl::globalBrightness();
}

void led_strip::Worker::fillPixels(const size_t &start_index, const size_t& step, const size_t &pixels_count, const RgbColor &color)
{
    for (size_t i = start_index; i < pixels_count; i += step)
    {
        leds.SetPixelColor(i, color);
    }
    
}

void led_strip::Worker::update()
{
    updateBehavor();
    leds.Show();   
}