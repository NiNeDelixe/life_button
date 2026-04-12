#ifndef LED_BAR_WORKER_HPP_
#define LED_BAR_WORKER_HPP_

#include "core/core.hpp"

#include "externals/IWorker.hpp"

namespace led_bar
{
    class Worker;
}

class led_bar::Worker : public IWorker
{
public:
    Worker();
    ~Worker() = default;

public:
    //void changeColor(int r, int g, int b);
    void turnOn();
    void turnOff();
    void changeState();

public:
    void update() override;

private:
    bool state;
};

static led_bar::Worker _led_bar = led_bar::Worker();

#endif  // LED_BAR_WORKER_HPP_
