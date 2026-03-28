#include "core/Polling.hpp"

void Polling::startUp()
{
    led_display_worker = led_display::Worker();
}

void Polling::poll()
{
    led_display_worker.poll();
}