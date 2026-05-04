#ifndef CORE_POLLING_HPP_
#define CORE_POLLING_HPP_

#include "core.hpp"

#include <GTimer.h>

#include "game_modes/GameModesManager.hpp"
#include "game_modes/lifes/Lifes.hpp"
#include "game_modes/bomb/Bomb.hpp"

#include "externals/beeper/Worker.hpp"
#include "externals/button/led/Worker.hpp"
#include "externals/button/Worker.hpp"
#include "externals/led_bar/Worker.hpp"
#include "externals/led_strip/Worker.hpp"
#include "externals/led_display/Worker.hpp"

#include "logic/saving/Saveing.hpp"

#include "web/WebInterface.hpp"


class Polling
{
public:
    Polling() = default;
    ~Polling() = delete;

public:
    static void startUp();
    static void poll();

    static void delay(esp_time_t time);

public:
    static GameModesManager mode_manager;
};

#endif  // CORE_POLLING_HPP_
