#include "game_modes/point_farming/PointFarming.hpp"

#include "core/Polling.hpp"

void PointFarming::start()
{
    led_display::Worker::getInstance().clear();
    led_display::Worker::getInstance().setNumber(0);
    button::Worker::getInstance().setOnPress(&PointFarming::onPress);
    button::Worker::getInstance().setOnRelease(&PointFarming::onRelease);
}

void PointFarming::update()
{
    led_display::Worker::getInstance().setNumber(m_counter.count);
}

void PointFarming::onPress()
{
    applyToCounter(1, Counter::operators::ADD);
}

void PointFarming::onRelease()
{
}
