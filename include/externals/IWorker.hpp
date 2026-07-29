#ifndef EXTERNALS_IWORKER_HPP_
#define EXTERNALS_IWORKER_HPP_

#include "core/core.hpp"

#include "utils/Updatable.hpp"

class IWorker : public Updatable
{
public:
    IWorker() = default;
    ~IWorker() = default;

public:
    virtual void update() = 0;

private:
    
};

#endif  // EXTERNALS_IWORKER_HPP_
