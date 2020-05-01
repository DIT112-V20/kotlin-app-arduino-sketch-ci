#include "MockCarWithGyroscope.hpp"
#include "MockEsp32WebServer.hpp"
#include "SmartCarWebController.h"
#include "gtest/gtest.h"

using namespace testing;

namespace
{
const auto kSuccess = 200;
const auto kError   = 404;
const std::vector kDummyName{'a', 'b', 'c', '\0'};
const std::vector kSpeed{'s', 'p', 'e', 'e', 'd', '\0'};
const std::vector kAngle{'a', 'n', 'g', 'l', 'e', '\0'};
} // namespace

struct SmartCarWebControllerTest : public Test
{
    MockCarWithGyroscope mCar;
    MockEsp32WebServer mWebServer;
    SmartCarWebController mSmartCarWebController{mCar, mWebServer};
};

struct DriveEndpointTest : public Test
{
    void SetUp() override
    {
        EXPECT_CALL(mWebServer, on(_, _)).WillOnce(SaveArg<1>(&mCallback));
        ON_CALL(mWebServer, argName(_)).WillByDefault(Return(kDummyName));

        mSmartCarWebController.registerDriveEndpoint();
    }

    MockCarWithGyroscope mCar;
    MockEsp32WebServer mWebServer;
    SmartCarWebController mSmartCarWebController{mCar, mWebServer};
    std::function<void()> mCallback;
};

TEST_F(SmartCarWebControllerTest,
       registerDriveEndpoint_WhenCalled_WillRegisterEndpoint)
{
    EXPECT_CALL(mWebServer, on(StrEq("/drive"), _));

    mSmartCarWebController.registerDriveEndpoint();
}

TEST_F(SmartCarWebControllerTest,
       registerGyroscopeEndpoint_WhenCalled_WillRegisterEndpoint)
{
    EXPECT_CALL(mWebServer, on(StrEq("/gyro"), _));

    mSmartCarWebController.registerGyroscopeEndpoint();
}

TEST_F(SmartCarWebControllerTest, gyroscopeEndpoint_WhenCalled_WillSendHeading)
{
    std::function<void()> callback;
    EXPECT_CALL(mWebServer, on(_, _)).WillOnce(SaveArg<1>(&callback));
    mSmartCarWebController.registerGyroscopeEndpoint();

    const auto heading = 334;
    EXPECT_CALL(mCar, getHeading()).WillOnce(Return(heading));
    EXPECT_CALL(mWebServer,
                send(kSuccess, _, StrEq(std::to_string(heading).c_str())));

    callback();
}

TEST_F(SmartCarWebControllerTest,
       registerErrorHandler_WhenCalled_WillRegisterErrorHandler)
{
    EXPECT_CALL(mWebServer, onNotFound(_));

    mSmartCarWebController.registerErrorHandler();
}

TEST_F(SmartCarWebControllerTest, errorEndpoint_WhenCalled_WillSendError)
{
    std::function<void()> callback;
    EXPECT_CALL(mWebServer, onNotFound(_)).WillOnce(SaveArg<0>(&callback));
    mSmartCarWebController.registerErrorHandler();

    EXPECT_CALL(mWebServer, send(kError, _, _));
    callback();
}

TEST_F(SmartCarWebControllerTest, beginServer_WhenCalled_WillBeginServer)
{
    EXPECT_CALL(mWebServer, begin());

    mSmartCarWebController.beginServer();
}

TEST_F(SmartCarWebControllerTest, update_WhenCalled_WillUpdateServerAndCar)
{
    EXPECT_CALL(mWebServer, handleClient());
    EXPECT_CALL(mCar, update());

    mSmartCarWebController.update();
}

TEST_F(DriveEndpointTest, callback_WhenCalled_WillSendSuccess)
{
    EXPECT_CALL(mWebServer, send(kSuccess, _, _));
    mCallback();
}

TEST_F(DriveEndpointTest, callback_WhenNoArguments_WillNotFetchArguments)
{
    EXPECT_CALL(mWebServer, args()).WillOnce(Return(0));
    EXPECT_CALL(mWebServer, argName(_)).Times(0);

    mCallback();
}

TEST_F(DriveEndpointTest, callback_WhenArguments_WillGetAllArguments)
{
    const auto numberOfArguments = 8438;
    EXPECT_CALL(mWebServer, args()).WillOnce(Return(numberOfArguments));
    EXPECT_CALL(mWebServer, argName(_)).Times(numberOfArguments);

    mCallback();
}

TEST_F(DriveEndpointTest, callback_WhenSpeedAsArgument_WillSetSpeed)
{
    const auto speed = 512;
    EXPECT_CALL(mWebServer, args()).WillOnce(Return(1));
    EXPECT_CALL(mWebServer, argName(_)).WillOnce(Return(kSpeed));
    EXPECT_CALL(mWebServer, argToInt(_)).WillOnce(Return(speed));
    EXPECT_CALL(mCar, setSpeed(static_cast<float>(speed)));

    mCallback();
}

TEST_F(DriveEndpointTest, callback_WhenAngleAsArgument_WillSetAngle)
{
    const auto angle = 843;
    EXPECT_CALL(mWebServer, args()).WillOnce(Return(1));
    EXPECT_CALL(mWebServer, argName(_)).WillOnce(Return(kAngle));
    EXPECT_CALL(mWebServer, argToInt(_)).WillOnce(Return(angle));
    EXPECT_CALL(mCar, setAngle(angle));

    mCallback();
}

TEST_F(DriveEndpointTest,
       callback_WhenSpeedAndAngleAsArgument_WillSetSpeedAndAngle)
{
    const auto angle = -843;
    const auto speed = -512;
    EXPECT_CALL(mWebServer, args()).WillOnce(Return(2));
    EXPECT_CALL(mWebServer, argName(_))
        .WillOnce(Return(kAngle))
        .WillOnce(Return(kSpeed));
    EXPECT_CALL(mWebServer, argToInt(_))
        .WillOnce(Return(angle))
        .WillOnce(Return(speed));
    EXPECT_CALL(mCar, setAngle(angle));
    EXPECT_CALL(mCar, setSpeed(static_cast<float>(speed)));

    mCallback();
}
