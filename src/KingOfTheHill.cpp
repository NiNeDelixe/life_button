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

    led_strip::Worker::getInstance().setBehavor(_first_example);
    led_strip::Worker::getInstance().changeColor(100, 100, 100); //white
    //led_bar::Worker::getInstance().turnOff();

    HasCounter::clear();

    HasTimer::setTimer(options.game_time.get());

    is_end_by_points = false;
    is_end_by_time = false;
    m_register_mode = false;

    m_current_team = -1;

    led_bar::Worker::getInstance().setText("Register", 1);
}

void KingOfTheHill::update()
{
    HasTimer::updateTimer();

    // if (is_register_mode == false && button::Worker::getInstance().isPressedOnce())
    // {
    //     is_register_mode = true;
    //     led_bar::Worker::getInstance().setText("Register cards..", 1);
    // }

    // if (is_register_mode == true && button::Worker::getInstance().isPressedOnce())
    // {
    //     auto res = m_teams.find(m_current_team);
    //     if (res != m_teams.end() && res++ != m_teams.end())
    //     {
    //         m_current_team = *(res++);
    //     }
    //     else
    //     {
    //         m_current_team = registerTeam();
    //     }
        
    // }

    if (m_register_mode == true && button::Worker::getInstance().isPressedOnce())
    {
        changeRegisterTeam();
    }
    
    
    updateRegistering();

    if (m_register_mode || m_uids.empty())
    {
        return;
    }
    
    // EVERY_MS(100)
    // {
    //     m_is_holding = false;
    // }
    
    if (!m_is_started && button::Worker::getInstance().isPressedOnce())
    {
        m_is_started = true;
        led_bar::Worker::getInstance().setText("Game Started", 1);
    }

    if (!m_is_started)
    {
        return;
    }
    

    if (updateEndGame())
    {
        return;
    }
    

    // CHANGE TEAM CONQUEST
    updateConquestTeam();
    
    updatePoints();

    updateSound();
}

void KingOfTheHill::registerCards()
{
    // if (!rfid::Worker::getInstance().tagDetected())
    // {
    //     return;
    // }
    
    // auto uid = rfid::Worker::getInstance().getUIDCard();

    // for (size_t i = 0; i < m_uids.size(); i++)
    // {
    //     if (m_uids.find(uid) != m_uids.end())
    //     {
    //         // int team = registerTeam();

    //         // if (team == -1)
    //         // {
    //         //     return;
    //         // }
            
    //         m_uids.insert({uid, m_current_team});

    //         led_bar::Worker::getInstance().setText("Card registered!", 1);
    //     }
    // }
    
    if (!rfid::Worker::getInstance().tagDetected())
    {
        return;
    }

    auto uid = rfid::Worker::getInstance().getUIDCard();

    // led_bar::Worker::getInstance().setText(
    //         uid.toString(),
    //         0
    //     );


    if (m_uids.find(uid) != m_uids.end())
    {
        return;
    }


    m_uids.insert({
        uid,
        m_current_team
    });


    led_bar::Worker::getInstance().setText(
        "Card registered!",
        1
    );
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
    if (is_end_by_points || m_current_team == -1)
    {
        return;
    }
    
    //render points on top display or blink them
    led_bar::Worker::getInstance().setText(getCount().toString(), 1);
    //led_display::Worker::getInstance().setNumber(getCount());

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

    if (options.hold_time.get() == 0)
    {
        changeConquestTeam();
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

bool KingOfTheHill::updateEndGame()
{
    if (is_end_by_points)
    {
        //beep
        beeper::Worker::getInstance().beepSeconds(TIME_S(10));
        led_bar::Worker::getInstance().setText("Game end points!", 1);
        //start();
        return true;
    }

    if (is_end_by_time)
    {
        //beep
        beeper::Worker::getInstance().beepSeconds(TIME_S(10));
        led_bar::Worker::getInstance().setText("Game end by time", 1);
        //start();
        return true;
    }
    
    return false;
}

void KingOfTheHill::updateSound()
{
    //signal where flag placed
    EVERY_S(2)
    {
        beeper::Worker::getInstance().beepSeconds(TIME_S(1));
    }
}

void KingOfTheHill::updateRegistering()
{
    // if (!m_register_mode)
    // {
    //     return;
    // }

    // led_bar::Worker::getInstance().setText(m_current_team.toString() , 1);
    
    
    // registerCards();

    if (!m_register_mode)
    {
        return;
    }

    led_bar::Worker::getInstance().setText(
        m_current_team.toString(),
        1
    );

    registerCards();
}

bool KingOfTheHill::isHoldToStart()
{
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
        if (m_current_team == 1)
        {
            led_strip::Worker::getInstance().changeColor(255, 0, 0);
        }
        if (m_current_team == 2)
        {
            led_strip::Worker::getInstance().changeColor(0, 0, 255);
        }
    }
}

void KingOfTheHill::toggleRegistering()
{
    if (m_register_mode)
    {
        stopRegistering();
    }
    else
    {
        startRegistering();
    }
}

void KingOfTheHill::startRegistering()
{
    m_register_mode = true;

    if (m_current_team == -1)
    {
        m_current_team = registerTeam();
    }

    led_bar::Worker::getInstance().setText(
        "Register cards",
        1
    );
}

void KingOfTheHill::stopRegistering()
{
    m_register_mode = false;

    led_bar::Worker::getInstance().setText(
        "Ready",
        1
    );

    m_current_team = -1;
}

void KingOfTheHill::changeRegisterTeam()
{
    auto it = m_teams.find(m_current_team);

    if (it == m_teams.end())
    {
        m_current_team = registerTeam();
        return;
    }

    ++it;

    if (it == m_teams.end())
    {
        m_current_team = registerTeam();
    }
    else
    {
        m_current_team = *it;
    }
}
