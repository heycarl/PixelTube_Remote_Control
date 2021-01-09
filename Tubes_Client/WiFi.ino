boolean ConnectWifi(void)
{
  boolean state = true;
  int i = 0;
  WiFi.mode(WIFI_STA);
  WiFi.hostname("pixel-" + String(dmx_settings.device_id));
  MDNS.begin("pixel-" + String(dmx_settings.device_id));
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(IPAddress(WiFi.localIP()));
  } else {
    Serial.println("");
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    Serial.println("Connection failed.");
    set_static_color(48, 77, 255);
    delay(1000);
    set_static_color(0, 0, 0);
    delay(1000);
    set_static_color(48, 77, 255);
    delay(1000);
    set_static_color(0, 0, 0);
    delay(1000);
    set_static_color(48, 77, 255);
    delay(1000);
    set_static_color(0, 0, 0);
    delay(20000);
    ConnectWifi();
  }
  return state;
}
