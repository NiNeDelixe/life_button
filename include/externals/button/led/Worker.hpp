#ifndef LED_WORKER_HPP_
#define LED_WORKER_HPP_

#include "core/core.hpp"

#include "externals/IWorker.hpp"

namespace button
{
namespace led
{
    class Worker;
}
}

class button::led::Worker : public IWorker
{
public:
    Worker();
    ~Worker() = default;

public:
    void update() override;

public:
    void setState(bool sate);
    void changetState();

private:
    bool state = false;
};

static button::led::Worker _button_led = button::led::Worker();

#endif  // LED_WORKER_HPP_
