#ifndef GAME_MODES_HAS_TIMER_HPP_
#define GAME_MODES_HAS_TIMER_HPP_

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

public:
    void startTimer()
    {
        if (m_started || m_duration == 0)
            return;

        LOG(INFO, "Timer has started");
        m_start_time = millis();
        m_started = true;
    }

    void updateTimer()
    {
        if (!m_started || m_finished)
            return;

        if (millis() - m_start_time >= m_duration)
        {
            LOG(INFO, "Timer is finished");
            m_finished = true;
        }
    }

    bool isTimerFinished() const
    {
        return m_finished;
    }

    bool isTimerStarted() const
    {
        return m_started;
    }

    uint32_t getTime() { return m_duration; }

    uint32_t getRemainingTime() const
    {
        if (!m_started)
            return m_duration;

        if (m_finished)
            return 0;

        uint32_t elapsed = millis() - m_start_time;

        if (elapsed >= m_duration)
            return 0;

        return m_duration - elapsed;
    }

private:
    uint32_t m_start_time = 0;
    uint32_t m_duration = 0;
    bool m_finished = false;
    bool m_started = false;
};

#endif // GAME_MODES_HAS_TIMER_HPP_
