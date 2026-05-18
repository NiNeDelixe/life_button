#include "game_modes/bomb/Bomb.hpp"

#include "core/Polling.hpp"

void Bomb::start()
{
    led_display::Worker::getInstance().clear();
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
    if (planted)
    {
        return;
    }

    // if (!button::Worker::getInstance().isReleased())
    // {
    //     return;
    // }
    

    if (button::Worker::getInstance().isPressed())
    {            
        EVERY_MS(100)
        {
            current_plant_time += 100;
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
    if (button::Worker::getInstance().isPressed() && planted)
    {
        if (!is_beepd)
        {
            beeper::Worker::getInstance().singleBeep();
            is_beepd = true;
        }

        EVERY_MS(100)
        {
            current_defusing_time += 100;
        }

        if (current_defusing_time >= options.defuse_option.get())
        {
            defused = true;
            is_beepd = false;
        }
    }
    else if(planted)
    {
        current_defusing_time = 0;
        is_beepd = false;
    }
}

void Bomb::updateTimer()
{
    EVERY_MS(100)
    {
        led_bar::Worker::getInstance().turnOff();
        if (planted)
        {
            current_timer += 100;
        }
    }
    
    if (options.timer_option.get() - current_timer <= options.timer_option.get() / TIME_S(10))
    {
        EVERY_MS(500)
        {
            beeper::Worker::getInstance().singleBeep();
            led_bar::Worker::getInstance().turnOn();
        }
    }
    else
    {
        EVERY_MS(1000)
        {
            beeper::Worker::getInstance().singleBeep();
            led_bar::Worker::getInstance().turnOn();
        }
    }  

    led_display::Worker::getInstance().setNumber((options.timer_option.get() - current_timer) / TIME_S(1));

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

void Bomb::onPress()
{
}

void Bomb::onRelease()
{
}
