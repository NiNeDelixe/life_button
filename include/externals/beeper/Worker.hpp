#ifndef BEEPER_WORKER_HPP_
#define BEEPER_WORKER_HPP_

#include "core/core.hpp"

#include <GTimer.h>

#include "externals/IWorker.hpp"

#include "externals/beeper/Options.hpp"


namespace beeper
{
    class Worker;
}

using volume_t = int;

class beeper::Worker : public IWorker
{
    DECLARE_CLASS(Worker)

private:
    Worker();

public:
    ~Worker() = default;

public:
    void changeWorkState(bool state);

    void beepSeconds(esp_time_t time);
    void singleBeep(esp_time_t time = 100);

public:
    void update() override;

private:
    BeeperOptions options;
    
    bool state = false;
    bool active = false;
    esp_time_t m_time = 0;
    uint32_t start_time = 0;
    uint32_t last_single_beep_request_time = 0;
};

#endif  // BEEPER_WORKER_HPP_
