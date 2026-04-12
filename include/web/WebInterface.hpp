#ifndef WEB_WEBINTERFACE_HPP_
#define WEB_WEBINTERFACE_HPP_

#include "core/core.hpp"

#include "game_modes/point_farming/PointFarming.hpp"

#include "externals/led_circuit/Worker.hpp"
//#include "externals/led_display/Worker.hpp"

namespace web
{
    class WebInterface;
};

class web::WebInterface
{
public:
    WebInterface() = default;
    ~WebInterface() = default;

    void onStart();
    void update();

private:
    const char* ssid = "ESP32";
    const char* password = "12345678";
};

static web::WebInterface _interface = web::WebInterface();

#endif  // WEB_WEBINTERFACE_HPP_