#include "game_modes/lifes/Lifes.hpp"

#include "core/Polling.hpp"

void Lifes::start()
{
    button::Worker::getInstance().setOnPress(&Lifes::onPress);
    button::Worker::getInstance().setOnRelease(&Lifes::onRelease);

    applyToCounter(options.lifes_option.get(), Counter::operators::SET);

    is_dead = false;
    is_beep = false;
    is_time_end = false;

    setTimer(options.timer_option.get());
}

void Lifes::update()
{
    updateTimer();
    
    if (!is_time_end)
    {
        led_display::Worker::getInstance().setNumber(getCount());
    }

    if (button::Worker::getInstance().isPressed())
    {
        startTimer();
    }

    if (isTimerFinished())
    {
        is_time_end = true;
    }

    if (getCount() <= 0)
    {
        is_dead = true;
    }

    if (is_dead && !is_beep)
    {
        button::led::Worker::getInstance().setState(true);
        beeper::Worker::getInstance().beepSeconds(TIME_S(10));
        is_beep = true;
        is_dead = false;
        is_time_end = false;
    }

    if (is_dead)
    {
        EVERY_S(1)
        {
            led_display::Worker::getInstance().setText("Life");
        }
    }

    if (is_time_end)
    {
        led_display::Worker::getInstance().setText("End ");
    }
    
}

void Lifes::onPress()
{
    applyToCounter(1, Counter::operators::DIV);
}

void Lifes::onRelease()
{
}
