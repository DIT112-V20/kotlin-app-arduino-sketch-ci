// Use a .ino file and comment the line below until #21 is fixed
// #include "SmartCarWebController.h"

#include <Arduino.h>

namespace
{
const auto kPlainText = "text/plain";
const auto kSuccess   = 200;
const auto kError     = 404;
} // namespace

void SmartCarWebController::registerDriveEndpoint()
{
    mWebServer.on("/drive", [this]() {
        const auto arguments = mWebServer.args();

        for (auto i = 0; i < arguments; i++)
        {
            const auto command = mWebServer.argName(i);
            if (command == "speed")
            {
                mCar.setSpeed(mWebServer.arg(i).toInt());
            }
            else if (command == "angle")
            {
                mCar.setAngle(mWebServer.arg(i).toInt());
            }
        }
        mWebServer.send(kSuccess, kPlainText, "ok");
    });
}

void SmartCarWebController::registerGyroscopeEndpoint()
{
    mWebServer.on("/gyro", [this]() {
        mWebServer.send(kSuccess, kPlainText, String(mCar.getHeading()));
    });
}

void SmartCarWebController::registerErrorHandler()
{
    mWebServer.onNotFound(
        [this]() { mWebServer.send(kError, kPlainText, "Unknown command"); });
}

void SmartCarWebController::beginServer()
{
    mWebServer.begin();
}

void SmartCarWebController::update()
{
    mWebServer.handleClient();
    mCar.update();
}
