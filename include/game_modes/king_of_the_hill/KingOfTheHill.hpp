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
private:
    using uids_type = std::unordered_map<rfid::Worker::UID, esp_int_t, rfid::Worker::UIDHash>;

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
    bool updateEndGame();
    void updateSound();
    void updateRegistering();
    bool isHoldToStart();

    void changeConquestTeam();

public:
    void toggleRegistering();

    void startRegistering();

    void stopRegistering();

    void changeRegisterTeam();

    bool isRegistering() const
    {
        return m_register_mode;
    }

public:
    GameModeOptions* getOptions() override { return &options; };

public:
    KOTHOptions options;

private:
    //id card, id team
    uids_type m_uids;
    //std::unordered_map<rfid::Worker::UID, int> m_teams_colors;

    esp_int_t m_current_team;
    std::set<esp_int_t> m_teams;

    bool is_end_by_points;
    bool is_end_by_time;

    esp_time_t hold_time;

    bool m_register_mode = false;

    bool m_is_holding = false;
    bool m_is_started = false;
    rfid::Worker::UID m_hold_uid;
};

#endif  // KING_OF_THE_HILL_KINGOFTHEHILL_HPP_
