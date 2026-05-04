#ifndef CORE_CONSTANTS_HPP_
#define CORE_CONSTANTS_HPP_

using pin_t = uint8_t;

constexpr pin_t ESP_CIRCUIT_BLUE_LED_PIN = 8;

constexpr pin_t ESP_EXTERNAL_BUTTON_PIN = 1;
constexpr pin_t ESP_EXTERNAL_BUTTON_LED_PIN = 0;

constexpr pin_t ESP_EXTERNAL_DIGIT_DISPLAY_CLK_PIN = 2;
constexpr pin_t ESP_EXTERNAL_DIGIT_DISPLAY_DIO_PIN = 3;

constexpr pin_t ESP_EXTERNAL_BEEPER_PIN = 6;

constexpr pin_t ESP_EXTERNAL_LED_STRIP_PIN = 5;
constexpr size_t ESP_EXTERNAL_LED_STRIP_COUNT = 18;
#define ESP_EXTERNAL_LED_STRIP_COLOR_ORDER GRB
#define ESP_EXTERNAL_LED_STRIP_TYPE WS2812

constexpr pin_t ESP_EXTERNAL_LED_BAR_PIN = 4;

constexpr pin_t ESP_EXTERNAL_RFID_RST_PIN = 8;
constexpr pin_t ESP_EXTERNAL_RFID_SS_PIN = 200; //

constexpr pin_t ESP_EXTERNAL_RFID_SPI_SCK_PIN = 4;
constexpr pin_t ESP_EXTERNAL_RFID_SPI_MISO_PIN = 5;
constexpr pin_t ESP_EXTERNAL_RFID_SPI_MOSI_PIN = 6;


#endif  // CORE_CONSTANTS_HPP_
