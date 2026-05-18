#include "game_modes/king_of_the_hill/KingOfTheHill.hpp"

// #include <unordered_map>
// #include <set>

#include "core/Polling.hpp"


KingOfTheHill::~KingOfTheHill()
{
    
}

void KingOfTheHill::start()
{
    button::Worker::getInstance().setOnPress(nullptr);
    button::Worker::getInstance().setOnRelease(nullptr);

    led_strip::Worker::getInstance().changeColor(255, 255, 255); //white
    led_bar::Worker::getInstance().turnOn();

    HasTimer::setTimer(options.game_time.get());

    is_end_by_points = false;
    is_end_by_time = false;
}

void KingOfTheHill::update()
{
    KingOfTheHill::updateTimer();

    updateEndGame();

    // CHANGE TEAM CONQUEST
    updateConquestTeam();
    
    updatePoints();

    updateSound();
}

void KingOfTheHill::registerCards()
{
    if (!rfid::Worker::getInstance().tagDetected())
    {
        return;
    }
    
    auto uid = rfid::Worker::getInstance().getUIDCard();

    for (size_t i = 0; i < m_uids.size(); i++)
    {
        if (m_uids.find(uid) != m_uids.end())
        {
            int team = registerTeam();

            if (team == -1)
            {
                return;
            }
            
            m_uids.insert({uid, team});
        }
    }
    
}

int KingOfTheHill::registerTeam()
{
    int new_team = addCounter();
    auto result = m_teams.insert(new_team);
    
    if (result.second)
    {
        return *result.first;
    }

    if (result.first != m_teams.end())
    {
        return *result.first;
    }
    
    
    return -1;
}

void KingOfTheHill::updatePoints()
{
    if (is_end_by_points)
    {
        return;
    }
    
    //render points on top display or blink them
    led_bar::Worker::getInstance().turnOff();

    EVERY_T(1 * 1000ul, GT_MACRO_MILLIS, uint32_t)
    {
        led_bar::Worker::getInstance().turnOn();
        applyToCounter(m_current_team, 1 * options.points_multiplier.get(), Counter::operators::ADD);
    }

    if (getCount() >= options.points_to_win.get())
    {
        is_end_by_points = true;
    }
    
}

void KingOfTheHill::updateConquestTeam()
{
    if (!rfid::Worker::getInstance().tagDetected())
    {
        hold_time = 0;
        return;
    }

    //render timer on number display
    led_display::Worker::getInstance().setNumber(hold_time / 1000);

    if (options.is_need_to_hold_button.get())
    {
        if (button::Worker::getInstance().isPressed())
        {
            EVERY_MS(100)
            {
                hold_time += 100;
            }
        }
        
        if (hold_time >= options.hold_time.get())
        {
            changeConquestTeam();
        }
        
    }
    else
    {
        EVERY_MS(100)
        {
            hold_time += 100;
        }
        
        if (hold_time >= options.hold_time.get())
        {
            changeConquestTeam();
        }
    }
    
}

void KingOfTheHill::updateTimer()
{
    HasTimer::updateTimer();

    //render timer on number display
    led_display::Worker::getInstance().setNumber(HasTimer::getTime() / 1000);

    if (is_end_by_time)
    {
        return;
    }

    if (HasTimer::isTimerFinished())
    {
        is_end_by_time = true;
    }
    
}

void KingOfTheHill::updateEndGame()
{
    if (is_end_by_points)
    {
        //beep
        beeper::Worker::getInstance().beepSeconds(TIME_S(10));
        start();
        return;
    }

    if (is_end_by_time)
    {
        //beep
        beeper::Worker::getInstance().beepSeconds(TIME_S(10));
        start();
        return;
    }
    
    
}

void KingOfTheHill::updateSound()
{
    //signal where flag placed
    EVERY_S(2)
    {
        beeper::Worker::getInstance().beepSeconds(TIME_S(1));
    }
}

void KingOfTheHill::changeConquestTeam()
{
    if (!rfid::Worker::getInstance().tagDetected())
    {
        return;
    }

    auto uid = rfid::Worker::getInstance().getUIDCard();

    if (m_uids.find(uid) != m_uids.end())
    {
        m_current_team = m_uids[uid];
        //change team color on led strip
    }
}
