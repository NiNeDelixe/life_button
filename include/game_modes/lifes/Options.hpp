#ifndef LIFES_OPTIONS_HPP_
#define LIFES_OPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

#include "game_modes/GameModeOptions.hpp"

#include "logic/saving/ISaveble.hpp"

struct LifesOptions : public GameModeOptions
{
    TimeOption timer_option = TimeOption(4294967294);
    IntOption lifes_option = IntOption(70);

    void save(Preferences& prefs) const override
    {
        prefs.putInt("lf_lifes", lifes_option.get());
        prefs.putInt("lf_timer", timer_option.get());
    }

    void load(Preferences& prefs) override
    {
        lifes_option = prefs.getInt("lf_lifes", 70);
        timer_option = prefs.getInt("lf_timer", 4294967294);
    }
};

#endif  // LIFES_OPTIONS_HPP_
