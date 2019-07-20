#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_MOSI D7 //d1
#define OLED_CLK D5 //d0
#define OLED_DC D2
#define OLED_CS D8
#define OLED_RESET D1
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            CUBOS PARAMS / FUNCTION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/
#define LCD_WIDTH   128 // Note: x-coordinates go wide
#define LCD_HEIGHT  64  // Note: y-coordinates go high

void clearscreen_displayDriver(){
  display.clearDisplay();
}

void updatescreen_displayDriver(){
  display.display();
}

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            INITING ON SETUP
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

void setup_displayDriver(){
   display.begin(SSD1306_SWITCHCAPVCC);
   display.clearDisplay();
   display.display();
   display.setTextWrap(false);
   
   pinMode(D0, INPUT); 
   pinMode(D3, INPUT); 
   pinMode(D4, INPUT); 
   pinMode(D6, INPUT); 
   pinMode(D9, INPUT);
   pinMode(D10, INPUT);
}

void setStr(char * dString, int x, int y){
  display.setTextColor(WHITE);  //  задаем цвет
  display.setTextSize(1);  //  задаем шрифт
  display.setCursor(x,y);  //  задаем координаты курсора
  display.print(dString);
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