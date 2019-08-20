
//unsigned char arrow_right[] = {0b00101111, 0b10110010};
//unsigned char arrow_left[] = {0b10011011, 0b11101000};

const unsigned char arrow_left[]  PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0xff,0xff,0xff,0x10,0x30,0x70,0xF0,0x70,0x30,0x10,0x00,};
const unsigned char arrow_right[] PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0xff,0xff,0xff,0x80,0xC0,0xE0,0xF0,0xE0,0xC0,0x80,0x00,};

const unsigned char arrow_up[] PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0xff,0xff,0xff,0x10,0x38,0x7C,0xFE,0x00,0x00,0x00,0x00,};    //8x4
const unsigned char arrow_down[] PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0xff,0xff,0xff,0xFE,0x7C,0x38,0x10,0x00,0x00,0x00,0x00,};  //8x4

#ifdef colorScreen
  const unsigned char battery_unknown[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFF,0xC7,0xFE,0xFF,0xBB,0xFE,0xFF,0xF7,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFE,0xFF,0xEF,0xFE,0xFF,0xFF,0xFC,};
  const unsigned char battery_100[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFC,0x7F,0xFF,0xFC,0x7F,0xFF,0xFE,0x7F,0xFF,0xFE,0x7F,0xFF,0xFC,0x7F,0xFF,0xFC,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_90[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x7F,0xFF,0xF8,0x7F,0xFF,0xF8,0x7F,0xFF,0xF8,0x7F,0xFF,0xF8,0x7F,0xFF,0xF8,0x7F,0xFF,0xF8,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_80[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_70[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x7F,0xFF,0x00,0x7F,0xFF,0x00,0x7F,0xFF,0x00,0x7F,0xFF,0x00,0x7F,0xFF,0x00,0x7F,0xFF,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_60[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x7F,0xFC,0x00,0x7F,0xFC,0x00,0x7F,0xFC,0x00,0x7F,0xFC,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_50[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x7F,0xE0,0x00,0x7F,0xE0,0x00,0x7F,0xE0,0x00,0x7F,0xE0,0x00,0x7F,0xE0,0x00,0x7F,0xE0,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_40[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x7F,0x80,0x00,0x7F,0x80,0x00,0x7F,0x80,0x00,0x7F,0x80,0x00,0x7F,0x80,0x00,0x7F,0x80,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_30[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_20[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x78,0x00,0x00,0x78,0x00,0x00,0x78,0x00,0x00,0x78,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_10[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_0[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0x00,0x00,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};

  const unsigned char wifi_connected[]      PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0x00,0x66,0xff,0x7E,0x81,0x3C,0x42,0x18,0x24,0x00,0x18,};
  const unsigned char wifi_notconnected[]   PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0x33,0xff,0x00,0x7E,0x81,0x3C,0x42,0x18,0x24,0x00,0x18,};
  const unsigned char wifi_off[]            PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0xb4,0xb4,0xb4,0x7E,0x81,0x3C,0x42,0x18,0x24,0x00,0x18,};
  const unsigned char bt_connected[]        PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0x00,0x66,0xff,0x00,0xE7,0x92,0xE2,0x92,0x92,0xE2,0x00,};
  const unsigned char bt_notconnected[]     PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0xE7,0x92,0xE2,0x92,0x92,0xE2,0x00,};
  const unsigned char bt_off[]              PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0xb4,0xb4,0xb4,0x00,0xE7,0x92,0xE2,0x92,0x92,0xE2,0x00,};

#else
  const unsigned char battery_unknown[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0x00,0x00,0x00,0xFF,0xFF,0xFC,0xFF,0xC7,0xFE,0xFF,0xBB,0xFE,0xFF,0xF7,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFE,0xFF,0xEF,0xFE,0xFF,0xFF,0xFC,};

  const unsigned char battery_100[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFC,};
  const unsigned char battery_90[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFF,0xFF,0xFA,0xFF,0xFF,0xFA,0xFF,0xFF,0xF9,0xFF,0xFF,0xF9,0xFF,0xFF,0xFA,0xFF,0xFF,0xFA,0xFF,0xFF,0xFC,};
  const unsigned char battery_80[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFF,0xFF,0xE2,0xFF,0xFF,0xE2,0xFF,0xFF,0xE1,0xFF,0xFF,0xE1,0xFF,0xFF,0xE2,0xFF,0xFF,0xE2,0xFF,0xFF,0xFC,};
  const unsigned char battery_70[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFF,0xFF,0x82,0xFF,0xFF,0x82,0xFF,0xFF,0x81,0xFF,0xFF,0x81,0xFF,0xFF,0x82,0xFF,0xFF,0x82,0xFF,0xFF,0xFC,};
  const unsigned char battery_60[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFF,0xFC,0x02,0xFF,0xFC,0x02,0xFF,0xFC,0x01,0xFF,0xFC,0x01,0xFF,0xFC,0x02,0xFF,0xFC,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_50[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFF,0xF0,0x02,0xFF,0xF0,0x02,0xFF,0xF0,0x01,0xFF,0xF0,0x01,0xFF,0xF0,0x02,0xFF,0xF0,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_40[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFF,0xC0,0x02,0xFF,0xC0,0x02,0xFF,0xC0,0x01,0xFF,0xC0,0x01,0xFF,0xC0,0x02,0xFF,0xC0,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_30[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xFE,0x00,0x02,0xFE,0x00,0x02,0xFE,0x00,0x01,0xFE,0x00,0x01,0xFE,0x00,0x02,0xFE,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_20[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xF8,0x00,0x02,0xF8,0x00,0x02,0xF8,0x00,0x01,0xF8,0x00,0x01,0xF8,0x00,0x02,0xF8,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_10[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0xE0,0x00,0x02,0xE0,0x00,0x02,0xE0,0x00,0x01,0xE0,0x00,0x01,0xE0,0x00,0x02,0xE0,0x00,0x02,0xFF,0xFF,0xFC,};
  const unsigned char battery_0[]  PROGMEM = {0x02,0x01,0x02,0x18,0x02,0x08,0x04,0xff,0xff,0xff,0xFF,0xFF,0xFC,0x80,0x00,0x02,0x80,0x00,0x02,0x80,0x00,0x01,0x80,0x00,0x01,0x80,0x00,0x02,0x80,0x00,0x02,0xFF,0xFF,0xFC,};

  const unsigned char wifi_connected[]      PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0x00,0x66,0xff,0x7E,0x81,0x3C,0x42,0x18,0x24,0x00,0x18,};
  const unsigned char wifi_notconnected[]   PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0x33,0xff,0x00,0x7E,0x81,0x3C,0x42,0x18,0x24,0x00,0x18,};
  const unsigned char wifi_off[]            PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0xb4,0xb4,0xb4,0x7E,0x81,0x3C,0x42,0x18,0x24,0x00,0x18,};
  const unsigned char bt_connected[]        PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0x00,0x66,0xff,0x00,0xE7,0x92,0xE2,0x92,0x92,0xE2,0x00,};
  const unsigned char bt_notconnected[]     PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0x33,0xff,0x00,0x00,0xE7,0x92,0xE2,0x92,0x92,0xE2,0x00,};
  const unsigned char bt_off[]              PROGMEM = {0x02,0x01,0x02,0x08,0x02,0x08,0x04,0xb4,0xb4,0xb4,0x00,0xE7,0x92,0xE2,0x92,0x92,0xE2,0x00,};
  
    
#endif

const byte* getIcon(byte icon){
  switch (icon){
    case ICON_ARROW_RIGHT:  return arrow_right;
    case ICON_ARROW_LEFT:   return arrow_left;
    case ICON_ARROW_UP:     return arrow_up;
    case ICON_ARROW_DOWN:   return arrow_down;
    case BATTERY_UNKNOWN:   return battery_unknown;
    case BATTERY_100:			  return battery_100;
    case BATTERY_90:			  return battery_90;
    case BATTERY_80:			  return battery_80;
    case BATTERY_70:			  return battery_70;
    case BATTERY_60:			  return battery_60;
    case BATTERY_50:			  return battery_50;
    case BATTERY_40:			  return battery_40;
    case BATTERY_30:			  return battery_30;
    case BATTERY_20:			  return battery_20;
    case BATTERY_10:			  return battery_10;
    case BATTERY_0:			    return battery_0;
    
    case WIFI_CONNECTED:		return wifi_connected;
    case WIFI_NOTCONNECTED:	return wifi_notconnected;
    case WIFI_OFF:			    return wifi_off;
    case BT_CONNECTED:		  return bt_connected;
    case BT_NOTCONNECTED:		return bt_notconnected;
    case BT_OFF:				    return bt_off;
    
    default: return {0};
  }

  
}
