#pragma once

#include "CarWithGyroscope.h"
#include <car/heading/HeadingCar.hpp>

class Group20CarWithGyroscope : public CarWithGyroscope
{
public:
    Group20CarWithGyroscope(HeadingCar& car);

    void setSpeed(float speed) override;
    void setAngle(int angle) override;
    void update() override;
    int getHeading() override;

private:
    HeadingCar& mCar;
};
