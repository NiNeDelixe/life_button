#ifndef CORE_STARTUP_HPP_
#define CORE_STARTUP_HPP_

#include "core.hpp"

#include "game_modes/lifes/Lifes.hpp"

class Polling
{
public:
    Polling() = default;
    ~Polling() = delete;

public:
    static void startUp();
    static void poll();

    static void delay(esp_time_t time);

private:
    static Lifes lifes;
};

#endif  // CORE_STARTUP_HPP_
