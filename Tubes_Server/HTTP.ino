void init_http_server() {
  server.on("/", handleIndex);
  server.on("/wifi", handleWifiSettings);
  server.on("/restart", handleDeviceRestart);
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
  String text = "device created by Gravity team \n";
  text += "Current device SSID: " + String(controller_settings.ssid) + "\n";
  text += "Current device password: " + String(controller_settings.password) + "\n";
  server.send(200, "text/plain", text);
}

void handleWifiSettings() {
  if (server.hasArg("ssid") && server.hasArg("password")) {
    if (check_ssid_raw(server.arg(0), server.arg(1))) {
      String out = "ok, ssid changed to: " + String(controller_settings.ssid);
      out += "\nok, passwordchanged to: " + String(controller_settings.password);
      out += "\nRestarting in 1s";
      server.send(200, "text/plain", out);
      store_to_eeprom();
      delay(1000);
      ESP.restart();
    }
    else
    {
      server.send(404, "text/plain", "not in value range");
    }
  }
  else
  {
    String out = "current ssid is: " + String(controller_settings.ssid);
    out += "\ncurrent passowrd is: " + String(controller_settings.password);
    server.send(200, "text/plain", out);
  }
}

void handleDeviceRestart() {
  server.send(200, "text/plain", "Restarting in 1 second");
  delay(1000);
  ESP.restart();
}
