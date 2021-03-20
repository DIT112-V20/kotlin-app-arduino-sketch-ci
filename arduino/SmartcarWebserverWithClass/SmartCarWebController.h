#pragma once

#include <Smartcar.h>
#include <WebServer.h>

class SmartCarWebController
{
public:
    void registerDriveEndpoint();

    void registerGyroscopeEndpoint();

    void registerErrorHandler();

    void beginServer();

    void update();

private:
    WebServer mWebServer{80};
    ArduinoRuntime mArduinoRuntime;
    BrushedMotor mLeftMotor{mArduinoRuntime, smartcarlib::pins::v2::leftMotorPins};
    BrushedMotor mRightMotor{mArduinoRuntime, smartcarlib::pins::v2::rightMotorPins};
    DifferentialControl mControl{mLeftMotor, mRightMotor};
    GY50 mGyroscope{mArduinoRuntime, 11};
    HeadingCar mCar{mControl, mGyroscope};
};
