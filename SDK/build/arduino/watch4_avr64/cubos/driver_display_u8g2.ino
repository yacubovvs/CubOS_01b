
#include <Arduino.h>
#include <U8g2lib.h>

#include <Wire.h>

#ifdef SCREEN_SSD1306
  U8G2_SSD1306_64X48_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#else
  U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#endif

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            CUBOS PARAMS / FUNCTION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

void clearscreen_displayDriver(){
  driver_clearScreen();
}

void updatescreen_displayDriver(){
  u8g2.sendBuffer();
}

void set_brightness(byte brightness){
  u8g2.setContrast(brightness);  
}

boolean currentColor = 1;

void setDrawColor(byte r, byte g, byte b){
  if (r + g + b > 385) currentColor = 0;
  else currentColor = 1;
}

void setDrawColor_contrast(){
  currentColor = 1;
}

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            INITING ON SETUP
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

void setup_displayDriver(){
  u8g2.begin();

  #ifdef device_has_backlight_control
    set_brightness(get_backlight_light());
  #endif
}

void display_driver_power_off(){
  u8g2.setPowerSave(true);
}

void display_driver_power_on(){
  u8g2.setPowerSave(false);
}

void setPixel(int x, int y){
  setPixel(x, y, false);
}

void setPixel(int x, int y, boolean no_limits){
  if( !(
    x<0 ||
    y<0 ||
    x>SCREEN_WIDTH-1 ||
    y>SCREEN_HEIGHT-1
    )){
    u8g2.drawPixel(
    #ifndef display_invert_y
      x, y
    #else
      SCREEN_WIDTH - 1 - x, SCREEN_HEIGHT - 1 - y
    #endif
    );
      
  }else if (no_limits){
    u8g2.drawPixel(
    #ifndef display_invert_y
      x, y
    #else
      SCREEN_WIDTH - 1 - x, SCREEN_HEIGHT - 1 - y
    #endif
    );
  }
  
}

void driver_clearScreen(){
  u8g2.clearBuffer();
}