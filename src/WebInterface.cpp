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
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_AP_STA);
    
    // Создание уникального SSID
    uint8_t mac[6];
    WiFi.macAddress(mac);
    snprintf(ssid, sizeof(ssid), "ESP_%02X%02X%02X%02X%02X%02X", 
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    WiFi.softAP(ssid); // 192.168.4.1
    WiFi.setTxPower(WIFI_POWER_8_5dBm);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });

    server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/css", index_css);
    });

    server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("value")) {
            int v = request->getParam("value")->value().toInt();
            //Polling::temp_lf.applyToCounter(v, Counter::operators::SET);
        }
        request->send(200, "text/plain", "OK");
    });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
        //int v = Polling::temp_lf.getCount();
        request->send(200, "text/plain", String());
    });

    server.onNotFound([](AsyncWebServerRequest *request){
        Serial.print("404");
        request->send(404, "text/plain", "Not found");
    });

    server.on("/getCurrentMode", HTTP_GET, [](AsyncWebServerRequest *request) {
        GameModeType curr_type = Polling::mode_manager.getCurrentGameType();
        
        uint8_t t = (uint8_t)curr_type;

        char* buff;
        sprintf(buff, "%d", t);
        
        request->send(200, "text/plain", buff);
    });

    server.on("/restart", HTTP_GET, [](AsyncWebServerRequest *request) {
        Polling::mode_manager.getCurrentGameMode()->start();
        
        request->send(200, "text/plain", "OK");
    });

    server.on("/mode", HTTP_GET, [](AsyncWebServerRequest *request){
        int type = request->getParam("type")->value().toInt();

        // GameMode* mode = nullptr;
        // Polling::mode_manager.crateGameMode((GameModeType)type);

        // json what settings mode has and default number
        String json;
        switch ((GameModeType)type)
        {
        case GameModeType::LIFES :
            json = "{";
            json += "\"lifes\":70,";
            json += "\"timer\":4294967.294";
            json += "}";
            break;
        case GameModeType::POINT :
            json = "{";
            json += "\"timer\":4294967.294,";
            json += "\"operation_value\":1,";
            json += "\"start_value\":0,";
            json += "\"operation_type\":[0,1,2]";
            json += "}";
            break;
        
        case GameModeType::BOMB :
            json = "{";
            json += "\"timer\":45,";
            json += "\"defuse\":10,";
            json += "\"plant\":3.2";
            json += "}";
            break;
        
        case GameModeType::KOTH :
            json = "{";
            json += "\"game_time\":4294967.294,";
            json += "\"hold_time\":5,";
            json += "\"points_multiplier\":1,";
            json += "\"is_need_to_hold_button\":false,";
            json += "\"points_to_win\":10000";
            json += "}";
            break;

        case GameModeType::SYNC_START :
            json = "{";
            json += "\"timer\":5";
            json += "}";
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
                    //lf->applyToCounter(v, Counter::operators::SET);
                    lf->options.lifes_option.set(v);
                }
                if (request->hasParam("timer")) 
                {
                    int v = request->getParam("timer")->value().toInt();
                    //lf->setTimer(v);
                    lf->options.timer_option.set(TIME_S(v));
                }
                lf->start();
            }
            break;

        case GameModeType::POINT :
            {
                PointFarming* po = (PointFarming*)Polling::mode_manager.getCurrentGameMode();
                if (request->hasParam("timer")) 
                {
                    int v = request->getParam("timer")->value().toInt();
                    po->options.timer.set(TIME_S(v));
                }
                if (request->hasParam("operation_value")) 
                {
                    int v = request->getParam("operation_value")->value().toInt();
                    po->options.operation_value.set(v);
                }
                if (request->hasParam("start_value")) 
                {
                    int v = request->getParam("start_value")->value().toInt();
                    po->options.start_value.set(v);
                }
                if (request->hasParam("operation_type")) 
                {
                    //int v = request->getParam("operation_type")->value().toInt();
                    //po->options.operation_type.set(v);
                }
            }
            break;
        
        case GameModeType::BOMB :
            {
                Bomb* bm = (Bomb*)Polling::mode_manager.getCurrentGameMode();
                if (request->hasParam("timer")) 
                {
                    int v = request->getParam("timer")->value().toInt();
                    bm->options.timer_option.set(TIME_S(v));
                }
                if (request->hasParam("defuse")) 
                {
                    int v = request->getParam("defuse")->value().toInt();
                    bm->options.defuse_option.set(TIME_S(v));
                }
                if (request->hasParam("plant")) 
                {
                    int v = request->getParam("plant")->value().toInt();
                    bm->options.plant_option.set(TIME_S(v));
                }
            }
            break;
        
        case GameModeType::KOTH :
            {
                KingOfTheHill* koth = (KingOfTheHill*)Polling::mode_manager.getCurrentGameMode();
                if (request->hasParam("game_time")) 
                {
                    int v = request->getParam("game_time")->value().toInt();
                    koth->options.game_time.set(TIME_S(v));
                }
                if (request->hasParam("hold_time")) 
                {
                    int v = request->getParam("hold_time")->value().toInt();
                    koth->options.hold_time.set(TIME_S(v));
                }
                if (request->hasParam("is_need_to_hold_button")) 
                {
                    bool v = request->getParam("is_need_to_hold_button")->value().toInt();
                    koth->options.is_need_to_hold_button.set(v);
                }
                if (request->hasParam("points_multiplier")) 
                {
                    int v = request->getParam("points_multiplier")->value().toInt();
                    koth->options.points_multiplier.set(v);
                }
                if (request->hasParam("points_to_win")) 
                {
                    int v = request->getParam("points_to_win")->value().toInt();
                    koth->options.points_to_win.set(v);
                }
            }
            break;

        case GameModeType::SYNC_START :
            {
                SyncStart* ss = (SyncStart*)Polling::mode_manager.getCurrentGameMode();
                if (request->hasParam("timer")) 
                {
                    int v = request->getParam("timer")->value().toInt();
                    ss->options.timer.set(TIME_S(v));
                }
            }
            break;

        default:
            break;
        }

        Polling::mode_manager.saveCurrent();

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