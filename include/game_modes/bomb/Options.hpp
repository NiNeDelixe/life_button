#ifndef BOMB_OPTIONS_HPP_
#define BOMB_OPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

#include "game_modes/GameModeOptions.hpp"

struct BombOptions : public GameModeOptions
{
    TimeOption timer_option = TimeOption(45000);
    TimeOption defuse_option = TimeOption(10000);
    TimeOption plant_option = TimeOption(3200);
};


#endif  // BOMB_OPTIONS_HPP_
