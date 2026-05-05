#ifndef KING_OF_THE_HILL_OPTIONS_HPP_
#define KING_OF_THE_HILL_OPTIONS_HPP_

#include "game_modes/GameModeOptions.hpp"

using RGBColorOption = StaticArrayOption<int, 3>;

struct KOTHOptions : public GameModeOptions
{
    // ArrayOption<RGBColorOption> team_color = {{ 255, 255, 255 }}; 
    ArrayOption<int> team_color = {}; 
    TimeOption hold_time = { TIME_S(5) };
    TimeOption game_time = { esp_time_t_max_value };
    IntOption points_to_win = { 10000 };
    IntOption points_multiplier = { 5 };

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
