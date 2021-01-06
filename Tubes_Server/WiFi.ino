boolean ConnectWifi(void)
{
  boolean state = true;
  int i = 0;
  WiFi.mode(WIFI_STA);
  WiFi.hostname("pixel_controller");
  MDNS.begin("pixel_controller");
  WiFi.begin(controller_settings.ssid, controller_settings.password);
  Serial.println("");
  Serial.println("Connecting to WiFi");
  
  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(controller_settings.ssid);
    Serial.print("IP address: ");
    Serial.println(IPAddress(WiFi.localIP()));
  } else {
  
    Serial.println("");
    Serial.println("Connection failed. Reverting default network");
    controller_settings.ssid = "";
    controller_settings.password = "";
    store_to_eeprom();
    delay(1000);
    ESP.restart();
  }
  
  return state;
}
