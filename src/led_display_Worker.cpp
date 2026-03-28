#include "externals/led_display/Worker.hpp"

led_display::Worker::Worker()
    : display(TM1637Display(ESP_EXTERNAL_DIGIT_DISPLAY_CLK_PIN, ESP_EXTERNAL_DIGIT_DISPLAY_DIO_PIN))
{
    display.setBrightness(0x0f);
}
void led_display::Worker::setText(const char *text, size_t length)
{
    if (length == 0)
    {
        length = strlen(text);
    }
    
    uint8_t* data = new uint8_t[length];

    string::encodeString(text, data, length);

    display.setSegments(data, length);
    delete[] data;
}

void led_display::Worker::setNumber(int num)
{
    display.showNumberDec(num, true);
}

void led_display::Worker::clear()
{
    display.clear();
}
