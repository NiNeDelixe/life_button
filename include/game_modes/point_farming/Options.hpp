#ifndef POINT_FARMING_OPTIONS_HPP_
#define POINT_FARMING_OPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

#include "game_modes/GameModeOptions.hpp"

#include "game_modes/HasCounter.hpp"

struct PointFarmingOptions : public GameModeOptions
{
    TimeOption timer = TimeOption(4294967294);
    ArrayOption<uint8_t> operation_type = {};

    void save(Preferences& prefs) const override
    {
        prefs.putBytes("pf_operation_type", operation_type.get(), 3);
        prefs.putInt("pf_timer", timer.get());
    }

    void load(Preferences& prefs) override
    {
        prefs.getBytes("pf_operation_type", operation_type.get(), 3);
        timer = prefs.getInt("pf_timer", 4294967294);
    }
};


#endif  // POINT_FARMING_OPTIONS_HPP_
