#include <ESPmDNS.h>
#include <Smartcar.h>
#include <WiFi.h>

#include "Group20CarWithGyroscope.h"
#include "Group20Esp32WebServer.h"
#include "SmartCarWebController.h"

const auto ssid     = "yourSSID";
const auto password = "yourWifiPassword";

WebServer server(80);

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);

GY50 gyroscope(11);

HeadingCar car(control, gyroscope);

Group20CarWithGyroscope carWrapper{car};
Group20Esp32WebServer serverWrapper{server};

SmartCarWebController smartcarWebController{carWrapper, serverWrapper};

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
