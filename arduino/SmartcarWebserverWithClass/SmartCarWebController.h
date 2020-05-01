#pragma once

#include <WebServer.h>
#include <Smartcar.h>


class SmartCarWebController {
  public:
    void registerDriveEndpoint();

    void registerGyroscopeEndpoint();

    void registerErrorHandler();

    void beginServer();

    void update();

  private:
    WebServer mWebServer{80};
    BrushedMotor mLeftMotor{smartcarlib::pins::v2::leftMotorPins};
    BrushedMotor mRightMotor{smartcarlib::pins::v2::rightMotorPins};
    DifferentialControl mControl{mLeftMotor, mRightMotor};
    GY50 mGyroscope{11};
    HeadingCar mCar{mControl, mGyroscope};
};
