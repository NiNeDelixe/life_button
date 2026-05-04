#ifndef SAVING_ISAVEBLE_HPP_
#define SAVING_ISAVEBLE_HPP_

#include "core/core.hpp"

#include <Preferences.h>

class ISaveble
{
public:
    ISaveble() = default;
    virtual ~ISaveble() = default;

    virtual void save(Preferences& prefs) const = 0;
    virtual void load(Preferences& prefs) = 0;

private:
    
};

#endif  // SAVING_ISAVEBLE_HPP_
