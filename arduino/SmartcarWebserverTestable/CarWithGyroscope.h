#pragma once

struct CarWithGyroscope {
  virtual ~CarWithGyroscope() = default;

  virtual void setSpeed(float speed) = 0;
  virtual void setAngle(int angle) = 0;
  virtual void update() = 0;
  virtual int getHeading() = 0;
};
