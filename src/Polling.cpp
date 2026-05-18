#include "core/Polling.hpp"

GameModesManager Polling::mode_manager = {};

void Polling::startUp()
{
    web::BoardsSync::getInstance().onStart();
    led_bar::Worker::getInstance().turnOn();
    beeper::Worker::getInstance().singleBeep();
    led_circuit::Worker::getInstance().singleRun();
    web::WebInterface::getInstance().onStart();
    led_display::Worker::getInstance().clear();
    
    //mode_manager.crateGameMode(GameModeType::LIFES);
    led_bar::Worker::getInstance().turnOff();
}

void Polling::poll()
{
    web::BoardsSync::getInstance().update();
    web::WebInterface::getInstance().update();
    led_circuit::Worker::getInstance().update();
    button::led::Worker::getInstance().update();
    beeper::Worker::getInstance().update();
    led_bar::Worker::getInstance().update();
    led_strip::Worker::getInstance().update();
    button::Worker::getInstance().update();
    
    mode_manager.update();
}

void Polling::delay(esp_time_t time)
{
    vTaskDelay(time / portTICK_PERIOD_MS);
    //millis(time);
}