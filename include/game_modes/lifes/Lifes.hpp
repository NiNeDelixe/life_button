#ifndef LIFES_LIFES_HPP_
#define LIFES_LIFES_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

#include "logic/counter/Counter.hpp"

#include "Options.hpp"

#include "externals/led_display/Worker.hpp"
#include "externals/button/Worker.hpp"

enum class operators
{
    ADD,
    DIV,
    SET
};

class Lifes : public GameMode
{
public:
    Lifes() = default;
    ~Lifes() = default;

public:
    void start() override;
    void update() override;

private:
#ifdef USE_STL_CODE
    void onPress();
    void onRelease();
#else
    static void onPress();
    static void onRelease();
#endif


public:
#ifdef USE_STL_CODE
    void applyToCounter(int num, const operators& oper);
#else
    static void applyToCounter(int num, const operators& oper);
#endif

private:
#ifdef USE_STL_CODE
    Counter lifes_counter;
    LifesOptions options;
#else
    static Counter lifes_counter;
    static LifesOptions options;
#endif

    led_display::Worker led_display_worker;
    button::Worker button_worker = button::Worker(nullptr, nullptr);
};

#endif  // LIFES_LIFES_HPP_
