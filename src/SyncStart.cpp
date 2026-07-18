#include "game_modes/sync_start/SyncStart.hpp"

#include "core/Polling.hpp"

void SyncStart::start()
{
    HasTimer::setTimer(options.timer.get());
    //lora::Worker::getInstance().setTargetAddress(0x0001);
    lora::Worker::getInstance().addISyncableClass(this);

    button::Worker::getInstance().setOnPress(&SyncStart::onPress);
    button::Worker::getInstance().setOnRelease(&SyncStart::onRelease);

    lora::Worker::getInstance().setReceiveCallback(
            [this](const ISyncable::Data& data, uint16_t sender)
            {
                onRecive(data);
            });
}

void SyncStart::update()
{
    HasTimer::updateTimer();
    led_display::Worker::getInstance().setNumber(HasTimer::getRemainingTime() / 1000);

    if (HasTimer::isTimerStarted())
    {
        EVERY_S(1)
        {
            static bool state = false;
            state = !state;

            if (state)
                led_bar::Worker::getInstance().turnOn();
            else
                led_bar::Worker::getInstance().turnOff();
        }
    }
    

    if (button::Worker::getInstance().isPressedOnce())
    {
        lora::Worker::getInstance().send(this);

        Delay::setTimeout(200, [this]()
        {
            HasTimer::startTimer();
            beeper::Worker::getInstance().singleBeep();
        });
    }
    
    if (button::Worker::getInstance().isPressedOnce() && !HasTimer::isTimerFinished())
    {
        HasTimer::setTimer(options.timer.get());
        beeper::Worker::getInstance().singleBeep();
    }
    
    if (HasTimer::isTimerFinished())
    {
        beeper::Worker::getInstance().beepSeconds(TIME_S(5));
        start();
    }
    
}

void SyncStart::onPress()
{
}

void SyncStart::onRelease()
{
}

ISyncable::Data SyncStart::onSend()
{
    m_sendBuffer.clear();

    m_sendBuffer.push_back(1);

    return {
        m_sendBuffer.data(),
        m_sendBuffer.size()
    };
}

void SyncStart::onRecive(const ISyncable::Data& data)
{
    HasTimer::startTimer();
    beeper::Worker::getInstance().singleBeep();
    
}
