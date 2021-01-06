void load_from_eeprom() {
  settings raw_settings;
  EEPROM.begin(512);
  EEPROM.get(1, raw_settings);
  EEPROM.end();
  if (check_value_raw(0, raw_settings.universe) && check_value_raw(1, raw_settings.address) && check_value_raw(2, raw_settings.ch_mode)) {
    Serial.println("Data from eeprom is OK, writing to device.");
    dmx_settings = raw_settings;
  }
  else {
    Serial.println("Incorrect data from eeprom, using default settings");
  }
}

void store_to_eeprom() {
  EEPROM.begin(512);
  EEPROM.put(1, dmx_settings);
  EEPROM.end();
}
