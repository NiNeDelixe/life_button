#include "game_modes/point_farming/PointFarming.hpp"

#include "core/Polling.hpp"

void PointFarming::start()
{
    led_display::Worker::getInstance().clear();
    led_display::Worker::getInstance().setNumber(options.start_value.get());
    HasCounter::clear();
    applyToCounter(options.start_value.get(), Counter::operators::SET);
    button::Worker::getInstance().setOnPress(&PointFarming::onPress);
    button::Worker::getInstance().setOnRelease(&PointFarming::onRelease);

    setTimer(options.timer.get());
}

void PointFarming::update()
{
    led_display::Worker::getInstance().setNumber(getCount());

    if (button::Worker::getInstance().isPressedOnce())
    {
        startTimer();
        applyToCounter(options.operation_value.get(), Counter::operators::ADD);
    }
    
}

void PointFarming::onPress()
{
}

void PointFarming::onRelease()
{
}
