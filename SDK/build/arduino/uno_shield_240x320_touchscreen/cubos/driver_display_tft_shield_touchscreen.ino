//#include <UTFTGLUE.h>              
#include "libs_h/MCUFRIEND_kbv/UTFTGLUE.h"              
UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0);

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            CUBOS PARAMS / FUNCTION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

int drawLimit_x_min = 0;
int drawLimit_y_min = 0;
int drawLimit_x_max = SCREEN_WIDTH;
int drawLimit_y_max = SCREEN_HEIGHT;

void set_DrawLimits(int min_x, int min_y, int max_x, int max_y){
  drawLimit_x_min = min_x;
  drawLimit_y_min = min_y;
  drawLimit_x_max = max_x;
  drawLimit_y_max = max_y;
}

LINEARHASH_TYPE linear_framebuffer_x[SCREEN_WIDTH/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE];   // Low memory hash framebuffer idea by Yacubov Vitaly
LINEARHASH_TYPE linear_framebuffer_y[SCREEN_HEIGHT/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE];  // Low memory hash framebuffer idea by Yacubov Vitaly
LINEARHASH_TYPE linear_framebuffer_x2[SCREEN_WIDTH/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE];   // Low memory hash framebuffer idea by Yacubov Vitaly
LINEARHASH_TYPE linear_framebuffer_y2[SCREEN_HEIGHT/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE];  // Low memory hash framebuffer idea by Yacubov Vitaly
LINEARHASH_TYPE linear_framebuffer_x_new[SCREEN_WIDTH/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE];   // Low memory hash framebuffer idea by Yacubov Vitaly
LINEARHASH_TYPE linear_framebuffer_y_new[SCREEN_HEIGHT/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE];  // Low memory hash framebuffer idea by Yacubov Vitaly

void setup_displayDriver(){
  randomSeed(analogRead(0));
  myGLCD.InitLCD();
  //myGLCD.setFont(SmallFont);
  //myGLCD.wrap(false)
  myGLCD.setRotation(PORTRAIT);

  setDrawColor_background();
  //myGLCD.clrScr();
  myGLCD.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  //myGLCD.setColor(255, 255, 255);
  setDrawColor_contrast();
}

void driver_clearScreen(){
  setDrawColor_background();
  myGLCD.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  setDrawColor_contrast();

  for (byte x=0; x<SCREEN_WIDTH/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE; x++){
      linear_framebuffer_x2[x]=0;
      linear_framebuffer_x[x] = 0;
      linear_framebuffer_x_new[x]=0;
    }
  
    for (byte y=0; y<SCREEN_HEIGHT/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE; y++){
      linear_framebuffer_y2[y]=0;
      linear_framebuffer_y[y]=0;
      linear_framebuffer_y_new[y]=0;
    }
}

#ifdef colorScreen
  byte red;
  byte green;
  byte blue;

  byte red_bg     = 255;
  byte green_bg   = 255;
  byte blue_bg    = 255;
  

  void setDrawColor(byte red_set, byte green_set, byte blue_set){
    red   = red_set;
    green = green_set;
    blue  = blue_set;
    
    myGLCD.setColor(red, green, blue);
  }

  void initColor_background(byte red_set, byte green_set, byte blue_set){
    red_bg   = red_set;
    green_bg = green_set;
    blue_bg  = blue_set;
  }

  void setDrawColor_background(){
    myGLCD.setColor(red_bg, green_bg, blue_bg);
  }

  void setDrawColor_contrast(){
    if (red_bg + green_bg + blue_bg > 383){
      red   = 0;
      green = 0;
      blue  = 0;
    }else{
      red   = 255;
      green = 255;
      blue  = 255;
    }
    
    
    myGLCD.setColor(red, green, blue);
  }
  
#endif

void clearscreen_displayDriver(){

  set_DrawLimits(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  if (get_os_auto_redraw_screen()){
    setDrawColor_background();
    
    for (byte x=0; x<SCREEN_WIDTH/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE; x++){
      if (linear_framebuffer_x[x]!=linear_framebuffer_x_new[x]){
        for (byte y=0; y<SCREEN_HEIGHT/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE; y++){
          if (linear_framebuffer_y[y]!=linear_framebuffer_y_new[y]){
            myGLCD.fillRect(x*LINEARHASH_FRAMEBUFFER_PIXEL_SIZE,y*LINEARHASH_FRAMEBUFFER_PIXEL_SIZE,x*LINEARHASH_FRAMEBUFFER_PIXEL_SIZE+LINEARHASH_FRAMEBUFFER_PIXEL_SIZE-1, y*LINEARHASH_FRAMEBUFFER_PIXEL_SIZE+LINEARHASH_FRAMEBUFFER_PIXEL_SIZE-1);
          }
        }
      }
    }
  
    for (byte x=0; x<SCREEN_WIDTH/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE; x++){
      linear_framebuffer_x2[x]=linear_framebuffer_x[x];
      linear_framebuffer_x[x] = linear_framebuffer_x_new[x];
      linear_framebuffer_x_new[x]=0;
    }
  
    for (byte y=0; y<SCREEN_HEIGHT/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE; y++){
      linear_framebuffer_y2[y]=linear_framebuffer_y[y];
      linear_framebuffer_y[y]=linear_framebuffer_y_new[y];
      linear_framebuffer_y_new[y]=0;
    }
  }
  setDrawColor_contrast();
}

void updatescreen_displayDriver(){
  //updateDisplay();
}

void setPixel(int x, int y){
  if(
      x>=drawLimit_x_min  &&
      y>=drawLimit_y_min  &&
      x<drawLimit_x_max   &&
      y<drawLimit_y_max   &&
      
      x>=0 && 
      y>=0 && 
      x<SCREEN_WIDTH && 
      y<SCREEN_HEIGHT
    ){

    if ( !get_os_auto_redraw_screen() || (linear_framebuffer_y[y/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE]!=linear_framebuffer_y2[y/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE] && linear_framebuffer_x[x/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE]!=linear_framebuffer_x2[x/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE])) 
      myGLCD.drawPixel(x,y);

    #ifdef colorScreen
      linear_framebuffer_x_new[x/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE] += y  + red%8 + green%8 + blue%8; // Forming the string-x hash
      linear_framebuffer_y_new[y/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE] += x  + red%8 + green%8 + blue%8; // Forming the string-x hash  

      //linear_framebuffer_x_new[x/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE] += y  + red*0x0F + green*0x0F + blue*0x0F; // Forming the string-x hash
      //linear_framebuffer_y_new[y/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE] += x  + red*0x0F + green*0x0F + blue*0x0F; // Forming the string-x hash  
    #else
      linear_framebuffer_x_new[x/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE] += y; // Forming the string-x hash
      linear_framebuffer_y_new[y/LINEARHASH_FRAMEBUFFER_PIXEL_SIZE] += x; // Forming the string-x hash  
    #endif
  }
}

