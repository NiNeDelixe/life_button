#ifndef LIFES_OPTIONS_HPP_
#define LIFES_OPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

struct LifesOptions
{
    TimeOption timer_option;
    IntOption lifes_option = IntOption(70);
};

#endif  // LIFES_OPTIONS_HPP_
