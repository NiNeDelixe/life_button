#include "game_modes/bomb/Bomb.hpp"

#include "core/Polling.hpp"

void Bomb::start()
{
    _led_display.clear();
    _led_display.setNumber(options.plant_option.get() / 100);
    _button.setOnPress(&Bomb::onPress);
    _button.setOnRelease(&Bomb::onRelease);
}

void Bomb::update()
{
    if (defused)
    {
        _beeper.beepSeconds(1000);
        defused = false;
        explode = false;
        planted = false;
        return;
    }
    

    if (explode)
    {
        _beeper.beepSeconds(10000);
        explode = false;
        return;
    }

    if (planted)
    {
        _led_bar.turnOn();
    }
    

    //PLANTING
    if (_button.isPressed() && current_plant_time < options.plant_option.get())
    {
        if (current_plant_time >= options.plant_option.get())
        {
            planted = true;
        }
        else
        {
            //current_plant_time += 1;
            EVERY_MS(100)
            {
                current_plant_time += 100;
            }
        }
    }
    else if (!_button.isPressed() && current_plant_time < options.plant_option.get())
    {
        current_plant_time = 0;
        planted = false;
    }
    else
    {
        planted = true;
    }

    if (!planted)
    {
        _led_display.setNumber((options.plant_option.get() - current_plant_time) / 1000);
        return;
    }

    //TIMER AND EXPLODE
    _led_display.setNumber((options.timer_option.get() - current_timer) / 1000);

    if (current_timer >= options.timer_option.get())
    {
        explode = true;
        return;
    }

    EVERY_MS(100)
    {
        current_timer += 100;
    }

    //DEFUSING
    if (current_defusing_time >= options.defuse_option.get())
    {
        defused = true;
    }
    else
    {
        EVERY_MS(100)
        {
            current_defusing_time += 100;
        }
    }
    
}

void Bomb::onPress()
{
    
}

void Bomb::onRelease()
{
    
}
