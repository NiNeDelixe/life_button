#include "core/Polling.hpp"

led_display::Worker Polling::led_display_worker = led_display::Worker();
button::Worker Polling::button_worker = button::Worker(nullptr, nullptr);

void Polling::startUp()
{
    auto onPress = []() {
        led_display_worker.setText("PRES");
    };
    auto onRelease = []() {
        led_display_worker.setText("RELE");
    };
    button_worker.setOnPress(onPress);
    button_worker.setOnRelease(onRelease);
}

void Polling::poll()
{
    button_worker.update();
}
void Polling::delay(esp_time_t time)
{
    vTaskDelay(time / portTICK_PERIOD_MS);
    //millis(time);
}