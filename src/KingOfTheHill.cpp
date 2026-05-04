#include "game_modes/king_of_the_hill/KingOfTheHill.hpp"

#include "core/Polling.hpp"

void KingOfTheHill::start()
{
    _button.setOnPress(nullptr);
    _button.setOnRelease(nullptr);

    _led_strip.changeColor(255, 255, 255);
    _led_bar.turnOn();
}

void KingOfTheHill::update()
{
}
