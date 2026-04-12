#ifndef LED_DISPLAY_WORKER_HPP_
#define LED_DISPLAY_WORKER_HPP_

#include "core/core.hpp"

#include <TM1637Display.h>

#include "utils/String.hpp"

namespace led_display
{
    class Worker;
}

class led_display::Worker
{
public:
    Worker();
    ~Worker() = default;

public:
    void setText(const char* text, size_t length = 0);
    void setNumber(int num);
    void clear();

private:
    TM1637Display display;

    uint8_t blank[4] = { 0x00, 0x00, 0x00, 0x00 };
};

static led_display::Worker _led_display = {};

#endif  // LED_DISPLAY_WORKER_HPP_
