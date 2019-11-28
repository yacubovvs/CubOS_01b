
#include <Arduino.h>
#include <U8g2lib.h>

#include <Wire.h>


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            CUBOS PARAMS / FUNCTION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

void clearscreen_displayDriver(){
  //display.clearDisplay();
}

void updatescreen_displayDriver(){
  //display.display();
  //u8g2_prepare();
  
  u8g2.sendBuffer();
  u8g2.clearBuffer();
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
   //display.begin(SSD1306_SWITCHCAPVCC);
   //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
   u8g2.begin();

   /*
   Adafruit_SH1106 display(OLED_RESET);
   display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
   display.clearDisplay();
   display.display();
   display.setTextWrap(false);
   */
}

void display_driver_power_off(){
  //display.ssd1306_command(SSD1306_DISPLAYOFF);
  u8g2.setPowerSave(false);
}

void display_driver_power_on(){
  //display.ssd1306_command(SSD1306_DISPLAYON);
  u8g2.setPowerSave(true);
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
  //display.clearDisplay();
}
