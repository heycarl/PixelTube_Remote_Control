bool check_value_range(byte check_type, int value){
  switch (check_type)
  {
  case 0:
    if (value > -1 and value < 16){
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
    if (value > 0 and value < 513){
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
    if (value == 3 or value == 177){
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
  default:
    return false;
    break;
  }
}

bool check_value_raw(byte check_type, int value){
  switch (check_type)
  {
  case 0:
    if (value > -1 and value < 16){
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
    if (value > 0 and value < 513){
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
    if (value == 3 or value == 177){
      Serial.println("Channel mode from raw: " + String(value));
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
