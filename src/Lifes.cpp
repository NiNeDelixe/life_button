#include "game_modes/lifes/Lifes.hpp"

#include "core/Polling.hpp"

void Lifes::start()
{
    _button.setOnPress(&Lifes::onPress);
    _button.setOnRelease(&Lifes::onRelease);

    applyToCounter(options.lifes_option.get(), Counter::operators::SET);

    is_dead = false;
}

void Lifes::update()
{
    _led_display.setNumber(m_counter.count);

    
    if (is_dead && !is_beep)
    {
        _button_led.setState(true);
        _beeper.beepSeconds(5000);
        is_beep = true;
    }
    
    if (m_counter.count <= 0)
    {
        this->is_dead = true;
    }
}

void Lifes::onPress()
{
    applyToCounter(1, Counter::operators::DIV);
}

void Lifes::onRelease()
{
}
