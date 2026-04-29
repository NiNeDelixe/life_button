#include "game_modes/bomb/Bomb.hpp"

#include "core/Polling.hpp"

void Bomb::start()
{
    _led_display.clear();
    _button.setOnPress(&Bomb::onPress);
    _button.setOnRelease(&Bomb::onRelease);
    // but.setOnPress(&Bomb::onPress);
    // but.setOnRelease(&Bomb::onRelease);

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
    //but.update();
    if (defused)
    {
        _beeper.beepSeconds(1000);
        start();
        return;
    }

    if (explode)
    {
        _beeper.beepSeconds(10000);
        start();
        return;
    }

    // --- PLANTING ---
    if (!planted)
    {
        if (_button.isPressed())
        {            
            EVERY_MS(100)
            {
                current_plant_time += 100;
            }

            if (!is_beepd)
            {
                _beeper.singleBeep();
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

        _led_display.setNumber((options.plant_option.get() - current_plant_time) / 1000);
        return;
    }

    // --- TIMER ---
    _led_bar.turnOn();

    EVERY_MS(100)
    {
        current_timer += 100;
    }
    
    if (options.timer_option.get() - current_timer <= 10000)
    {
        EVERY_MS(500)
        {
            _beeper.singleBeep();
        }
    }
    else
    {
        EVERY_MS(1000)
        {
            _beeper.singleBeep();
        }
    }
    
    

    _led_display.setNumber((options.timer_option.get() - current_timer) / 1000);

    if (current_timer >= options.timer_option.get())
    {
        explode = true;
        return;
    }

    // --- DEFUSE ---
    if (_button.isPressed())
    {
        if (!is_beepd)
        {
            _beeper.singleBeep();
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
