#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArtnetWifi.h>
#include <Arduino.h>
#include <FastLED.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

//led
#define NUM_LEDS 60
#define DATA_PIN 4
CRGB leds[NUM_LEDS];

// WiFi
const char *ssid = "Home";
const char *password = "9876543210";

// vars
struct settings {
  byte universe = 0;
  int address = 1;
  byte ch_mode = 180;
  byte device_id = 1;
};

String hostname_str;

//objects
settings dmx_settings;

WiFiUDP UdpSend;
ArtnetWifi artnet;

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  ConnectWifi();
  load_from_eeprom();
  init_http_server();
  pixel_init();
  pixel_initial_test();
  setup_ota();
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
}

void loop(void) {
  ArduinoOTA.handle();
  server.handleClient();
  artnet.read();
}
