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
#define DEBUG debug

#define T(...) #__VA_ARGS__

#define LOG(severinity, message) Serial.println(T([severinity]: message));

#define DIGITAL_OUTPUT HIGH

#define BEEPER_DIGITAL_OUTPUT DIGITAL_OUTPUT

#endif  // INCLUDE_CORE_HPP_
