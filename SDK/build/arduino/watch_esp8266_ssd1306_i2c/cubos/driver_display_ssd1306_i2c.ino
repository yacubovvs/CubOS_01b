#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            CUBOS PARAMS / FUNCTION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

void clearscreen_displayDriver(){
  display.clearDisplay();
}

void updatescreen_displayDriver(){
  display.display();
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
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
   display.clearDisplay();
   display.display();
   display.setTextWrap(false);
}

void display_driver_power_off(){
  display.ssd1306_command(SSD1306_DISPLAYOFF);
}

void display_driver_power_on(){
  display.ssd1306_command(SSD1306_DISPLAYON);
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
   display.drawPixel(x, y, WHITE);
  }else if (no_limits){
    display.drawPixel(x, y, WHITE);
  }
  
}

void driver_clearScreen(){
  display.clearDisplay();
}