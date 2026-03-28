#include "core/Polling.hpp"

Lifes Polling::lifes = Lifes();

void Polling::startUp()
{
    lifes.start();
}

void Polling::poll()
{
    lifes.update();
}
void Polling::delay(esp_time_t time)
{
    vTaskDelay(time / portTICK_PERIOD_MS);
    //millis(time);
}