#ifndef CORE_STARTUP_HPP_
#define CORE_STARTUP_HPP_

#include "core.hpp"

#include "externals/led_display/Worker.hpp"

class Polling
{
public:
    Polling() = default;
    ~Polling() = delete;

public:
    static void startUp();
    static void poll();

private:
    static led_display::Worker led_display_worker;
};

#endif  // CORE_STARTUP_HPP_
