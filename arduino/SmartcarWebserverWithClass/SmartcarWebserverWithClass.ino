#include <ESPmDNS.h>
#include <WiFi.h>

#include "SmartCarWebController.h"

const auto ssid     = "yourSSID";
const auto password = "yourWifiPassword";

SmartCarWebController smartcarWebController;

void setup(void)
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("smartcar"))
    {
        MDNS.addService("http", "tcp", 80);
        Serial.println("MDNS responder started");
    }

    smartcarWebController.registerDriveEndpoint();

    smartcarWebController.registerGyroscopeEndpoint();

    smartcarWebController.registerErrorHandler();

    smartcarWebController.beginServer();

    Serial.println("HTTP server started");
}

void loop(void)
{
    smartcarWebController.update();
}
