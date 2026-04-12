#ifndef GAME_MODES_HASCOUNTER_HPP_
#define GAME_MODES_HASCOUNTER_HPP_

#include "core/core.hpp"

#include "logic/counter/Counter.hpp"

class HasCounter
{
public:
    HasCounter() = default;
    virtual ~HasCounter() = default;

public:
    static void applyToCounter(int num, const Counter::operators& oper)
    {
        switch (oper)
        {
        case Counter::operators::ADD:
            m_counter.count += num;
            break;
        case Counter::operators::DIV:
            m_counter.count -= num;
            break;
        case Counter::operators::SET:
            m_counter.count = num;
            break;
        
        default:
            break;
        }
    }
    static int getCount() { return m_counter.count; }

protected:
    static Counter m_counter;
};

#endif  // GAME_MODES_HASCOUNTER_HPP_
