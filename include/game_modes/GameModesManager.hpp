#ifndef GAME_MODES_GAME_MODES_MANAGER_HPP_
#define GAME_MODES_GAME_MODES_MANAGER_HPP_

#include "core/core.hpp"
#include "game_modes/GameMode.hpp"

#include "logic/saving/Saveing.hpp"

#include "externals/led_bar/Worker.hpp"

class GameModesManager : public SaveManager
{
public:
    GameModesManager();
    ~GameModesManager();

public:
    void crateGameMode(const GameModeType& type);
    void createSavedGamemode();

    void setGameMode(GameMode* gamemode) { m_current_gamemode = gamemode; }
    GameMode* getCurrentGameMode() { return m_current_gamemode; }
    GameModeType getCurrentGameType() { return m_current_gametype; }

    void defaultSetupGamemode();

    void saveCurrent();

    void loadCurrent();

    void update();

public:
    GameMode* m_current_gamemode = nullptr;
    GameModeType m_current_gametype = GameModeType::BOMB;
};

#endif // GAME_MODES_GAME_MODES_MANAGER_HPP_
