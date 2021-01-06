#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <FS.h>   // Include the SPIFFS library


#define firmware_verion "v1.0.0";

// vars
struct settings {
  String ssid = "Home";
  String password = "9876543210";
};

//objects
settings controller_settings;

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  // load data from eeprom
  load_from_eeprom();
   // connect to wifi
  ConnectWifi();
  // initialization of http server
  init_http_server();
  // initialization and setup of OTA update server
  setup_ota();
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  // put your main code here, to run repeatedly:

}
