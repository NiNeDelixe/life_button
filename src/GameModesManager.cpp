#include "game_modes/GameModesManager.hpp"

#include "game_modes/bomb/Bomb.hpp"
//#include "game_modes/king_of_the_hill/"
#include "game_modes/lifes/Lifes.hpp"
#include "game_modes/point_farming/PointFarming.hpp"

GameModesManager::GameModesManager()
{
    m_max_active_gamemodes = 4;
    m_count_active_gamemodes = 0;
    m_active_gamemodes = new GameMode*[m_max_active_gamemodes]{};
    m_current_gamemode = nullptr;
}

GameModesManager::~GameModesManager()
{
    if (m_active_gamemodes)
    {
        for (size_t i = 0; i < m_count_active_gamemodes; i++)
        {
            if (m_active_gamemodes[i])
            {
                delete m_active_gamemodes[i];
            }
        }
        delete[] m_active_gamemodes;
    }
    
    if (m_current_gamemode)
    {
        delete m_current_gamemode;
    }
}

void GameModesManager::crateGameMode(const GameModeType &type)
{
    if (m_current_gamemode)
    {
        delete m_current_gamemode;
    }
    
    crateGameMode(m_current_gamemode, type);
}

void GameModesManager::crateGameMode(GameMode *null_out_gamemode, const GameModeType &type)
{
    GameMode * new_gm;
    switch (type)
    {
    case GameModeType::BOMB :
        new_gm = new Bomb();
        break;

    case GameModeType::KOTH :
        //FIXME: Not implemented
        break;
    
    case GameModeType::LIFES :
        new_gm = new Lifes();
        break;

    case GameModeType::POINT :
        new_gm = new PointFarming();
        break;

    default:
        break;
    }

    if (new_gm)
    {
        new_gm->start();

        push_back(new_gm);

        null_out_gamemode = new_gm;
    }
}

void GameModesManager::push_back(GameMode *gamemode)
{
    if (m_count_active_gamemodes >= m_max_active_gamemodes)
    {
        size_t new_cap = m_max_active_gamemodes * 2;
        GameMode** new_arr = new GameMode*[new_cap]{};

        for (size_t i = 0; i < m_count_active_gamemodes; i++)
        {
            new_arr[i] = m_active_gamemodes[i];
        }

        delete[] m_active_gamemodes;
        m_active_gamemodes = new_arr;
        m_max_active_gamemodes = new_cap;
    }

    m_active_gamemodes[m_count_active_gamemodes++] = gamemode;
}
