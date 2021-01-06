void load_from_eeprom() {
  settings raw_settings;
  EEPROM.begin(512);
  EEPROM.get(1, raw_settings);
  EEPROM.end();
  if (check_ssid_raw(raw_settings.ssid, raw_settings.password)) {
    Serial.println("Data from eeprom is OK, writing to device.");
    controller_settings = raw_settings;
  }
  else {
    Serial.println("Incorrect data from eeprom, using default settings");
  }
}


void store_to_eeprom() {
  EEPROM.begin(512);
  EEPROM.put(1, controller_settings);
  EEPROM.end();
}
