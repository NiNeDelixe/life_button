#ifndef UTILS_DELAY_HPP_
#define UTILS_DELAY_HPP_

#include <Arduino.h>
#include <functional>
#include <vector>

class Delay
{
public:
    static void setTimeout(uint32_t time, std::function<void()> callback)
    {
        m_tasks.push_back({
            millis(),
            time,
            callback
        });
    }

    static void update()
    {
        uint32_t now = millis();

        for (auto it = m_tasks.begin(); it != m_tasks.end();)
        {
            if (now - it->start >= it->delay)
            {
                it->callback();
                it = m_tasks.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

private:
    struct Task
    {
        uint32_t start;
        uint32_t delay;
        std::function<void()> callback;
    };

    inline static std::vector<Task> m_tasks;
};

#endif // UTILS_DELAY_HPP_
