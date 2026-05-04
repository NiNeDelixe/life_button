#ifndef INCLUDE_CORE_HPP_
#define INCLUDE_CORE_HPP_

#include <Arduino.h>

#include <GTimer.h>

#include <stdint.h>

#include "Constants.hpp"

#define NOMINMAX

#define CORE_VERSION "0.1.0"

using esp_time_t = uint32_t;
using esp_millis_t = uint32_t;

#define WARN warning
#define ERROR error
#define INFO info
//#define DEBUG debug

#define STR(x) #x
#define XSTR(x) STR(x)

#define LOG(severity, message)        \
    do {                             \
        Serial.print("[");           \
        Serial.print(#severity);     \
        Serial.print("]: ");         \
        Serial.println(message);     \
    } while(0)

#define DIGITAL_OUTPUT HIGH

#ifdef DEBUG
#define BEEPER_DIGITAL_OUTPUT LOW
#else
#define BEEPER_DIGITAL_OUTPUT HIGH
#endif

#define TIME_NS(time) (time)
#define TIME_MS(time) (TIME_NS(time) * 10)
#define TIME_S(time) (TIME_MS(time) * 100)
#define TIME_M(time) (TIME_S(time)  * 60)

#endif  // INCLUDE_CORE_HPP_
