#ifndef UTILS_OPTION_HPP_
#define UTILS_OPTION_HPP_

#include "core/core.hpp"

template <typename T>
class IOption
{
public:
    IOption() = default;
    virtual ~IOption() = default;

public:
    virtual void set(const T& new_value) { value = new_value; };
    virtual const T& get() const { return value; };

public:


private:
    T value;
};

class IntOption : public IOption<int>
{
public:
    IntOption() = default;
    ~IntOption() = default;

private:
    
};

class TimeOption : public IOption<esp_time_t>
{
public:
    TimeOption() = default;
    ~TimeOption() = default;

private:
    
};


#endif  // UTILS_OPTION_HPP_
