#include "externals/led_bar/Worker.hpp"

#include "utils/Delay.hpp"

led_bar::Worker::Worker()
    : lcd(ESP_EXTERNAL_BAR_DISPLAY_I2C_ADDRES, ESP_EXTERNAL_BAR_DISPLAY_CHARS_COUNT, ESP_EXTERNAL_BAR_DISPLAY_LINE_COUNT)
{
    lcd.init();
    lcd.clear();

    is_displayed_new_text = false;
}

void led_bar::Worker::turnOn()
{
    if (is_displayed_new_text)
    {
        return;
    }
    setState(true);
    lcd.backlight();
}

void led_bar::Worker::turnOff()
{
    if (is_displayed_new_text)
    {
        return;
    }
    setState(false);
    lcd.noBacklight();
}

void led_bar::Worker::setText(const char *text)
{
    lcd.clear();

    setText(text, 0);
}

void led_bar::Worker::setText(const char *text, const int &line_num, const bool& handle_backlight)
{
    if (line_num < 0 || line_num >= ESP_EXTERNAL_BAR_DISPLAY_LINE_COUNT)
        return;

    if (displayed_text[line_num] == text)
        return;

    displayed_text[line_num] = text;

    lcd.setCursor(0, line_num);
    lcd.print("                ");
    lcd.setCursor(0, line_num);
    lcd.print(text);

    if (handle_backlight)
    {
        handleBacklight();
    }
}

void led_bar::Worker::setInt(const int &num, const int& line, const bool& handle_backlight)
{
    if (line < 0 || line >= ESP_EXTERNAL_BAR_DISPLAY_LINE_COUNT)
        return;

    if (old_int == num)
        return;

    old_int = num;

    lcd.setCursor(0, line);
    lcd.print("                ");
    lcd.setCursor(0, line);
    lcd.printf("%d", num);

    if (handle_backlight)
    {
        handleBacklight();
    }
}

void led_bar::Worker::handleBacklight(const time_t &time)
{
    is_displayed_new_text = true;

    lcd.backlight();

    Delay::setTimeout(time, []() {
        auto &w = led_bar::Worker::getInstance();
        w.is_displayed_new_text = false;
        w.update();
    });
}

void led_bar::Worker::clear()
{
    lcd.clear();
}

void led_bar::Worker::update()
{
    if (is_displayed_new_text)
    {
        return;
    }
    

    if (turn_state)
    {
        lcd.backlight();
    }
    else
    {
        lcd.noBacklight();
    }
}