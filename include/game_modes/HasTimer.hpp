#ifndef GAME_MODES_HASTIMER_HPP_
#define GAME_MODES_HASTIMER_HPP_

#include "core/core.hpp"

class HasTimer
{
public:
    HasTimer() = default;
    virtual ~HasTimer() = default;


    void setTimer(uint32_t duration_ms)
    {
        m_duration = duration_ms;
        m_finished = false;
        m_started = false;
    }

protected:
    void startTimer()
    {
        if (m_started || m_duration == 0)
            return;

        m_start_time = millis();
        m_started = true;
    }

    void updateTimer()
    {
        if (!m_started || m_finished)
            return;

        if (millis() - m_start_time >= m_duration)
        {
            m_finished = true;
        }
    }

    bool isTimerFinished() const
    {
        return m_finished;
    }

private:
    uint32_t m_start_time = 0;
    uint32_t m_duration = 0;
    bool m_finished = false;
    bool m_started = false;
};

#endif  // GAME_MODES_HASTIMER_HPP_
