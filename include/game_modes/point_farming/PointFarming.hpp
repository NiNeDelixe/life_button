#pragma once
#ifndef POINT_FARMING_POINTFARMING_HPP_
#define POINT_FARMING_POINTFARMING_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

#include "game_modes/HasCounter.hpp"

class PointFarming : public GameMode, public HasCounter
{
public:
    PointFarming() = default;
    ~PointFarming() = default;

public:
    void start() override;
    void update() override;

    static void onPress();
    static void onRelease();

private:
};

#endif  // POINT_FARMING_POINTFARMING_HPP_
