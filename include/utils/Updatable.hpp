#ifndef UTILS_UPDATABLE_HPP_
#define UTILS_UPDATABLE_HPP_

#include "core/core.hpp"

class Polling;

class Updatable
{
protected:
    Updatable();
    virtual ~Updatable();

    Updatable(const Updatable&) = delete;
    Updatable& operator=(const Updatable&) = delete;
    Updatable(Updatable&&) = delete;
    Updatable& operator=(Updatable&&) = delete;

public:
    virtual void update() = 0;

private:
    
};

#endif // UTILS_UPDATABLE_HPP_
