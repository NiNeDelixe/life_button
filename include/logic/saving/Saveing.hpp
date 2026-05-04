#ifndef SAVING_SAVEING_HPP_
#define SAVING_SAVEING_HPP_

#include "core/core.hpp"

#include <Preferences.h>
#include <nvs_flash.h>

#include "logic/saving/ISaveble.hpp"


class SaveManager
{
public:
    SaveManager(ISaveble** objs, size_t count)
        : objects(objs), count(count) {
            esp_err_t err_init = nvs_flash_init();
            if (err_init == ESP_ERR_NVS_NO_FREE_PAGES || err_init == ESP_ERR_NVS_NEW_VERSION_FOUND) {
                // NVS partition was truncated and needs to be erased
                // Retry nvs_flash_init
                ESP_ERROR_CHECK(nvs_flash_erase());
                err_init = nvs_flash_init();
            }
            ESP_ERROR_CHECK( err_init );
        }

    virtual ~SaveManager() = default;

    void begin(const char* ns, bool readOnly = false)
    {
        prefs.begin(ns, readOnly);
    }

    void end();

    void forceSave(const char* name)
    {
        end();
        begin(name);
    }

    void saveAll()
    {
        for (size_t i = 0; i < count; ++i)
            objects[i]->save(prefs);
    }

    void loadAll()
    {
        for (size_t i = 0; i < count; ++i)
            objects[i]->load(prefs);
    }

protected:
    Preferences prefs;
    ISaveble** objects;
    size_t count;
};

#endif  // SAVING_SAVEING_HPP_
