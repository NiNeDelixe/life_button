#include "logic/timer/Timer.hpp"

Timer::Timer()
{
    timer = millis();
}

void Timer::update()
{
    timer = millis();
}

bool Timer::isTimeOut(esp_time_t time)
{
    if (time == 0)
    {
        time = estimation;
    }
    
    if (millis() - timer >= time)
    {
        return true;
    }
    

    return false;
}
