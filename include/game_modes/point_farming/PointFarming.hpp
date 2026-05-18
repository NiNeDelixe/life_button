#pragma once
#ifndef POINT_FARMING_POINTFARMING_HPP_
#define POINT_FARMING_POINTFARMING_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

#include "game_modes/HasCounter.hpp"
#include "game_modes/HasTimer.hpp"

#include "game_modes/point_farming/Options.hpp"

class PointFarming : public GameMode, public HasCounter, public HasTimer
{
public:
    PointFarming() = default;
    ~PointFarming() = default;

public:
    void start() override;
    void update() override;

    static void onPress();
    static void onRelease();

public:
    GameModeOptions* getOptions() { return &options; };

public:
    PointFarmingOptions options;

private:
};

#endif  // POINT_FARMING_POINTFARMING_HPP_
