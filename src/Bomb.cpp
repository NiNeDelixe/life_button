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
    if (defused)
    {
        beeper::Worker::getInstance().beepSeconds(TIME_S(1));
        start();
        return;
    }

    if (explode)
    {
        beeper::Worker::getInstance().beepSeconds(TIME_S(10));
        start();
        return;
    }

    // --- PLANTING ---
    if (!planted)
    {
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
        return;
    }

    // --- TIMER ---
    led_bar::Worker::getInstance().turnOn();

    EVERY_MS(100)
    {
        current_timer += 100;
    }
    
    if (options.timer_option.get() - current_timer <= options.timer_option.get() / TIME_S(10))
    {
        EVERY_MS(500)
        {
            beeper::Worker::getInstance().singleBeep();
        }
    }
    else
    {
        EVERY_MS(1000)
        {
            beeper::Worker::getInstance().singleBeep();
        }
    }
    
    

    led_display::Worker::getInstance().setNumber((options.timer_option.get() - current_timer) / TIME_S(1));

    if (current_timer >= options.timer_option.get())
    {
        explode = true;
        return;
    }

    // --- DEFUSE ---
    if (button::Worker::getInstance().isPressed())
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
    else
    {
        current_defusing_time = 0;
        is_beepd = false;
    }
    
}

void Bomb::onPress()
{
}

void Bomb::onRelease()
{
}
