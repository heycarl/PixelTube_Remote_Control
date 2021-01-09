bool check_value_range(byte check_type, int value) {
  switch (check_type)
  {
    case 0:
      if (value > -1 and value < 16) {
        dmx_settings.universe = value;
        Serial.println("Universe: " + String(dmx_settings.universe));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    case 1:
      if (value > 0 and value < 513) {
        dmx_settings.address = value;
        Serial.println("Address: " + String(dmx_settings.address));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    case 2:
      if (value == 3 or value == 180) {
        dmx_settings.ch_mode = value;
        Serial.println("Channel mode: " + String(dmx_settings.ch_mode));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    case 3:
      if (value > -1 and value < 255) {
        dmx_settings.device_id = value;
        Serial.println("Device id : " + String(value));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    case 4:
      if (value == 0 or value == 1) {
        dmx_settings.working_mode = value;
        Serial.println("Working Mode : " + String(value));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    default:
      return false;
      break;
  }
}

bool rgb_check(int red, int green, int blue) {
  if (red > -1 and red < 256 and green > -1 and green < 256 and blue > -1 and blue < 256) {
    dmx_settings.r = red;
    dmx_settings.g = green;
    dmx_settings.b = blue;
    Serial.println("Static color changed to: " + String(red) + " " + String(green) + " " + String(blue));
    return true;
  }
  else
  {
    return false;
  }
}


bool address_check(int value) {
  if (value > 0 and value < 513) {
    return true;
  }
  else
  {
    return false;
  }
}

bool check_value_raw(byte check_type, int value) {
  switch (check_type)
  {
    case 0:
      if (value > -1 and value < 16) {
        Serial.println("Universe from raw: " + String(value));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    case 1:
      if (value > 0 and value < 513) {
        Serial.println("Address from raw: " + String(value));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    case 2:
      if (value == 3 or value == 180) {
        Serial.println("Channel mode from raw: " + String(value));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    case 3:
      if (value > -1 and value < 255) {
        Serial.println("Device id from raw: " + String(value));
        return true;
        break;
      }
      else
      {
        return false;
        break;
      }
    default:
      return false;
      break;
  }
}
