#ifndef EXTERNALS_IWORKER_HPP_
#define EXTERNALS_IWORKER_HPP_

#include "core/core.hpp"

class IWorker
{
public:
    IWorker() = default;
    ~IWorker() = default;

public:
    virtual void update() = 0;

private:
    
};

#endif  // EXTERNALS_IWORKER_HPP_
