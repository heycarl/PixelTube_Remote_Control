bool check_ssid_raw(String ssid_raw, String password_raw) {
  if (ssid_raw != "" and password_raw != "") {
    Serial.println("");
    controller_settings.ssid = ssid_raw;
    controller_settings.password = password_raw;
    Serial.println("SSID changed to: " + ssid_raw);
    Serial.println("PASSWORD changed to: " + password_raw);
    return true;
  }
  else
  {
    return false;
  }
}
