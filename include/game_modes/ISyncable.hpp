#ifndef GAME_MODES_ISYNCABLE_HPP_
#define GAME_MODES_ISYNCABLE_HPP_

#include "core/core.hpp"

class ISyncable
{
public:
    struct Data
    {
        const uint8_t* data;
        size_t size;

        bool empty() const
        {
            return data == nullptr || size == 0;
        }
    };

public:
    ISyncable() = default;
    virtual ~ISyncable() = default;

    //change data and data_size to send data
    virtual Data onSend() = 0;
    //data and data_size is receiving from other board
    virtual void onRecive(const Data& data) = 0;

private:
    
};

#endif  // GAME_MODES_ISYNCABLE_HPP_
