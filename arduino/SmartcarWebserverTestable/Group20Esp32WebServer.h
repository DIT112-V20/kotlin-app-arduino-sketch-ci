#pragma once

#include "Esp32WebServer.h"
#include <WebServer.h>

class Group20Esp32WebServer : public Esp32WebServer {
  public:
    Group20Esp32WebServer(WebServer& webServer);

    void begin() override;
    void on(const char* endpoint, std::function<void()> callback) override;
    void onNotFound(std::function<void()> callback) override;
    int args() override;
    std::vector<char> argName(int index) override;
    int argToInt(int index) override;
    void send(int errorCode, const char* type, const char* payload) override;
    void handleClient() override;

  private:
    WebServer& mWebServer;
};
