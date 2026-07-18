#include "game_modes/HasCounter.hpp"

std::vector<Counter> HasCounter::m_counters = {Counter()};
Counter* HasCounter::m_current_counter = &HasCounter::m_counters.front();
int HasCounter::m_counters_count = 1;
Counter HasCounter::counter = Counter();

HasCounter::HasCounter()
{
    HasCounter::clear();
}

void HasCounter::applyToCounter(const int& num, const Counter::operators &oper)
{
    switch (oper)
    {
    case Counter::operators::ADD:
        m_current_counter->count += num;
        break;
    case Counter::operators::DIV:
        m_current_counter->count -= num;
        break;
    case Counter::operators::SET:
        m_current_counter->count = num;
        break;
    
    default:
        break;
    }
}

void HasCounter::applyToCounter(const int& counterIdx, const int &num, const Counter::operators &oper)
{
    if (static_cast<size_t>(counterIdx) < m_counters.size())
    {
        m_current_counter = &m_counters[counterIdx];
        applyToCounter(num, oper);
    }
}

void HasCounter::clear()
{
    m_counters_count = 1;
    m_counters.clear();
    m_counters.push_back(Counter());
    m_current_counter = &m_counters.front();
}

int HasCounter::addCounter() 
{
    m_counters.push_back(Counter());
    m_counters_count++;
    return m_counters.size() - 1;
}

bool HasCounter::setCurrentCaunter(const int &counterIdx)
{
    if (m_counters.size() > static_cast<size_t>(counterIdx))
    {
        m_current_counter = &m_counters[counterIdx];
        return true;
    }
    return false;
}
