void init_http_server() {
  server.on("/", handleIndex);
  server.on("/status", handleStatus);
  server.on("/universe", handleUniverse);
  server.on("/address", handleAddress);
  server.on("/ch_mode", handleChMode);
  server.on("/device_id", handleDeviceId);
  server.on("/working_mode", handleWorkingMode);
  server.on("/rgb", handleRGB);
  server.on("/restart", handleDeviceRestart);
  server.on("/settings", handleSettings);
  SPIFFS.begin();                           // Start the SPI Flash Files System
  server.onNotFound([]() {                              // If the client requests any URI
    if (!handleFileRead(server.uri()))                  // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });
  server.begin();
  Serial.println("Init http server done");
}

String getContentType(String filename) { // convert the file extension to the MIME type
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
  String contentType = getContentType(path);            // Get the MIME type
  if (SPIFFS.exists(path)) {                            // If the file exists
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = server.streamFile(file, contentType); // And send it to the client
    file.close();                                       // Then close the file again
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;                                         // If the file doesn't exist, return false
}
  
void handleIndex() {
  String text = "Gravity Production";
  server.send(200, "text/plain", text);
}

void handleStatus() {
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

void handleSettings() {
  StaticJsonDocument<309> doc;

  doc["universe"] = dmx_settings.universe;
  doc["address"] = dmx_settings.address;
  doc["ch_mode"] = dmx_settings.ch_mode;
  doc["working_mode"] = dmx_settings.working_mode;
  doc["red"] = dmx_settings.r;
  doc["green"] = dmx_settings.g;
  doc["blue"] = dmx_settings.b;
  doc["firmware"] = firmware_verion;
  IPAddress ip = WiFi.localIP();
  doc["ip"] =  String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
  IPAddress subnet = WiFi.subnetMask();
  doc["mask"] = String(subnet[0]) + "." + String(subnet[1]) + "." + String(subnet[2]) + "." + String(subnet[3]);
  IPAddress gateway = WiFi.gatewayIP();
  doc["geatway"] = String(gateway[0]) + "." + String(gateway[1]) + "." + String(gateway[2]) + "." + String(gateway[3]);

  String out = "";
  serializeJson(doc, out);
  server.send(200, "text/plain", out);
}
