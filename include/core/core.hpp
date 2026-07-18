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

constexpr esp_time_t esp_time_t_max_value = 4294967295;

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

#define BEEPER_DIGITAL_OFF_OUTPUT LOW

#ifdef DEBUG
#define BEEPER_DIGITAL_OUTPUT LOW
#define BEEPER_DIGITAL_ON_OUTPUT LOW
#else
#define BEEPER_DIGITAL_OUTPUT HIGH
#define BEEPER_DIGITAL_ON_OUTPUT HIGH
#endif

#define TIME_NS(time) (time)
#define TIME_MS(time) (TIME_NS(time) * 10)
#define TIME_S(time) (TIME_MS(time) * 100)
#define TIME_M(time) (TIME_S(time)  * 60)

#define DELETE_COPY(Class) \
Class(const Class&) = delete; \
void operator=(const Class&) = delete;

#define DECLARE_CLASS(Class) \
public: \
DELETE_COPY(Class) \
static Class& getInstance() { static Class instance; return instance; } \
private: \

#endif  // INCLUDE_CORE_HPP_
