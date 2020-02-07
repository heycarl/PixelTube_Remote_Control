void init_http_server() {
  server.on("/", handleRoot);
  server.on("/universe", handleUniverse);
  server.on("/address", handleAddress);
  server.on("/ch_mode", handleChMode);
  server.begin();
  Serial.println("Init http server done");
}

void handleRoot() {
  server.send(200, "text/plain", "by Gravity");
}

void handleUniverse() {
  if (server.hasArg("value")) {
    if (check_value_range(0, server.arg(0).toInt())){
      server.send(200, "text/plain", "ok, changed to: " + String(dmx_settings.universe));
      store_to_eeprom();
    }
    else
    {
      server.send(404, "text/plain", "not in value range");
    }
  }
  else
  {
    server.send(200, "text/plain", "current value is: " + String(dmx_settings.universe));
  }
}

void handleAddress() {
  if (server.hasArg("value")) {
    if (check_value_range(1, server.arg(0).toInt())){
      server.send(200, "text/plain", "ok, changed to: " + String(dmx_settings.address));
      store_to_eeprom();
    }
    else
    {
      server.send(404, "text/plain", "not in value range");
    }
  }
  else
  {
    server.send(200, "text/plain", "current value is: " + String(dmx_settings.address));
  }
}

void handleChMode() {
  if (server.hasArg("value")) {
    if (check_value_range(2, server.arg(0).toInt())){
      server.send(200, "text/plain", "ok, changed to: " + String(dmx_settings.ch_mode));
      store_to_eeprom();
    }
    else
    {
      server.send(404, "text/plain", "not in value range");
    }
  }
  else
  {
    server.send(200, "text/plain", "current value is: " + String(dmx_settings.ch_mode));
  }
}
