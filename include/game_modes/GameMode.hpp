#ifndef GAME_MODES_GAMEMODE_HPP_
#define GAME_MODES_GAMEMODE_HPP_

#include "core/core.hpp"

#include "game_modes/GameModeOptions.hpp"

enum class GameModeType : uint8_t
{
    BOMB,
    KOTH,
    LIFES,
    POINT,
    SYNC_START
};

inline const char* to_string(GameModeType v)
{
    switch (v)
    {
        case GameModeType::BOMB:   return "Bomb";
        case GameModeType::KOTH:   return "King of the hill";
        case GameModeType::LIFES: return "Lifes";
        case GameModeType::POINT: return "Point farming";
        case GameModeType::SYNC_START: return "Sync start";
        default:      return "[Unknown GameModeType]";
    }
}

class GameMode
{
public:
    GameMode() = default;
    virtual ~GameMode() = default;

public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual GameModeOptions* getOptions() { return nullptr; };

private:
    
};

#endif  // GAME_MODES_GAMEMODE_HPP_
