#ifndef KING_OF_THE_HILL_KINGOFTHEHILL_HPP_
#define KING_OF_THE_HILL_KINGOFTHEHILL_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

#include "game_modes/king_of_the_hill/Options.hpp"

#include "game_modes/HasCounter.hpp"
#include "game_modes/HasTimer.hpp"

#include "externals/rfid/Worker.hpp"

#include <unordered_map>
#include <set>

class KingOfTheHill : public GameMode, public HasCounter, public HasTimer
{
public:
    KingOfTheHill() = default;
    ~KingOfTheHill();

    void start() override;
    void update() override;

    void registerCards();
    int registerTeam();

    void updatePoints();
    void updateConquestTeam();
    void updateTimer();
    void updateEndGame();
    void updateSound();

    void changeConquestTeam();

public:
    GameModeOptions* getOptions() override { return &options; };

public:
    KOTHOptions options;

private:
    std::unordered_map<rfid::Worker::UID, int, rfid::Worker::UIDHash> m_uids;
    //std::unordered_map<rfid::Worker::UID, int> m_teams_colors;

    int m_current_team;
    std::set<int> m_teams;

    bool is_end_by_points;
    bool is_end_by_time;

    esp_time_t hold_time;
};

#endif  // KING_OF_THE_HILL_KINGOFTHEHILL_HPP_
