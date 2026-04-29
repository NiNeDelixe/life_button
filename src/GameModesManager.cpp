#include "game_modes/GameModesManager.hpp"

#include "game_modes/bomb/Bomb.hpp"
//#include "game_modes/king_of_the_hill/"
#include "game_modes/lifes/Lifes.hpp"
#include "game_modes/point_farming/PointFarming.hpp"

GameModesManager::GameModesManager()
{
    m_current_gamemode = nullptr;
}

GameModesManager::~GameModesManager()
{
    if (m_current_gamemode)
    {
        delete m_current_gamemode;
        m_current_gamemode = nullptr;
    }
}

void GameModesManager::crateGameMode(const GameModeType &type)
{
    if (m_current_gamemode)
    {
        delete m_current_gamemode;
        m_current_gamemode = nullptr;
    }

    switch (type)
    {
    case GameModeType::BOMB:
        m_current_gamemode = new Bomb();
        break;

    case GameModeType::LIFES:
        m_current_gamemode = new Lifes();
        break;

    case GameModeType::POINT:
        m_current_gamemode = new PointFarming();
        break;

    case GameModeType::KOTH:
        // не реализовано
        break;

    default:
        return;
    }

    if (m_current_gamemode)
    {
        m_current_gamemode->start();
        m_current_gametype = type;
    }
}

void GameModesManager::update()
{
    if (m_current_gamemode)
    {
        m_current_gamemode->update();
    }
}