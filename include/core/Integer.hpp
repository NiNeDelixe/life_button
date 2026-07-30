#ifndef CORE_INTEGER_HPP_
#define CORE_INTEGER_HPP_

#include <Arduino.h>

#include <stdint.h>

template<class INT_TYPE = int32_t>
class Integer
{
public:
    Integer() : m_value(0) {}
    Integer(INT_TYPE value) : m_value(value) {}

    operator INT_TYPE() const 
    {
        return m_value;
    }

    Integer &operator=(INT_TYPE value) 
    {
        m_value = value;
        return *this;
    }

    Integer &operator+=(INT_TYPE value) 
    {
        m_value += value;
        return *this;
    }

    Integer &operator-=(INT_TYPE value) 
    {
        m_value -= value;
        return *this;
    }

    const char *toString() const 
    {
        itoa(m_value, m_buffer, 10);
        return m_buffer;
    }

private:
    INT_TYPE m_value;
    mutable char m_buffer[12];
};

#endif // CORE_INTEGER_HPP_
