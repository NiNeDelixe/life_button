#include "game_modes/lifes/Lifes.hpp"

#include "core/Polling.hpp"

LifesOptions Lifes::options = LifesOptions();

void Lifes::start()
{
    buton.setOnPress(&Lifes::onPress);
    buton.setOnRelease(&Lifes::onRelease);
    _button.setOnPress(&Lifes::onPress);
    _button.setOnRelease(&Lifes::onRelease);

    applyToCounter(options.lifes_option.get(), Counter::operators::SET);
}

void Lifes::update()
{
    buton.update();
    _led_display.setNumber(m_counter.count);

    if (m_counter.count <= 0)
    {
        this->is_dead = true;
    }

    if (is_dead && !is_beep)
    {
        _button_led.setState(true);
        _beeper.beepSeconds(5000);
        is_beep = true;
    }
    
}

void Lifes::onPress()
{
    LOG(DEBUG, "life button pressed");
    applyToCounter(1, Counter::operators::DIV);
}

void Lifes::onRelease()
{
    LOG(DEBUG, "life button release");
}
