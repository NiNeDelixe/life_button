#include "core/Polling.hpp"

#include "utils/Updatable.hpp"

GameModesManager Polling::mode_manager = {};

void Polling::startUp()
{
    web::BoardsSync::getInstance().onStart();
    led_bar::Worker::getInstance().turnOn();
    beeper::Worker::getInstance().singleBeep();
    led_circuit::Worker::getInstance().singleRun();
    web::WebInterface::getInstance().onStart();
    led_display::Worker::getInstance().clear();
    rfid::Worker::getInstance();

    led_strip::Worker::getInstance().setBehavor(_first_example);
    
    led_bar::Worker::getInstance().turnOff();

    led_bar::Worker::getInstance().setText("test");

    button::led::Worker::getInstance().turnOff();

    mode_manager.createSavedGamemode();
}

void Polling::poll()
{
    Delay::update();

    std::vector<Updatable*> snapshot;
    {
        std::lock_guard<std::mutex> lock(mutex());
        snapshot = objects();
    }
    
    for (auto* obj : snapshot) 
    {
        obj->update();
    }

    // if (HasTimer* timer = (HasTimer*)(mode_manager.getCurrentGameMode()))
    //     timer->updateTimer();
    
    mode_manager.update();
}

void Polling::delay(esp_time_t time)
{
    vTaskDelay(time / portTICK_PERIOD_MS);
    //millis(time);
}