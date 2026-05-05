#ifndef LED_CIRCUIT_WORKER_HPP_
#define LED_CIRCUIT_WORKER_HPP_

#include "core/core.hpp"

#include <GTimer.h>

#include "externals/IWorker.hpp"

namespace led_circuit
{
    class Worker;
}

class led_circuit::Worker : public IWorker
{
    DECLARE_CLASS(Worker)

private:
    Worker();

public:
    ~Worker() = default;

public:
    void update() override;

public:
    void timeRun(esp_time_t time);
    void singleRun(esp_time_t time = 50);

private:
    bool state;
    esp_time_t m_time;
    esp_time_t start_time;
    bool active;
};

#endif  // LED_CIRCUIT_WORKER_HPP_
