#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Smartcar.h>

const auto ssid = "HoneyJar";
const auto password = "krukuschFR0NG69382!?";

WebServer server(80);

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);

GY50 gyroscope(11);

HeadingCar car(control, gyroscope);

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("smartcar")) {
    Serial.println("MDNS responder started");
  }

  server.on("/drive", []() {
    const auto arguments = server.args();
    
    for (auto i = 0; i < arguments; i++) {
      const auto command = server.argName(i);
      if (command == "speed") {
        car.setSpeed(server.arg(i).toInt());
      } else if (command == "angle") {
        car.setAngle(server.arg(i).toInt());
      }
    }
    server.send(200, "text/plain", "ok");
  });


  server.on("/gyro", []() {
    char heading[4];
    itoa(car.getHeading(), heading, 10);
    server.send(200, "text/plain", heading);
  });

  server.onNotFound([]() {
    server.send(404, "text/plain", "Unknown command");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  car.update();
}
