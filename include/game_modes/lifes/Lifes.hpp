#ifndef LIFES_LIFES_HPP_
#define LIFES_LIFES_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"
#include "game_modes/HasCounter.hpp"

#include "logic/counter/Counter.hpp"

#include "Options.hpp"

#include "externals/led_display/Worker.hpp"
#include "externals/button/Worker.hpp"
#include "externals/beeper/Worker.hpp"
#include "externals/button/led/Worker.hpp"



class Lifes : public GameMode, public HasCounter
{
public:
    Lifes() = default;
    ~Lifes() = default;

public:
    void start() override;
    void update() override;

private:
    static void onPress();
    static void onRelease();


public:

private:
    static LifesOptions options; //May was nonstatic
    button::Worker buton = button::Worker(nullptr, nullptr);

    bool is_dead = false;
    bool is_beep = false;
};

#endif  // LIFES_LIFES_HPP_
