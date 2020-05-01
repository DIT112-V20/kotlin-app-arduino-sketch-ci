#include "Group20CarWithGyroscope.h"

Group20CarWithGyroscope::Group20CarWithGyroscope(HeadingCar& car) : mCar{car} {}

void Group20CarWithGyroscope::setSpeed(float speed) {
  mCar.setSpeed(speed);
}

void Group20CarWithGyroscope::setAngle(int angle) {
  mCar.setAngle(angle);
}

void Group20CarWithGyroscope::update() {
  mCar.update();
}

int Group20CarWithGyroscope::getHeading() {
  return mCar.getHeading();
}
