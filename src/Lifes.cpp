#include "game_modes/lifes/Lifes.hpp"

#include "core/Polling.hpp"

void Lifes::start()
{
    _button.setOnPress(&Lifes::onPress);
    _button.setOnRelease(&Lifes::onRelease);

    applyToCounter(options.lifes_option.get(), Counter::operators::SET);

    is_dead = false;
    is_beep = false;

    setTimer(options.timer_option.get());
}

void Lifes::update()
{
    updateTimer();
    
    _led_display.setNumber(m_counter.count);

    if (_button.isPressed())
    {
        startTimer();
    }

    if (isTimerFinished())
    {
        is_dead = true;
    }

    if (m_counter.count <= 0)
    {
        is_dead = true;
        is_beep = false;
    }

    if (is_dead && !is_beep)
    {
        _button_led.setState(true);
        _beeper.beepSeconds(TIME_S(10));
        is_beep = true;
        is_dead = false;
    }
}

void Lifes::onPress()
{
    applyToCounter(1, Counter::operators::DIV);
}

void Lifes::onRelease()
{
}
