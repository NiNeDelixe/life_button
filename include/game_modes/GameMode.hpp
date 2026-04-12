#ifndef GAME_MODES_GAMEMODE_HPP_
#define GAME_MODES_GAMEMODE_HPP_

#include "core/core.hpp"

enum class GameModeType : uint8_t
{
    BOMB,
    KOTH,
    LIFES,
    POINT
};

class GameMode
{
public:
    GameMode() = default;
    virtual ~GameMode() = default;

public:
    virtual void start() = 0;
    virtual void update() = 0;

private:
    
};

#endif  // GAME_MODES_GAMEMODE_HPP_
