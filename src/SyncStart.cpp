#include "game_modes/sync_start/SyncStart.hpp"

#include "core/Polling.hpp"

void SyncStart::start()
{
    HasTimer::setTimer(options.timer.get());
    //lora::Worker::getInstance().setTargetAddress(0x0001);
    lora::Worker::getInstance().addISyncableClass(this);

    button::Worker::getInstance().setOnPress(&SyncStart::onPress);
    button::Worker::getInstance().setOnRelease(&SyncStart::onRelease);

    led_bar::Worker::getInstance().turnOff();
    led_bar::Worker::getInstance().setText("Push button to ready", 1);

    lora::Worker::getInstance().setReceiveCallback(
            [this](const ISyncable::Data& data, uint16_t sender)
            {
                onRecive(data);
            });

    is_other_side_ready = false;
    is_this_side_ready = false;
}

void SyncStart::update()
{
    HasTimer::updateTimer();
    led_display::Worker::getInstance().setNumber(HasTimer::getRemainingTime() / 1000);

    updateButtonTimer();
    
    setReady();

    confirmReady();

    if (button::Worker::getInstance().isPressedOnce() && (!is_other_side_ready || is_this_side_ready))
    {
        lora::Worker::getInstance().send(this);

        startButtonTimer();
    }
    
    // if (button::Worker::getInstance().isPressedOnce() && !HasTimer::isTimerFinished())
    // {
    //     HasTimer::setTimer(options.timer.get());
    //     beeper::Worker::getInstance().singleBeep();
    // }
    
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

void SyncStart::confirmReady()
{
    if (is_other_side_ready && !is_this_side_ready)
    {
        led_bar::Worker::getInstance().setText("PSH BUT TO START", 1);
    }
    
    if (is_this_side_ready && !is_other_side_ready)
    {
        led_bar::Worker::getInstance().setText("You ready, wait.", 1);
    }
    
    if (is_this_side_ready && is_other_side_ready)
    {
        led_bar::Worker::getInstance().setText("TIMER HAS START!", 1);
    }
    
}

void SyncStart::setReady()
{
    if (button::Worker::getInstance().isPressed() && !is_this_side_ready)
    {
        is_this_side_ready = true;
    }
}

void SyncStart::updateButtonTimer()
{
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
}

void SyncStart::startButtonTimer()
{
    if (this->is_this_side_ready && this->is_other_side_ready)
    {
        Delay::setTimeout(200, [this]()
        {
            HasTimer::startTimer();
            beeper::Worker::getInstance().singleBeep();
        });
    }
}

ISyncable::Data SyncStart::onSend()
{
    m_sendBuffer.clear();

    if (this->is_this_side_ready && this->is_other_side_ready)
    {
        m_sendBuffer.push_back(0); //starting signal
    }
    
    if (this->is_this_side_ready)
    {
        m_sendBuffer.push_back(1); //this button ready signal
    }

    return {
        m_sendBuffer.data(),
        m_sendBuffer.size()
    };
}

void SyncStart::onRecive(const ISyncable::Data& data)
{
    auto find = [&](size_t to_find) -> bool
    {
        return std::find(data.data, data.data + data.size, to_find)
            != data.data + data.size;
    };

    if (find(0))
    {
        HasTimer::startTimer();
        beeper::Worker::getInstance().singleBeep();
    }

    if (find(1))
    {
        is_other_side_ready = true;
    }
}
