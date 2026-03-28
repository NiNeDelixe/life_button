#ifndef LIFES_LIFES_HPP_
#define LIFES_LIFES_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

#include "logic/counter/Counter.hpp"

#include "Options.hpp"

class Lifes : public GameMode
{
public:
    Lifes() = default;
    ~Lifes() = default;

private:
    Counter lifes_counter;
    LifesOptions options;
};

#endif  // LIFES_LIFES_HPP_
