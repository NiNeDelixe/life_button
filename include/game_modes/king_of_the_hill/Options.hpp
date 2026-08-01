#ifndef KING_OF_THE_HILL_OPTIONS_HPP_
#define KING_OF_THE_HILL_OPTIONS_HPP_

#include "game_modes/GameModeOptions.hpp"

using RGBColorOption = StaticArrayOption<int, 3>;

struct RegisterTeam
{
    String name;
    uint32_t color;
    std::vector<String> cards;
};

struct KOTHOptions : public GameModeOptions
{
    // ArrayOption<RGBColorOption> team_color = {{ 255, 255, 255 }}; 
    ArrayOption<int> team_color = {}; 
    TimeOption hold_time = { TIME_S(5) };
    TimeOption game_time = { esp_time_t_max_value };
    IntOption points_to_win = { 10000 };
    IntOption points_multiplier = { 1 };

    FlagOption is_need_to_hold_button = { false };

    //Option in develop
    //points add passive for teams who dont conquest flag
    FlagOption is_flag_rot; 


    void save(Preferences& prefs) const override
    {
        prefs.putInt("koth_hold_time", hold_time.get());
        prefs.putInt("koth_game_time", game_time.get());
        prefs.putInt("koth_points_to_win", points_to_win.get());
        prefs.putInt("koth_points_multiplier", points_multiplier.get());
        prefs.putBool("koth_is_need_to_hold_button", is_need_to_hold_button.get());
    }

    void load(Preferences& prefs) override
    {
        hold_time = prefs.getInt("koth_hold_time", TIME_S(5));
        game_time = prefs.getInt("koth_game_time", esp_time_t_max_value);
        points_to_win = prefs.getInt("koth_points_to_win", 10000);
        points_multiplier = prefs.getInt("koth_points_multiplier", 5);
        is_need_to_hold_button = prefs.getBool("koth_is_need_to_hold_button", false);
    }
};


#endif  // KING_OF_THE_HILL_OPTIONS_HPP_
