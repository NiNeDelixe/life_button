#include "game_modes/point_farming/PointFarming.hpp"

#include "core/Polling.hpp"

void PointFarming::start()
{
    _led_display.clear();
    _led_display.setNumber(0);
    _button.setOnPress(&PointFarming::onPress);
    _button.setOnRelease(&PointFarming::onRelease);
}

void PointFarming::update()
{
    _led_display.setNumber(m_counter.count);
}

void PointFarming::onPress()
{
    applyToCounter(1, Counter::operators::ADD);
}

void PointFarming::onRelease()
{
}
