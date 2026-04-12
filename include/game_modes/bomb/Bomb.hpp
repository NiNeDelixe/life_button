#ifndef BOMB_BOMB_HPP_
#define BOMB_BOMB_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

#include "game_modes/bomb/Options.hpp"

class Bomb : public GameMode
{
public:
    Bomb() = default;
    ~Bomb() = default;

public:
    void start() override;
    void update() override;

public:
    static void onPress();
    static void onRelease();

private:
    BombOptions options;
    esp_time_t current_plant_time = 0;
    esp_time_t current_timer = 0;
    esp_time_t current_defusing_time = 0;

    bool planted = false;
    bool explode = false;
    bool defused = false;
};

#endif  // BOMB_BOMB_HPP_
