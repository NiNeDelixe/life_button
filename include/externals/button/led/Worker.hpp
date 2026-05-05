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
    DECLARE_CLASS(Worker)

private:
    Worker();

public:
    ~Worker() = default;

public:
    void update() override;

public:
    void setState(bool sate);
    void changetState();

private:
    bool state = false;
};

#endif  // LED_WORKER_HPP_
