#ifndef BEEPER_OPTIONS_HPP_
#define BEEPER_OPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

struct BeeperOptions
{
    IntOption volume = {100};
};


#endif  // BEEPER_OPTIONS_HPP_
