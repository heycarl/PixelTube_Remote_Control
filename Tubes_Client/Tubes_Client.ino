#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArtnetnodeWifi.h>
#include <Arduino.h>
#include <FastLED.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <FS.h>   // Include the SPIFFS library


//led
#define NUM_LEDS 60
#define DATA_PIN 4
CRGB leds[NUM_LEDS];

// WiFi
const char *ssid = "Gravity_PixelTubes";
const char *password = "TubesShouldBeUpdated::";

#define firmware_verion "v1.0.2";

// vars
struct settings {
  byte universe = 0;
  int address = 1;
  byte ch_mode = 180;
  byte device_id = 1;
  bool working_mode = 0;
  byte r = 0;
  byte g = 0;
  byte b = 0;
};

String hostname_str;

unsigned long lastDMX_Time = 0;
bool noDMX_Mode = false;

//objects
settings dmx_settings;

WiFiUDP UdpSend;
ArtnetnodeWifi artnetnode;

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  // connect to wifi
  ConnectWifi();
  // load data from eeprom
  load_from_eeprom();
  // initialization of http server
  init_http_server();
  // initialization of ws2812 strip
  pixel_init();
  // RGB test for ws2812 strip
  pixel_initial_test();
  // initialization and setup of OTA update server
  setup_ota();
  // artnet setup
  setupARTNET();
  lastDMX_Time = millis();
}

void loop(void) {
  ArduinoOTA.handle();
  server.handleClient();
  if (!dmx_settings.working_mode) {
    if (millis() - lastDMX_Time > 10000) {
      if (noDMX_Mode == false) {
        noDMX_Mode = true;
        set_static_color(227, 32, 0);
      }
    }
    artnetnode.read();
  }
  else {
    set_static_color(dmx_settings.r, dmx_settings.g, dmx_settings.b);
  }
}
