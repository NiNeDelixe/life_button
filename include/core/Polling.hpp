#ifndef CORE_POLLING_HPP_
#define CORE_POLLING_HPP_

#include "core.hpp"

#include <GTimer.h>

#include "game_modes/GameModesManager.hpp"
#include "game_modes/lifes/Lifes.hpp"
#include "game_modes/bomb/Bomb.hpp"
#include "game_modes/king_of_the_hill/KingOfTheHill.hpp"

#include "externals/beeper/Worker.hpp"
#include "externals/button/led/Worker.hpp"
#include "externals/button/Worker.hpp"
#include "externals/led_bar/Worker.hpp"
#include "externals/led_strip/Worker.hpp"
#include "externals/led_display/Worker.hpp"
#include "externals/rfid/Worker.hpp"
#include "externals/lora/Worker.hpp"

#include "logic/saving/Saveing.hpp"

#include "web/WebInterface.hpp"
#include "web/BoardsSync.hpp"

#include "utils/Delay.hpp"

class Updatable;

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
    friend class Updatable;

    static std::vector<Updatable*>& objects() {
        static std::vector<Updatable*> objs;
        return objs;
    }

    static std::mutex& mutex() {
        static std::mutex m;
        return m;
    }
    static void registerObject(Updatable* const obj) {
        std::lock_guard<std::mutex> lock(mutex());
        objects().push_back(obj);
    }

    static void unregisterObject(Updatable* const obj) {
        std::lock_guard<std::mutex> lock(mutex());
        auto& objs = objects();
        objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
    }

public:
    static GameModesManager mode_manager;
};

#endif  // CORE_POLLING_HPP_
