#ifndef KING_OF_THE_HILL_KINGOFTHEHILL_HPP_
#define KING_OF_THE_HILL_KINGOFTHEHILL_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

#include "game_modes/king_of_the_hill/Options.hpp"

class KingOfTheHill : public GameMode
{
public:
    KingOfTheHill() = default;
    ~KingOfTheHill() = default;

    void start();
    void update();

public:
    GameModeOptions* getOptions() override { return &options; };

public:
    KOTHOptions options;

private:
    
};

#endif  // KING_OF_THE_HILL_KINGOFTHEHILL_HPP_
