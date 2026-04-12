#ifndef TIMER_TIMER_HPP_
#define TIMER_TIMER_HPP_

#include "core/core.hpp"

class Timer
{
public:
    Timer();
    ~Timer() = default;

public:
    //void init();
    void update();

public:
    void setDestination(esp_time_t time) { estimation = time; }
    esp_time_t getTime() const { return timer; }

public:
    bool isTimeOut(esp_time_t time = 0);

private:
    esp_time_t timer;
    esp_time_t estimation;
};

#endif  // TIMER_TIMER_HPP_
