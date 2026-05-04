#ifndef KING_OF_THE_HILL_KINGOFTHEHILL_HPP_
#define KING_OF_THE_HILL_KINGOFTHEHILL_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

class KingOfTheHill : public GameMode
{
public:
    KingOfTheHill() = default;
    ~KingOfTheHill() = default;

    void start();
    void update();

private:
    
};

#endif  // KING_OF_THE_HILL_KINGOFTHEHILL_HPP_
