#ifndef UTILS_STRING_HPP_
#define UTILS_STRING_HPP_

#include "core/core.hpp"

#include <TM1637Display.h>

namespace string
{
    uint8_t encodeChar(char c);

    void encodeString(const char* str, uint8_t* out, uint8_t len);
}

#endif  // UTILS_STRING_HPP_
