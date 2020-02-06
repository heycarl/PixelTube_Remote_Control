#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const char *ssid = "Home";
const char *password = "9876543210";

struct settings{
  byte universe = 0;
  int address = 1;
  byte ch_mode = 177;
};

settings dmx_settings;

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  ConnectWifi();
  load_from_eeprom();
  init_http_server();
}

void loop(void) {
  server.handleClient();
}
