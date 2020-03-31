void init_http_server() {
  server.on("/", handleRoot);
  server.on("/universe", handleUniverse);
  server.on("/address", handleAddress);
  server.on("/ch_mode", handleChMode);
  server.on("/device_id", handleDeviceId);
  server.on("/working_mode", handleWorkingMode);
  server.on("/rgb", handleRGB);
  server.on("/restart", handleDeviceRestart);
  server.begin();
  Serial.println("Init http server done");
}

void handleRoot() {
  String text = "device created by Gravity team \n";
  text += "Current device universe: " + String(dmx_settings.universe) + "\n";
  text += "Current device address: " + String(dmx_settings.address) + "\n";
  text += "Current device channel mode: " + String(dmx_settings.ch_mode) + "\n";
  text += "Current device working mode: " + working_mode_to_string() + "\n";
  text += "Static color RED: " + String(dmx_settings.r) + "\n";
  text += "Static color GREEN: " + String(dmx_settings.g) + "\n";
  text += "Static color BLUE: " + String(dmx_settings.b) + "\n";
  text += "Current device id: " + hostname_str + "\n";
  server.send(200, "text/plain", text);
}

void handleUniverse() {
  if (server.hasArg("value")) {
    if (check_value_range(0, server.arg(0).toInt())) {
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
    if (check_value_range(1, server.arg(0).toInt())) {
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
    if (check_value_range(2, server.arg(0).toInt())) {
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

void handleDeviceId() {
  if (server.hasArg("value")) {
    if (check_value_range(3, server.arg(0).toInt())) {
      server.send(200, "text/plain", "ok, changed to: " + String(dmx_settings.device_id));
      store_to_eeprom();
    }
    else
    {
      server.send(404, "text/plain", "not in value range");
    }
  }
  else
  {
    server.send(200, "text/plain", "current value is: " + String(dmx_settings.device_id));
  }
}

void handleWorkingMode() {
  if (server.hasArg("value")) {
    if (check_value_range(4, server.arg(0).toInt())) {
      server.send(200, "text/plain", "ok, changed to: " + String(dmx_settings.working_mode));
      store_to_eeprom();
    }
    else
    {
      server.send(404, "text/plain", "not in value range");
    }
  }
  else
  {
    server.send(200, "text/plain", "current value is: " + String(dmx_settings.working_mode));
  }
}

void handleRGB() {
  if (server.hasArg("red") and server.hasArg("green") and server.hasArg("blue")) {
    if (rgb_check(server.arg(0).toInt(), server.arg(1).toInt(), server.arg(2).toInt())) {
      server.send(200, "text/plain", "ok, changed to: " + String(dmx_settings.r) + " " + String(dmx_settings.g) + " " + String(dmx_settings.b));
      store_to_eeprom();
    }
    else
    {
      server.send(404, "text/plain", "not in value range");
    }
  }
  else
  {
    server.send(200, "text/plain", "Static color is: " + String(dmx_settings.r) + " " + String(dmx_settings.g) + " " + String(dmx_settings.b));
  }
}

void handleDeviceRestart() {
  server.send(200, "text/plain", "Restarting in 1 second");
  delay(1000);
  ESP.restart();
}
