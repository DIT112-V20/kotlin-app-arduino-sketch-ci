#ifndef ARDUINO_REFACTORING_FOR_TESTABILITY_MOCKCARWITHGYROSCOPE_HPP
#define ARDUINO_REFACTORING_FOR_TESTABILITY_MOCKCARWITHGYROSCOPE_HPP

#include "CarWithGyroscope.h"
#include "gmock/gmock.h"

class MockCarWithGyroscope : public CarWithGyroscope
{
public:
    MOCK_METHOD(void, setSpeed, (float speed), (override));
    MOCK_METHOD(void, setAngle, (int angle), (override));
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(int, getHeading, (), (override));
};

#endif // ARDUINO_REFACTORING_FOR_TESTABILITY_MOCKCARWITHGYROSCOPE_HPP
