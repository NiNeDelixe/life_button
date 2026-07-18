#ifndef SYNC_START_OPTIONS_HPP_
#define SYNC_START_OPTIONS_HPP_

#include "core/core.hpp"

#include "utils/Option.hpp"

#include "game_modes/GameModeOptions.hpp"

#include "game_modes/HasCounter.hpp"

struct SyncStartOptions : public GameModeOptions
{
    TimeOption timer = TimeOption(TIME_S(5));

    void save(Preferences& prefs) const override
    {
        prefs.putInt("ss_timer", timer.get());
    }

    void load(Preferences& prefs) override
    {
        timer = prefs.getInt("ss_timer", TIME_S(5));
    }
};


#endif  // SYNC_START_OPTIONS_HPP_
