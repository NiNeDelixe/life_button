#ifndef DATA_STRUCT_GAMEMODESSTRUCT_HPP_
#define DATA_STRUCT_GAMEMODESSTRUCT_HPP_

#include "game_modes/GameMode.hpp"
#include "game_modes/GameModeOptions.hpp"

struct GameModesStruct
{
    GameModeType type;
    GameModeOptions* options;
};


#endif  // DATA_STRUCT_GAMEMODESSTRUCT_HPP_
