#ifndef GAME_MODES_HASCOUNTER_HPP_
#define GAME_MODES_HASCOUNTER_HPP_

#include "core/core.hpp"

#include "logic/counter/Counter.hpp"

#include <vector>

class HasCounter
{
public:
    HasCounter();
    virtual ~HasCounter() = default;

public:
    static void applyToCounter(const int& num, const Counter::operators& oper);
    static void applyToCounter(const int& counter, const int& num, const Counter::operators& oper);
    static int getCount() { return m_current_counter->count; }
    static void clear();

    static int addCounter();
    static Counter& getCurrentCaunter() { return *m_current_counter; };
    static bool setCurrentCaunter(const int& counter);

protected:
    static Counter* m_current_counter;
    static std::vector<Counter> m_counters;
    static int m_counters_count;
    static Counter counter;
};

#endif  // GAME_MODES_HASCOUNTER_HPP_
