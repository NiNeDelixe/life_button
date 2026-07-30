#ifndef LED_STRIP_WORKER_HPP_
#define LED_STRIP_WORKER_HPP_

#include "core/core.hpp"

#include <tuple>

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#include "externals/IWorker.hpp"

namespace led_strip
{
    class Worker;

    struct Behavior
    {
        enum class Mode : uint8_t
        {
            STATIC,
            BLINK,
            FADE,
            PULSE,
            OFF
        };

        Mode mode = Mode::OFF;

        uint32_t color = 0xFFFFFF;   // RGB (0xRRGGBB)

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

        void setBrightness(uint8_t new_brightness)
        {
            uint8_t r = (color >> 16) & 0xFF;
            uint8_t g = (color >> 8) & 0xFF;
            uint8_t b = color & 0xFF;

            uint8_t old_v = std::max({r, g, b});
            if (old_v == 0)
            {
                r = g = b = new_brightness;
            }
            else
            {
                uint8_t scale = new_brightness / old_v;
                r = std::round(r * scale);
                g = std::round(g * scale);
                b = std::round(b * scale);
            }
            
            r = std::max((uint8_t)0, std::min((uint8_t)255, r));
            g = std::max((uint8_t)0, std::min((uint8_t)255, g));
            b = std::max((uint8_t)0, std::min((uint8_t)255, b));

            color = (r << 16) | (g << 8) | b;
        }
    };
}

static led_strip::Behavior _first_example = { led_strip::Behavior::Mode::STATIC };
static led_strip::Behavior _off_beh = { led_strip::Behavior::Mode::OFF };

class led_strip::Worker : public IWorker
{
    DECLARE_CLASS(Worker)

private:
    Worker();

public:
    ~Worker() = default;

    using leds_type = NeoPixelBus<NeoGrbFeature, NeoEsp32LcdX16Ws2812xMethod>;

public:
    void changeColor(int r, int g, int b);
    void changeColor(int address, int r, int g, int b); 
    void setBehavor(const Behavior& beh) { current_beh = beh; }

private:
    void updateBehavor();
    void fillPixels(const size_t& start_index, const size_t& step, const size_t& pixels_count, const RgbColor& color);

public:
    void update() override;

public:
    Behavior current_beh = {};

private:
    //CRGB leds[ESP_EXTERNAL_LED_STRIP_COUNT];
    leds_type leds = leds_type(ESP_EXTERNAL_LED_STRIP_COUNT, ESP_EXTERNAL_LED_STRIP_PIN);
    //NeoPixelAnimator animations = NeoPixelAnimator(PixelCount);
};

#endif  // LED_STRIP_WORKER_HPP_
