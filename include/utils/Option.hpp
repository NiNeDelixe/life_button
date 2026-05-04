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


protected:
    T value;
};

class IntOption : public IOption<int>
{
public:
    IntOption() = default;
    IntOption(int value) { this->value = value; }
    ~IntOption() = default;

private:
    
};

class TimeOption : public IOption<esp_time_t>
{
public:
    TimeOption() = default;
    TimeOption(esp_time_t value) { this->value = value; }
    ~TimeOption() = default;

private:
    
};

class FlagOption : public IOption<bool>
{
public:
    FlagOption() = default;
    FlagOption(bool value) { this->value = value; }
    ~FlagOption() = default;

private:
    
};

template<class TYPE>
class ArrayOption : public IOption<TYPE*>
{
public:
    ArrayOption() = default;
    ArrayOption(TYPE* value) { this->value = value; }
    ~ArrayOption() = default;

private:
    
};

// template<class TYPE>
// class VectorOption : public IOption<std::vector<TYPE>>
// {
// public:
//     ArrayOption() = default;
//     ArrayOption(std::vector<TYPE> value) { this->value = value; }
//     ~ArrayOption() = default;

// private:
    
// };

#endif  // UTILS_OPTION_HPP_
