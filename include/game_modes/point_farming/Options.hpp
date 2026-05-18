#ifndef POINT_FARMING_OPTIONS_HPP_
#define POINT_FARMING_OPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

#include "game_modes/GameModeOptions.hpp"

#include "game_modes/HasCounter.hpp"

struct PointFarmingOptions : public GameModeOptions
{
    TimeOption timer = TimeOption(4294967294);
    StaticArrayOption<uint8_t, 3> operation_type = { (uint8_t)Counter::operators::ADD, (uint8_t)Counter::operators::DIV, (uint8_t)Counter::operators::SET  };
    IntOption operation_value = { 1 };
    IntOption start_value = { 0 };

    void save(Preferences& prefs) const override
    {
        prefs.putBytes("pf_operation_type", operation_type.get().data(), 3);
        prefs.putInt("pf_timer", timer.get());
        prefs.putInt("pf_operation_value", operation_value.get());
        prefs.putInt("pf_start_value", start_value.get());
    }

    void load(Preferences& prefs) override
    {
        //uint8_t* array_buffer;
        std::array<uint8_t, 3> array_buffer;
        prefs.getBytes("pf_operation_type", array_buffer.data(), array_buffer.size());
        // for (size_t i = 0; i < 3; ++i)
        // {
        //     array_buffer[i] = buffer[i];
        // }
        operation_type.set(array_buffer);
        
        
        timer = prefs.getInt("pf_timer", 4294967294);
        prefs.getInt("pf_operation_value", operation_value.get());
        prefs.getInt("pf_start_value", start_value.get());
    }
};


#endif  // POINT_FARMING_OPTIONS_HPP_
