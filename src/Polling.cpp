#include "core/Polling.hpp"

GameModesManager Polling::mode_manager = {};

void Polling::startUp()
{
    _led_bar.turnOn();
    _beeper.singleBeep();
    _led_circuit.singleRun();
    _interface.onStart();
    _led_bar.turnOff();
    _led_display.clear();

    //mode_manager.crateGameMode(GameModeType::LIFES);
}

void Polling::poll()
{
    _interface.update();
    _led_circuit.update();
    _button_led.update();
    _beeper.update();
    _led_bar.update();
    _led_strip.update();
    _button.update();
    
    mode_manager.update();
}

void Polling::delay(esp_time_t time)
{
    vTaskDelay(time / portTICK_PERIOD_MS);
    //millis(time);
}