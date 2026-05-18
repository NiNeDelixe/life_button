#include "game_modes/HasCounter.hpp"

#include <unordered_map>

std::unordered_map<int, Counter> HasCounter::m_counters = {};
Counter& HasCounter::m_current_counter = HasCounter::m_counters[0];

HasCounter::HasCounter()
{
    HasCounter::m_counters.emplace();
    HasCounter::m_current_counter = HasCounter::m_counters[0];
}

void HasCounter::applyToCounter(const int& num, const Counter::operators &oper)
{
    switch (oper)
    {
    case Counter::operators::ADD:
        m_current_counter.count += num;
        break;
    case Counter::operators::DIV:
        m_current_counter.count -= num;
        break;
    case Counter::operators::SET:
        m_current_counter.count = num;
        break;
    
    default:
        break;
    }
}

void HasCounter::applyToCounter(const int& counter, const int &num, const Counter::operators &oper)
{
    if (m_counters.find(counter) != m_counters.end())
    {
        m_current_counter = m_counters[counter];
        applyToCounter(num, oper);
    }
    
}

int HasCounter::addCounter() 
{
    return m_counters.emplace().first.operator*().first;
}

bool HasCounter::setCurrentCaunter(const int &counter)
{
    if (m_counters.find(counter) != m_counters.end())
    {
        m_current_counter = m_counters[counter];
        return true;
    }
    return false;
}
