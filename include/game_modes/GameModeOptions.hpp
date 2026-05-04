#ifndef GAME_MODES_GAMEMODEOPTIONS_HPP_
#define GAME_MODES_GAMEMODEOPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

#include "logic/saving/ISaveble.hpp"

class GameModeOptions : public ISaveble
{
public:
    GameModeOptions() = default;
    virtual ~GameModeOptions() = default;

private:
    
};

#endif  // GAME_MODES_GAMEMODEOPTIONS_HPP_
