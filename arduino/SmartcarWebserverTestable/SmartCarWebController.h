#pragma once

#include "CarWithGyroscope.h"
#include "Esp32WebServer.h"

class SmartCarWebController
{
public:
    SmartCarWebController(CarWithGyroscope& car, Esp32WebServer& webServer);

    void registerDriveEndpoint();
    void registerGyroscopeEndpoint();
    void registerErrorHandler();
    void beginServer();
    void update();

private:
    CarWithGyroscope& mCar;
    Esp32WebServer& mWebServer;
};
