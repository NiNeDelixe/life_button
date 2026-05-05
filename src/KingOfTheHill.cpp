#include "game_modes/king_of_the_hill/KingOfTheHill.hpp"

#include "core/Polling.hpp"

void KingOfTheHill::start()
{
    button::Worker::getInstance().setOnPress(nullptr);
    button::Worker::getInstance().setOnRelease(nullptr);

    led_strip::Worker::getInstance().changeColor(255, 255, 255); //white
    led_bar::Worker::getInstance().turnOn();
}

void KingOfTheHill::update()
{
}
