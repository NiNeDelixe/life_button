#ifndef BOMB_OPTIONS_HPP_
#define BOMB_OPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

#include "game_modes/GameModeOptions.hpp"

#include "logic/saving/ISaveble.hpp"

struct BombOptions : public GameModeOptions
{
    TimeOption timer_option = TimeOption(45000);
    TimeOption defuse_option = TimeOption(10000);
    TimeOption plant_option = TimeOption(3200);

    void save(Preferences& prefs) const override
    {
        prefs.putInt("bm_timer", timer_option.get());
        prefs.putInt("bm_defuse", defuse_option.get());
        prefs.putInt("bm_plant", plant_option.get());
    }

    void load(Preferences& prefs) override
    {
        timer_option = prefs.getInt("bm_timer", 45000);
        defuse_option = prefs.getInt("bm_defuse", 10000);
        plant_option = prefs.getInt("bm_plant", 3200);
    }
};


#endif  // BOMB_OPTIONS_HPP_
