#include "logic/saving/Saveing.hpp"

//#include "core/Polling.hpp"

void SaveManager::end()
{
    prefs.end();
    //Polling::delay(100);
}