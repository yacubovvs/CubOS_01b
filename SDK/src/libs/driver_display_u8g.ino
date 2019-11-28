#include <SPI.h>
#include <Wire.h>
#include "U8glib.h"
  
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST); // Dev 0, Fast I2C / TWI
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK); // Display which does not send ACK

 void setup_displayDriver(){

  //U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 
  U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST); // Dev 0, Fast I2C / TWI
  //U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK); // Display which does not send ACK

  u8g.setColorIndex(1);

}

byte framebuffer[1024];
boolean currentColor = 1;

void clearscreen_displayDriver(){
  memset(framebuffer, 0, 1024);
  
  currentColor=1;
}

long m1 = 0;
long m2 = 0;
void updatescreen_displayDriver(){
  //display.display();
  drawDebugString( (int)(m2 - m1), 10); // Время на вывод изображения на экран
  
  m1 = _millis();
  u8g.firstPage();  

  if(while(u8g.nextPage());)
  do{
    u8g.drawBitmap(0,0,16,64, framebuffer);

    /*
    for(int p=0; p<1024; p++){
      for(int pp=0; pp<8; pp++){
        if(framebuffer[p] & (1 << pp)){ 
          //if((p%16)*8 - pp + 7<64 && p/16<32)
          u8g.drawPixel( (p%16)*8 - pp + 7, p/16);
        }
      }
    }*/
  
  }
  

  
  m2 = _millis();

  currentColor = 1;
}

void setDrawColor(byte r, byte g, byte b){
  if (r + g + b > 385) currentColor = 0;
  else currentColor = 1;
}

void setDrawColor_contrast(){
  currentColor = 1;
}


void display_driver_power_off(){
  //display.ssd1306_command(SSD1306_DISPLAYOFF);
  u8g.sleepOn();
}

void display_driver_power_on(){
  //display.ssd1306_command(SSD1306_DISPLAYON);
  u8g.sleepOff();
}

void setPixel(int x, int y){
  setPixel(x, y, false);
}

void setFramebufferPixel(byte x, byte y, boolean color){
  int fb_pos = x + y*128;

  framebuffer[fb_pos/8] |= ( 1 << (7-fb_pos%8) );
  //if (color) framebuffer[fb_pos/8] |= ( 1 << (7-fb_pos%8) );
  //else framebuffer[fb_pos/8] &= ~( 1 << (7-fb_pos%8) );
}

void setPixel(int x, int y, boolean no_limits){
  if( !(
    x<0 ||
    y<0 ||
    x>SCREEN_WIDTH-1 ||
    y>SCREEN_HEIGHT-1
    )){
   //u8g.drawPixel(x, y);
   setFramebufferPixel(x, y, currentColor);
  }else if (no_limits){
    //u8g.drawPixel(x, y);
    setFramebufferPixel(x, y, currentColor);
  }
  
}

void driver_clearScreen(){
  clearscreen_displayDriver();
}