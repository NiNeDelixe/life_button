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
    DECLARE_CLASS(Worker)

private:
    Worker();

public:
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

#endif  // LED_BAR_WORKER_HPP_
