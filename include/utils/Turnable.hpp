#ifndef UTILS_TURNABLE_HPP_
#define UTILS_TURNABLE_HPP_

#include "core/core.hpp"

#include "utils/Updatable.hpp"

class Turnable : public Updatable
{
public:
    Turnable() = default;
    ~Turnable() = default;

public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void changeState() { turn_state = !turn_state; };
    //virtual void update() override = 0;
    virtual void setState(bool state) { turn_state = state; }

protected:
    bool turn_state = false;
};

#endif // UTILS_TURNABLE_HPP_
