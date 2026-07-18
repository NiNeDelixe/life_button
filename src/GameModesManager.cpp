#include "game_modes/GameModesManager.hpp"

#include "game_modes/bomb/Bomb.hpp"
#include "game_modes/king_of_the_hill/KingOfTheHill.hpp"
#include "game_modes/lifes/Lifes.hpp"
#include "game_modes/point_farming/PointFarming.hpp"
#include "game_modes/sync_start/SyncStart.hpp"

GameModesManager::GameModesManager()
    : SaveManager(nullptr, 0)
{
    m_current_gamemode = nullptr;

    begin("game");

    uint8_t type = prefs.getUChar("gm_type", static_cast<uint8_t>(GameModeType::LIFES));

    crateGameMode(static_cast<GameModeType>(type));
}

GameModesManager::~GameModesManager()
{
    saveCurrent();

    if (m_current_gamemode)
    {
        delete m_current_gamemode;
        m_current_gamemode = nullptr;
    }

    end();
}

void GameModesManager::crateGameMode(const GameModeType &type)
{
    saveCurrent();

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
        m_current_gamemode = new KingOfTheHill();
        break;

    case GameModeType::SYNC_START :
        m_current_gamemode = new SyncStart();
        break;

    default:
        return;
    }

    if (m_current_gamemode)
    {
        loadCurrent();

        m_current_gamemode->start();
        m_current_gametype = type;

        saveCurrent();
    }
}

void GameModesManager::saveCurrent()
{
    if (!m_current_gamemode) return;

    prefs.putUChar("gm_type", static_cast<uint8_t>(m_current_gametype));

    auto* opts = m_current_gamemode->getOptions();
    if (opts)
        opts->save(prefs);

    forceSave("game");
}

void GameModesManager::loadCurrent()
{
    if (!m_current_gamemode) return;

    auto* opts = m_current_gamemode->getOptions();
    if (opts)
        opts->load(prefs);
}

void GameModesManager::update()
{
    if (m_current_gamemode)
    {
        m_current_gamemode->update();
    }
}