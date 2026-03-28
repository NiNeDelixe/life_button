#ifndef GAME_MODES_GAMEMODE_HPP_
#define GAME_MODES_GAMEMODE_HPP_

#include "core/core.hpp"

class GameMode
{
public:
    GameMode() = default;
    virtual ~GameMode() = default;

public:
    virtual void tick() = 0;

private:
    
};

#endif  // GAME_MODES_GAMEMODE_HPP_
