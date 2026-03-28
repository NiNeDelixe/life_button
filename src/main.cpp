#include "core/core.hpp"

#include "core/Constants.hpp"

#include "core/Polling.hpp"

void setup() 
{
  	Polling::startUp();
}

void loop() 
{
  	Polling::poll();
}