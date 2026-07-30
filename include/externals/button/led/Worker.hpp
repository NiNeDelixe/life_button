#ifndef LED_WORKER_HPP_
#define LED_WORKER_HPP_

#include "core/core.hpp"

#include "externals/IWorker.hpp"

#include "utils/Turnable.hpp"

namespace button
{
    namespace led
    {
        class Worker;
    }
}

class button::led::Worker : public IWorker, public Turnable
{
    DECLARE_CLASS(Worker)

private:
    Worker();

public:
    ~Worker() = default;

public:
    void turnOn() override
    {
        setState(true);
        digitalWrite(ESP_EXTERNAL_BUTTON_LED_PIN, LOW);
    }
    void turnOff() override 
    {
        setState(false);
        digitalWrite(ESP_EXTERNAL_BUTTON_LED_PIN, HIGH);
    }
    void update() override;

private:

};

#endif  // LED_WORKER_HPP_
