#include "game_modes/lifes/Lifes.hpp"

#include "core/Polling.hpp"

void Lifes::start()
{
    button::Worker::getInstance().setOnPress(&Lifes::onPress);
    button::Worker::getInstance().setOnRelease(&Lifes::onRelease);

    applyToCounter(options.lifes_option.get(), Counter::operators::SET);

    is_dead = false;
    is_beep = false;

    setTimer(options.timer_option.get());
}

void Lifes::update()
{
    updateTimer();
    
    led_display::Worker::getInstance().setNumber(m_counter.count);

    if (button::Worker::getInstance().isPressed())
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
        button::led::Worker::getInstance().setState(true);
        beeper::Worker::getInstance().beepSeconds(TIME_S(10));
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
