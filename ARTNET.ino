void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  if (universe == dmx_settings.universe) {
    if (dmx_settings.ch_mode == 3) {
      for (int led = 0; led < NUM_LEDS; led++) {
        leds[led] = CRGB(data[dmx_settings.address -1], data[dmx_settings.address -1 + 1], data[dmx_settings.address -1 + 2]);
      }
    }
    else if (dmx_settings.ch_mode == 180) {
      for (byte led = 0; led < NUM_LEDS; led++) {
        if (address_check(dmx_settings.address + led * 3) && address_check(dmx_settings.address + led * 3 + 1) && address_check(dmx_settings.address + led * 3 + 2))
        {
          leds[led] = CRGB(data[dmx_settings.address -1 + led * 3], data[dmx_settings.address -1 + led * 3 + 1], data[dmx_settings.address -1 + led * 3 + 2]);
        }
        else {
          break;
        }
      }
    }
    FastLED.show();
  }
}
