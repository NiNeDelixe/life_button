#ifndef GAME_MODES_ISYNCABLE_HPP_
#define GAME_MODES_ISYNCABLE_HPP_

#include "core/core.hpp"

class ISyncable
{
public:
    ISyncable() = default;
    virtual ~ISyncable() = default;

    //change data and data_size to send data
    virtual void onSend(void* data, size_t& data_size) = 0;
    //data and data_size is reciveng from other board
    virtual void onRecive(void* data, size_t data_size) = 0;

private:
    
};

#endif  // GAME_MODES_ISYNCABLE_HPP_
