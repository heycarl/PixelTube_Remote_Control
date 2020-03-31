void pixel_init () {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void pixel_initial_test() {
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(127, 0, 0);
  }
  FastLED.show();
  delay(1000);
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(0, 127, 0);
  }
  FastLED.show();
  delay(1000);
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(0, 0, 127);
  }
  FastLED.show();
  delay(1000);
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void set_static_color(byte red, byte green, byte blue) {
  for (byte led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB(red, green, blue);
  }
  FastLED.show();
}
