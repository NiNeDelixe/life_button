#include "web/WebInterface.hpp"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "core/Polling.hpp"

#include "pre_builded_headers/index_html.h"
#include "pre_builded_headers/index_css.h"

AsyncWebServer server(80);


void web::WebInterface::onStart()
{
    //WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

    WiFi.softAP(ssid); // 192.168.4.1
    //WiFi.setTxPower(WIFI_POWER_8_5dBm);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });

    server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/css", index_css);
    });

    server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("value")) {
            int v = request->getParam("value")->value().toInt();
            Polling::temp_lf.applyToCounter(v, Counter::operators::SET);
        }
        request->send(200, "text/plain", "OK");
    });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
        int v = Polling::temp_lf.getCount();
        request->send(200, "text/plain", String());
    });

    server.onNotFound([](AsyncWebServerRequest *request){
        Serial.print("404");
        request->send(404, "text/plain", "Not found");
    });

    server.on("/mode", HTTP_GET, [](AsyncWebServerRequest *request){
        int type = request->getParam("type")->value().toInt();

        GameMode* mode = nullptr;
        Polling::mode_manager.crateGameMode(mode, (GameModeType)type);

        // json what settings mode has and default number
        String json;
        switch ((GameModeType)type)
        {
        case GameModeType::LIFES :
            json = "{";
            json += "\"lifes\":3";
            json += "}";
            break;
        case GameModeType::POINT :
            json = "{}";
            break;
        
        case GameModeType::BOMB :
            json = "{";
            json += "\"timer\":45000,";
            json += "\"plant\":10000,";
            json += "\"defuse\":3200";
            json += "}";
            break;
        
        case GameModeType::KOTH :
            json = "{}";
            break;

        default:
            json = "{}";
            break;
        }

        request->send(200, "application/json", json);
    });

    server.on("/setMode", HTTP_GET, [](AsyncWebServerRequest *request){
        int type = request->getParam("type")->value().toInt();

        Polling::mode_manager.crateGameMode((GameModeType)type);
        
        switch ((GameModeType)type)
        {
        case GameModeType::LIFES :
            {
                Lifes* lf = (Lifes*)Polling::mode_manager.getCurrentGameMode();
                if (request->hasParam("lifes")) 
                {
                    int v = request->getParam("lifes")->value().toInt();
                    lf->applyToCounter(v, Counter::operators::SET);
                }
            }
            break;

        case GameModeType::POINT :
            {
                PointFarming* po = (PointFarming*)Polling::mode_manager.getCurrentGameMode();
                po->applyToCounter(0, Counter::operators::SET);
            }
            break;
        
        case GameModeType::BOMB :
            {
                Bomb* bm = (Bomb*)Polling::mode_manager.getCurrentGameMode();
                if (request->hasParam("timer")) 
                {
                    int v = request->getParam("timer")->value().toInt();
                    bm;
                }
                if (request->hasParam("defuse")) 
                {
                    int v = request->getParam("defuse")->value().toInt();
                    bm;
                }
                if (request->hasParam("plant")) 
                {
                    int v = request->getParam("plant")->value().toInt();
                    bm;
                }
            }
            break;
        
        case GameModeType::KOTH :
            break;

        default:
            break;
        }

        request->send(200, "text/plain", "OK");
    });

    server.begin();
    Serial.print("started");
}

void web::WebInterface::update()
{
    //Polling::delay(1000);
    //Serial.print("!");
    // nothing to do
}