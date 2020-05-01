#include "Group20Esp32WebServer.h"

Group20Esp32WebServer::Group20Esp32WebServer(WebServer& webServer) : mWebServer{webServer} {}

void Group20Esp32WebServer::begin() {
  mWebServer.begin();
}

void Group20Esp32WebServer::on(const char* endpoint, std::function<void()> callback) {
  mWebServer.on(endpoint, callback);
}

void Group20Esp32WebServer::onNotFound(std::function<void()> callback) {
  mWebServer.onNotFound(callback);
}

int Group20Esp32WebServer::args() {
  return mWebServer.args();
}

std::vector<char> Group20Esp32WebServer::argName(int index) {
  const auto name = mWebServer.argName(index);
  std::vector<char> argumentName;
  for (auto c : name) {
    argumentName.emplace_back(c);
  }

  return argumentName;
}

int Group20Esp32WebServer::argToInt(int index) {
  return mWebServer.arg(index).toInt();
}

void Group20Esp32WebServer::send(int errorCode, const char* type, const char* payload) {
  mWebServer.send(errorCode, type, payload);
}

void Group20Esp32WebServer::handleClient() {
  mWebServer.handleClient();
}
