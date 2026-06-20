#include "externals/led_bar/Worker.hpp"

led_bar::Worker::Worker()
    : lcd(ESP_EXTERNAL_BAR_DISPLAY_I2C_ADDRES, ESP_EXTERNAL_BAR_DISPLAY_CHARS_COUNT, ESP_EXTERNAL_BAR_DISPLAY_LINE_COUNT)
{
    // set the LCD address to 0x27 for a 16 chars and 2 line display
    lcd.init();
    lcd.clear();
}

void led_bar::Worker::turnOn()
{
    state = true;
    lcd.backlight();
}

void led_bar::Worker::turnOff()
{
    state = false;
    lcd.noBacklight();
}

void led_bar::Worker::changeState()
{
    state = !state;
}

void led_bar::Worker::setText(const char *text)
{
    lcd.clear();
    lcd.backlight();
}

void led_bar::Worker::update() 
{
    if (state)
    {
        lcd.backlight();
    }
    else
    {
        lcd.noBacklight();
    }
}