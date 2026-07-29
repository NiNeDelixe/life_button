#include "utils/Updatable.hpp"

#include "core/Polling.hpp"

Updatable::Updatable()
{
    Polling::registerObject(this);
}

Updatable::~Updatable()
{
    Polling::unregisterObject(this);
}