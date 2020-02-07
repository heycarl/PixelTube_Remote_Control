void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  //
  //  Serial.print("DMX: Univ: ");
  //  Serial.print(universe, DEC);
  //  Serial.print(", Seq: ");
  //  Serial.print(sequence, DEC);
  //  Serial.print(", Data (");
  //  Serial.print(length, DEC);
  //  Serial.print("): ");

  if (universe == dmx_settings.universe) {
    if (dmx_settings.ch_mode == 3) {
      for (int led = 0; led < NUM_LEDS; led++) {
        leds[led] = CRGB(data[dmx_settings.address], data[dmx_settings.address + 1], data[dmx_settings.address + 2]);
      }
    }
    else if (dmx_settings.ch_mode == 177) {
      for (int i = 0; i < length / 3; i++)
      {
        if (led < numLeds)
          leds[led] = CRGB(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
      }
    }
    FastLED.show();
  }

  //for (int i = dmx_settings.address; i < length; i++)
  //{
  //        Serial.print(data[i], HEX);
  //        Serial.print(" ");
  //}
