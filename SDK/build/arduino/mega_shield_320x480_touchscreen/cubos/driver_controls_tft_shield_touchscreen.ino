

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
int TS_LEFT=907,TS_RIGHT=136,TS_TOP=942,TS_BOTTOM=139;
void driver_display_callibrate(int x0, int y0, int x1, int y1, int x2, int y2){
  
  /* 
  * /
  Serial.print("TS_LEFT: ");
  Serial.print(TS_LEFT);
  Serial.print("   TS_RIGHT: ");
  Serial.print(TS_RIGHT);
  Serial.print("\n\n");
  // */

  int32_t x_length = (abs(x0 - x1));
  int32_t y_length = (abs(y0 - y1));

  int32_t k_x = x_length*100/(SCREEN_WIDTH - 52);
  int32_t k_y = y_length*100/(SCREEN_HEIGHT - 52);

  int32_t TS_LENGTH_X   = abs(TS_LEFT - TS_RIGHT);
  int32_t TS_MID_X      = abs(TS_LEFT + TS_RIGHT)/2;
  int32_t TS_LENGTH_Y   = abs(TS_TOP - TS_BOTTOM);
  int32_t TS_MID_Y      = abs(TS_TOP + TS_BOTTOM)/2;

  bool TS_X_INVERSE = (TS_RIGHT > TS_LEFT);
  bool TS_Y_INVERSE = (TS_BOTTOM > TS_TOP);

  /*
  Serial.print("\n\n");
  Serial.print("k_x: ");
  Serial.print(k_x);
  Serial.print("   k_y: ");
  Serial.print(k_y);
  Serial.print("\n\n");

  Serial.print("TS_LEFT: ");
  Serial.print(TS_LEFT);
  Serial.print("   TS_RIGHT: ");
  Serial.print(TS_RIGHT);
  Serial.print("\n\n");
  */

  
  //os_touch_x = map(tp.x, TS_LEFT, TS_RIGHT, SCREEN_WIDTH,0);
  //os_touch_y = map(tp.y, TS_TOP, TS_BOTTOM, SCREEN_HEIGHT,0);

  //int max_y = map(tp.y, TS_TOP, TS_BOTTOM, SCREEN_HEIGHT,0);


  TS_LEFT     = TS_MID_X + TS_LENGTH_X * k_x / 100 /2;
  TS_RIGHT    = TS_MID_X - TS_LENGTH_X * k_x / 100 /2;
  
  TS_TOP      = TS_MID_Y + TS_LENGTH_Y * k_y / 100 /2;
  TS_BOTTOM   = TS_MID_Y - TS_LENGTH_Y * k_y / 100 /2;

  int32_t x_shift_0 = min(x1, x0);
  int32_t x_shift_1 = SCREEN_WIDTH - max(x1,x0);
  
  int32_t y_shift_0 = min(y1, y0);
  int32_t y_shift_1 = SCREEN_HEIGHT - max(y1,y0);

  /*
  Serial.print("x_shift_0: ");
  Serial.print(x_shift_0);
  Serial.print("     x_shift_1: ");
  Serial.print(x_shift_1);
  Serial.print("\n");
  Serial.print("y_shift_0: ");
  Serial.print(y_shift_0);
  Serial.print("     y_shift_1: ");
  Serial.print(y_shift_1);
  Serial.print("\n\n");
  */

  /*
  uint32_t delta_x_0 = map(x0, SCREEN_HEIGHT, 0, min(TS_LEFT,TS_RIGHT), max(TS_LEFT,TS_RIGHT));
  uint32_t delta_x_1 = TS_RIGHT - map(x1, SCREEN_HEIGHT, 0, min(TS_LEFT,TS_RIGHT), max(TS_LEFT,TS_RIGHT));

  uint32_t delta_y_0 = map(y0, SCREEN_HEIGHT, 0, min(TS_TOP, TS_BOTTOM), max(TS_TOP, TS_BOTTOM));
  uint32_t delta_y_1 = TS_BOTTOM - map(y1, SCREEN_HEIGHT, 0, min(TS_TOP, TS_BOTTOM), max(TS_TOP, TS_BOTTOM));
  */

  int32_t need_shift_x = x_shift_0 - x_shift_1;
  int32_t need_shift_y = y_shift_0 - y_shift_1;

  /*
  Serial.println("# # # # # # # # # # # #");
  Serial.print("TS_LEFT: ");
  Serial.print(TS_LEFT);
  Serial.print("   TS_RIGHT: ");
  Serial.print(TS_RIGHT);
  Serial.print("TS_TOP: ");
  Serial.print(TS_TOP);
  Serial.print("   TS_BOTTOM: ");
  Serial.print(TS_BOTTOM);
  Serial.print("\n\n");
  */

  if (TS_X_INVERSE){
    TS_LEFT   -= need_shift_x*100/x_length * TS_LENGTH_X / 100 / 2;
    TS_RIGHT  -= need_shift_x*100/x_length * TS_LENGTH_X / 100 / 2;
  }else{
    TS_LEFT   += need_shift_x*100/x_length * TS_LENGTH_X / 100 / 2;
    TS_RIGHT  += need_shift_x*100/x_length * TS_LENGTH_X / 100 / 2;
  }

  

  if (TS_Y_INVERSE){
    TS_BOTTOM -= need_shift_y*100/y_length * TS_LENGTH_Y / 100 / 2;
    TS_TOP    -= need_shift_y*100/y_length * TS_LENGTH_Y / 100 / 2;
  }else{
    TS_BOTTOM += need_shift_y*100/y_length * TS_LENGTH_Y / 100 / 2;
    TS_TOP    += need_shift_y*100/y_length * TS_LENGTH_Y / 100 / 2;
  }
  

  /*
  Serial.println(need_shift_y);
  Serial.println(y_length);
  Serial.println(need_shift_y*100/y_length);

  Serial.println("# # # # # # # # # # # #");
  Serial.print("TS_LEFT: ");
  Serial.print(TS_LEFT);
  Serial.print("   TS_RIGHT: ");
  Serial.print(TS_RIGHT);
  Serial.print("TS_TOP: ");
  Serial.print(TS_TOP);
  Serial.print("   TS_BOTTOM: ");
  Serial.print(TS_BOTTOM);
  Serial.print("\n\n");
  */

  //TS_LEFT   = TS_MID_X + (TS_LENGTH_X * k_x - 100) / 100 / 2;
  //TS_RIGHT  = TS_MID_X - (TS_LENGTH_X * k_x - 100) / 100 / 2;


  
  

/*
  Serial.print("\n");
  Serial.print("X0: ");
  Serial.print(x0);
  Serial.print("      Y0:");
  Serial.print(y0);
  Serial.print("\n");
  Serial.print("X1: ");
  Serial.print(x1);
  Serial.print("      Y1:");
  Serial.print(y1);
  Serial.print("\n");
  Serial.print("X2: ");
  Serial.print(x2);
  Serial.print("      Y2:");
  Serial.print(y2);
  Serial.print("\n");
*/

  //Serial.print("\n\n");

  //bool TS_X_INVERSE = (TS_LEFT > TS_RIGHT);
  //bool TS_Y_INVERSE = (TS_BOTTOM > TS_TOP);

  int temp;
  if(x0>x1 || TS_X_INVERSE){
    temp = TS_LEFT;
    TS_LEFT = TS_RIGHT;
    TS_RIGHT = temp;
  }

  if(y0>y1 || TS_Y_INVERSE){
    //Serial.print("TS TOP AND BOTTOM CHANGE!!!\n");
    temp = TS_TOP;
    TS_TOP = TS_BOTTOM;
    TS_BOTTOM = temp;
  }

  /* 
  * /
  Serial.print("TS_LEFT: ");
  Serial.print(TS_LEFT);
  Serial.print("   TS_RIGHT: ");
  Serial.print(TS_RIGHT);
  Serial.print("\n\n");
  // */

}

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
  //pinMode(46, OUTPUT);
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button started to press
boolean isPressStart(byte num){
  if (num>=os_control_buttons) return false;
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button Press finished
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

/*
void cancelTouchStart(){
  isTouchStart = false;
}
*/

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

    os_touch_x = map(tp.x, TS_LEFT, TS_RIGHT, SCREEN_WIDTH,0);
    os_touch_y = map(tp.y, TS_TOP, TS_BOTTOM, SCREEN_HEIGHT,0);
    
    #ifdef debug
      #ifdef debug_show_touch_position
        #define x_size 5

        drawLine( os_touch_x - x_size, os_touch_y - x_size, os_touch_x + x_size, os_touch_y + x_size);
        drawLine( os_touch_x - x_size, os_touch_y + x_size, os_touch_x + x_size, os_touch_y - x_size);
      #endif
    #endif
  
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