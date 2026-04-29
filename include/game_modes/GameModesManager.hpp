#ifndef GAME_MODES_GAMEMODESMANAGER_HPP_
#define GAME_MODES_GAMEMODESMANAGER_HPP_

#include "core/core.hpp"
#include "game_modes/GameMode.hpp"

class GameModesManager
{
public:
    GameModesManager();
    ~GameModesManager();

public:
    void crateGameMode(const GameModeType& type);

    void setGameMode(GameMode* gamemode) { m_current_gamemode = gamemode; }
    GameMode* getCurrentGameMode() { return m_current_gamemode; }

    void update();

public:
    GameMode* m_current_gamemode = nullptr;
    GameModeType m_current_gametype = GameModeType::BOMB;
};

#endif