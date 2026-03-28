#include "game_modes/lifes/Lifes.hpp"

#include "core/Polling.hpp"

Counter Lifes::lifes_counter = Counter();
LifesOptions Lifes::options = LifesOptions();

void Lifes::start()
{
    led_display_worker = led_display::Worker();

#ifdef USE_STL_CODE
    button_worker.setOnPress(std::bind(&Lifes::onPress, &lifes));
    button_worker.setOnRelease(std::bind(&Lifes::onRelease, &lifes));
#else
    button_worker.setOnPress(&Lifes::onPress);
    button_worker.setOnRelease(&Lifes::onRelease);
#endif

    applyToCounter(options.lifes_option.get(), operators::SET);
}

void Lifes::update()
{
    button_worker.update();
    led_display_worker.setNumber(lifes_counter.count);
}

void Lifes::onPress()
{
    Serial.print("life button pressed");
    applyToCounter(1, operators::DIV);
}

void Lifes::onRelease()
{
    Serial.print("life button release");
}

void Lifes::applyToCounter(int num, const operators &oper)
{
    switch (oper)
    {
    case operators::ADD:
        lifes_counter.count += num;
        break;
    case operators::DIV:
        lifes_counter.count -= num;
        break;
    case operators::SET:
        lifes_counter.count = num;
        break;
    
    default:
        break;
    }
     
}