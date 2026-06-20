#include "externals/lora/Worker.hpp"

#include <queue>
#include <vector>

lora::Worker::Worker()
{

}

void lora::Worker::update()
{
}

void lora::Worker::sendAllMessages()
{
    for (auto&& classs : m_classes)
    {
        void* data;
        size_t data_size;
        classs->onSend(data, data_size);
    }
    
}

void lora::Worker::addISyncableClass(ISyncable *class_to_add)
{
    m_classes.push_back(class_to_add);
}