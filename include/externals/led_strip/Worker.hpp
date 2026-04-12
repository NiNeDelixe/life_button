#ifndef LED_STRIP_WORKER_HPP_
#define LED_STRIP_WORKER_HPP_

#include "core/core.hpp"

//#include <FastLED.h>

#include "externals/IWorker.hpp"

namespace led_strip
{
    class Worker;

    struct Behavior
    {
        enum class Mode : uint8_t
        {
            STATIC,     // постоянный свет
            BLINK,      // мигание
            FADE,       // плавное затухание/нарастание
            PULSE,      // пульсация
            OFF
        };

        Mode mode = Mode::OFF;

        uint32_t color = 0xFFFFFF;   // RGB (0xRRGGBB)
        uint8_t brightness = 50;    // 0-255

        uint16_t start_index = 0; // с какого светодиода начинать
        uint16_t count = 0;       // сколько светодиодов задействовано (0 = все)
        uint8_t step = 1;         // шаг (1 = каждый, 2 = через один, 3 = через два и т.д.)

        union
        {
            struct
            {
                uint16_t on_time_ms;
                uint16_t off_time_ms;
            } blink;

            struct
            {
                uint16_t fade_in_ms;
                uint16_t fade_out_ms;
            } fade;

            struct
            {
                uint16_t period_ms;
            } pulse;
        };

        bool loop = true;
    };
}

static led_strip::Behavior _first_example = {};

class led_strip::Worker : public IWorker
{
public:
    Worker();
    ~Worker() = default;

public:
    void changeColor(int r, int g, int b);
    void changeColor(int address, int r, int g, int b); 
    void setBehavor(const Behavior& beh) { current_beh = beh; }

private:
    void updateBehavor();

public:
    void update() override;

public:
    Behavior current_beh = {};

private:
    //CRGB leds[ESP_EXTERNAL_LED_STRIP_COUNT];
};

static led_strip::Worker _led_strip = {};

#endif  // LED_STRIP_WORKER_HPP_
