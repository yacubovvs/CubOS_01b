

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
  PARAMS
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

//#include <MCUFRIEND_kbv.h>
#include "libs_h/MCUFRIEND_kbv/MCUFRIEND_kbv.h" 
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>
//#include "libs_h/Adafruit_TouchScreen/TouchScreen.h" 
 
#define XP 8
#define XM A2
#define YP A3
#define YM 9

//const int XP=8,XM=A2,YP=A3,YM=9; //ID=0x9341
const int TS_LEFT=907,TS_RT=136,TS_TOP=942,TS_BOT=139;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define MINPRESSURE 50
#define MAXPRESSURE 1200

// device buttons count
const byte os_control_buttons = 1; 

uint16_t os_touch_x = 0;
uint16_t os_touch_y = 0;

uint16_t get_os_touch_x(){
  return os_touch_x;
}

uint16_t get_os_touch_y(){
  return os_touch_y;
}

// Do not change:
boolean os_control_pressStart[] = {false};
boolean os_control_pressed[]      = {false};


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
  HENDLER
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

#define BUTTONS_CONTROLS_SIZE               32
#define BUTTONS_CONTROLS_PADDING            10
#define BUTTONS_CONTROLS_MARGIN_LEFT_RIGHT  10

void os_control_setup(){
  pinMode(46, OUTPUT);
  //digitalWrite(46, 1);
  //delay(100);
  //digitalWrite(46, 0);
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button started to press
boolean isPressStart(byte num){
  if (num>=os_control_buttons) return false;
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button [ress finished
boolean isPressEnd(byte num){
  if (num>=os_control_buttons) return false;
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button pressed
boolean isPress(byte num){
  if (num>=os_control_buttons) return false;
}

bool isTouching = false;
bool isTouchStart = false;

long lastTouch=0;
long lastTouch_start=0;

void os_control_loop(){

  TSPoint tp;
  tp = ts.getPoint();
    
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);

  if(isTouching && millis() - lastTouch> dtime){
    isTouching = false;
  }

  if(isTouchStart && millis() - lastTouch_start> dtime){
    isTouchStart = false;
  }


  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    //isTouching = true;
    if(!isTouchStart && !isTouching ){
      isTouchStart = true;

      lastTouch_start = millis();
    }

    isTouching = true;
    
    lastTouch = millis();

    os_touch_x = map(tp.x, TS_LEFT, TS_RT, SCREEN_WIDTH,0);
    os_touch_y = map(tp.y, TS_TOP, TS_BOT, SCREEN_HEIGHT,0);
    
    
  
    //drawDebugString(os_touch_x,20);
    //drawDebugString(os_touch_y,30); 
  }


  /*
  if (software_btn){
    if (!os_control_pressed[0]){
      os_control_pressStart[0]=true;
      os_control_pressed[0]=true;
    }else os_control_pressStart[0]=false;
  }else{
    os_control_pressStart[0]=false;
    os_control_pressed[0]=false;
  }
  */
  
}

//////////////////////////////////////////////////////////////////////////////
//  Events for apps

boolean touchScreen_isTouching(){return isTouching;}
boolean touchScreen_isTouch_Start(){return isTouchStart;}
boolean isPressStart_Right(){return false;}
boolean isPressStart_Select(){return isTouchStart;}
boolean isPressStart_Left(){return false;}
//
//////////////////////////////////////////////////////////////////////////////