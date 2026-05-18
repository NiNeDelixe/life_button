#ifndef GAME_MODES_HASCOUNTER_HPP_
#define GAME_MODES_HASCOUNTER_HPP_

#include "core/core.hpp"

#include "logic/counter/Counter.hpp"

#include <unordered_map>

class HasCounter
{
public:
    HasCounter();
    virtual ~HasCounter() = default;

public:
    static void applyToCounter(const int& num, const Counter::operators& oper);
    static void applyToCounter(const int& counter, const int& num, const Counter::operators& oper);
    static int getCount() { return m_current_counter.count; }

    static int addCounter();
    static Counter& getCurrentCaunter() { return m_current_counter; };
    static bool setCurrentCaunter(const int& counter);

protected:
    static Counter& m_current_counter;
    static std::unordered_map<int, Counter> m_counters;
};

#endif  // GAME_MODES_HASCOUNTER_HPP_
