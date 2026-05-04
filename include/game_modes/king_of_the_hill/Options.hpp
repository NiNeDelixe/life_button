#ifndef KING_OF_THE_HILL_OPTIONS_HPP_
#define KING_OF_THE_HILL_OPTIONS_HPP_

#include "game_modes/GameModeOptions.hpp"

struct KOTHOptions : public GameModeOptions
{


    void save(Preferences& prefs) const override
    {
        // prefs.putInt("koth_lifes", lifes_option.get());
        // prefs.putInt("koth_timer", timer_option.get());
    }

    void load(Preferences& prefs) override
    {
        // lifes_option = prefs.getInt("koth_lifes", 70);
        // timer_option = prefs.getInt("koth_timer", 0);
    }
};


#endif  // KING_OF_THE_HILL_OPTIONS_HPP_
