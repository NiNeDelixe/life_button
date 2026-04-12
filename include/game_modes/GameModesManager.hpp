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
    /// @brief create and set gamemode
    /// @param type enum type of gamemodes
    void crateGameMode(const GameModeType& type);

    /// @brief create and get without set gamemode
    /// @param null_out_gamemode out variable
    /// @param type enume type of gamemodes
    void crateGameMode(GameMode* null_out_gamemode, const GameModeType& type);

    void setGameMode(GameMode* gamemode) { m_current_gamemode = gamemode; };

    GameMode* getCurrentGameMode() { return m_current_gamemode; } //FIXME: bruh

    void update() 
    {
        for (size_t i = 0; i < m_count_active_gamemodes; i++)
        {
            if (m_active_gamemodes[i])
            {
                m_active_gamemodes[i]->update();
            }
        }
        
    }

    void push_back(GameMode* gamemode);

public: //TEMP
    GameMode* m_current_gamemode = nullptr;
    GameMode** m_active_gamemodes;
    size_t m_count_active_gamemodes;
    size_t m_max_active_gamemodes;
};

#endif  // GAME_MODES_GAMEMODESMANAGER_HPP_
