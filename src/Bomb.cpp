#include "game_modes/bomb/Bomb.hpp"

#include "core/Polling.hpp"

void Bomb::start()
{
    led_display::Worker::getInstance().clear();
    led_bar::Worker::getInstance().turnOff();

    led_bar::Worker::getInstance().setInt(options.defuse_option.get() / TIME_S(1), 1);

    button::Worker::getInstance().setOnPress(&Bomb::onPress);
    button::Worker::getInstance().setOnRelease(&Bomb::onRelease);

    current_plant_time = 0;
    current_timer = 0;
    current_defusing_time = 0;

    planted = false;
    explode = false;
    defused = false;
    is_beepd = false;
}

void Bomb::update()
{
    updateEnd();

    // --- PLANTING ---
    updatePlant();

    // --- TIMER ---
    updateTimer();

    // --- DEFUSE ---
    updateDefuse();
    
}

void Bomb::updatePlant()
{
    if (!checkIdle())
    {
        return;
    }
    

    if (button::Worker::getInstance().isPressed())
    {            
        EVERY_MS(1000)
        {
            current_plant_time += 1000;
        }

        if (!is_beepd)
        {
            beeper::Worker::getInstance().singleBeep();
            is_beepd = true;
        }

        if (current_plant_time >= options.plant_option.get())
        {
            planted = true;
            current_timer = 0;
            is_beepd = false;
        }
    }
    else
    {
        current_plant_time = 0;
        is_beepd = false;
    }

    led_display::Worker::getInstance().setNumber((options.plant_option.get() - current_plant_time) / TIME_S(1));
}

void Bomb::updateDefuse()
{
    if (checkIdle())
    {
        return;
    }
    

    if (button::Worker::getInstance().isPressed() && planted)
    {
        if (!is_beepd)
        {
            beeper::Worker::getInstance().singleBeep();
            is_beepd = true;
        }

        EVERY_MS(1000)
        {
            current_defusing_time += 1000;
        }

        if (current_defusing_time >= options.defuse_option.get())
        {
            defused = true;
            is_beepd = false;
        }

        led_bar::Worker::getInstance().setInt((options.defuse_option.get() - current_defusing_time) / TIME_S(1), 1);
    }
    else if(planted)
    {
        current_defusing_time = 0;
        is_beepd = false;
        led_bar::Worker::getInstance().setInt(options.defuse_option.get() / TIME_S(1), 1, false);
    }
}

void Bomb::updateTimer()
{
    if (checkIdle())
    {
        return;
    }

    EVERY_MS(1000)
    {
        current_timer += 1000;
    }

    const uint32_t blink_interval =
        (options.timer_option.get() - current_timer <= options.timer_option.get() / TIME_S(10))
            ? 500
            : 1000;

    EVERY_MS(blink_interval)
    {
        beeper::Worker::getInstance().singleBeep();
    }

    if ((millis() / blink_interval) % 2 == 0)
    {
        led_bar::Worker::getInstance().turnOn();
    }
    else
    {
        led_bar::Worker::getInstance().turnOff();
    }

    if (planted)
    {
        led_display::Worker::getInstance().setNumber((options.timer_option.get() - current_timer) / TIME_S(1));
    }

    if (current_timer >= options.timer_option.get())
    {
        explode = true;
        return;
    }
}

void Bomb::updateEnd()
{
    if (defused)
    {
        beeper::Worker::getInstance().beepSeconds(TIME_S(5));
        start();
        return;
    }

    if (explode)
    {
        beeper::Worker::getInstance().beepSeconds(TIME_S(20));
        start();
        return;
    }
}

bool Bomb::checkIdle()
{
    return !defused && !explode && !planted;
}

bool Bomb::checkPlanted()
{
    return !defused && !explode && planted;
}

bool Bomb::checkExplode()
{
    return !defused && explode && !planted;
}

bool Bomb::checkDefused()
{
    return defused && !explode && !planted;
}

void Bomb::onPress()
{
}

void Bomb::onRelease()
{
}
