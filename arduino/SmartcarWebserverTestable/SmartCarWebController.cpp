#include "SmartCarWebController.h"

#include <cstdlib>
#include <cstring>

namespace {
const auto kPlainText = "text/plain";
const auto kSuccess = 200;
const auto kError = 404;

bool areEqual(const std::vector<char>& v, const char* c) {
  char characters[v.size() + 1] = {0};
  for (auto i = 0; i < v.size(); i++) {
    characters[i] = v.at(i);
  }

  return strcmp(characters, c) == 0;
}
}

SmartCarWebController::SmartCarWebController(CarWithGyroscope& car, Esp32WebServer& webServer)
  : mCar{car}, mWebServer{webServer} {}

void SmartCarWebController::registerDriveEndpoint() {
  mWebServer.on("/drive", [this]() {
    const auto arguments = mWebServer.args();

    for (auto i = 0; i < arguments; i++) {
      const auto command = mWebServer.argName(i);
      if (areEqual(command, "speed")) {
        mCar.setSpeed(mWebServer.argToInt(i));
      } else if (areEqual(command, "angle")) {
        mCar.setAngle(mWebServer.argToInt(i));
      }
    }
    mWebServer.send(kSuccess, kPlainText, "ok");
  });
}

void SmartCarWebController::registerGyroscopeEndpoint() {
  mWebServer.on("/gyro", [this]() {
    char heading[4];
    itoa(mCar.getHeading(), heading, 10);
    mWebServer.send(kSuccess, kPlainText, heading);
  });
}

void SmartCarWebController::registerErrorHandler() {
  mWebServer.onNotFound([this]() {
    mWebServer.send(kError, kPlainText, "Unknown command");
  });
}

void SmartCarWebController::beginServer() {
  mWebServer.begin();
}

void SmartCarWebController::update() {
  mWebServer.handleClient();
  mCar.update();
}
