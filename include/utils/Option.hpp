#ifndef UTILS_OPTION_HPP_
#define UTILS_OPTION_HPP_

#include "core/core.hpp"

#include <initializer_list>

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
    //typedef type = typename(T);

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
    ArrayOption() : size(0) {}

    ArrayOption(std::initializer_list<TYPE> list)
    {
        size = list.size();
        this->value = new TYPE[size];

        size_t i = 0;
        for (const auto& v : list)
            this->value[i++] = v;
    }

    ArrayOption(const ArrayOption& other)
    {
        size = other.size;
        this->value = new TYPE[size];
        for (size_t i = 0; i < size; ++i)
            this->value[i] = other.value[i];
    }

    ArrayOption& operator=(const ArrayOption& other)
    {
        if (this == &other) return *this;

        delete[] this->value;

        size = other.size;
        this->value = new TYPE[size];
        for (size_t i = 0; i < size; ++i)
            this->value[i] = other.value[i];

        return *this;
    }

    ~ArrayOption()
    {
        delete[] this->value;
    }

public:
    //const TYPE*& get() const override { return *this->value; }
    TYPE* getArray() const { return this->value; }
    size_t getSize() const { return size; }

private:
    size_t size = 0;
};

template<class TYPE, size_t n>
class StaticArrayOption : public IOption<std::array<TYPE, n>>
{
public:
    StaticArrayOption()
    {
        this->value = {TYPE{}, TYPE{}, TYPE{}};
    }

    StaticArrayOption(const std::array<TYPE, n>& value)
    {
        this->value = value;
    }

    StaticArrayOption(TYPE v1, TYPE v2, TYPE v3)
    {
        this->value = {v1, v2, v3};
    }

    StaticArrayOption(std::initializer_list<TYPE> list)
    {
        size_t i = 0;
        for (auto& v : list)
        {
            if (i >= 3) break;
            this->value[i++] = v;
        }
        for (; i < 3; ++i)
            this->value[i] = TYPE{};
    }

    ~StaticArrayOption() = default;

public:
    const std::array<TYPE, n>& get() const override
    {
        return this->value;
    }

    void set(const std::array<TYPE, n>& new_value) override
    {
        this->value = new_value;
    }

    TYPE& operator[](size_t index) { return this->value[index]; }
    const TYPE& operator[](size_t index) const { return this->value[index]; }
};

template<class TYPE, size_t n>
class StaticChoiseOptions : public StaticArrayOption<TYPE, n>
{
public:
    // StaticArrayOption<TYPE, n>::StaticArrayOption();
    // StaticArrayOption<TYPE, n>::StaticArrayOption(const std::array<TYPE, n>&);
    // StaticArrayOption<TYPE, n>::StaticArrayOption(std::initializer_list<TYPE>);
    // StaticArrayOption<TYPE, n>::StaticArrayOption(TYPE, TYPE, TYPE);

private:
    size_t choise = 0;
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
