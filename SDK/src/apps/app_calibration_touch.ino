/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                                                                                         *
 *                                  >>>   IMPORTANT!   <<<                                 *
 *                   DO NOT FORGET TO ADD YOU APP IN os_applications.ino                   *
 *                                                                                         *
 *                                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#define appNameClass    TouchCalibration         // App name without spaces
#define appName         "Calibration"      // App name with spaces 

#define target_frame_padding 10

class appNameClass: public Application{
    public:
        byte touch_count = 0;
        long LastTouch = 0;

        int touches[3][2];
        virtual void loop() override{
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                                >>>   MAIN APP LOOP   <<<                                *
            *                                                                                         *
            */

            //EVERY FRAME CODE
            if (touch_count!=2){
              drawString_centered("Tap on target",SCREEN_WIDTH/2, (SCREEN_HEIGHT - FONT_CHAR_HEIGHT)/2 );
            }else{
              drawString_centered("Tap on target",SCREEN_WIDTH/2, 30 );
            }

            if (touch_count==0){
              drawIcon( icon_target, target_frame_padding, target_frame_padding);
            }else if(touch_count==1){
              drawIcon( icon_target, SCREEN_WIDTH - target_frame_padding - 32, SCREEN_HEIGHT - target_frame_padding - 32);
            }else if(touch_count==2){
              drawIcon( icon_target, SCREEN_WIDTH/2 - 16, SCREEN_HEIGHT/2 - 16);
            }

            if (touch_count>2){
              touch_count = 0;
            }

            if( (_millis() - LastTouch)>700 ){
              if (isPressStart_Select()){

                LastTouch = _millis();
                touches[touch_count][0] = get_os_touch_x();
                touches[touch_count][1] = get_os_touch_y();

                if (touch_count==2){
                  touch_count = 0;

                  /*
                  #ifdef debug
                    for(int i=0; i<3; i++){
                      Serial.print(i);
                      Serial.print(" -   x: ");
                      Serial.print(touches[i][0]);
                      Serial.print("   y: ");
                      Serial.print(touches[i][1]);
                      Serial.print("\n");
                    }
                  #endif
                  */

                  //driver_display_callibrate(int TS_LEFT_new, int TS_RIGHT_new, int TS_TOP_new, int TS_BOTTOM_new);
                  driver_display_callibrate(
                    touches[0][0],
                    touches[0][1],

                    touches[1][0],
                    touches[1][1],

                    touches[2][0],
                    touches[2][1]
                  );

                  //Serial.println((touches[0][0] + touches[1][0])/2 - touches[2][0]);
                  //Serial.println("");

                  if (
                    //true ||
                    abs((touches[0][0] + touches[1][0])/2 - touches[2][0]) > 6 ||
                    abs((touches[0][1] + touches[1][1])/2 - touches[2][1]) > 6
                  ){
                    this->setup();
                    return;
                  }

                  os_switch_to_app(-1);
                }else{
                  touch_count ++;
                }
              }
            }

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };
        void setup(){
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                              >>>   APP SETUP ON START   <<<                             *
            *                                                                                         *
            */

            // ON START CODE
            #ifdef tabletView
                this->showStatusBar = false;
            #endif
            LastTouch = _millis();
            touch_count = 0;

            for(int i=0; i<3; i++){
              touches[i][0] = 0;
              touches[i][1] = 0;
            }

            initColor_background(0x22, 0x25, 0x49);
            driver_clearScreen();
            

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */
        };

        appNameClass(){ // Constructor
            setup();
        };

        const static byte icon[];
        const static byte icon_target[];

        static unsigned const char* getParams(unsigned char type){
            switch(type){ 
              case PARAM_TYPE_NAME: return (unsigned char*)appName; 
              case PARAM_TYPE_ICON: return icon;
              default: return (unsigned char*)""; }
        };

        
};

const byte appNameClass::icon_target[] PROGMEM = {0x02,0x01,0x02,0x20,0x02,0x20,0x04,0xff,0xff,0xff,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x0C,0x00,0x00,0x38,0x1C,0x00,0x00,0x1C,0x38,0x00,0x00,0x0E,0x70,0x00,0x00,0x07,0xE0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x07,0xE0,0x00,0x00,0x0E,0x70,0x00,0x00,0x1C,0x38,0x00,0x00,0x38,0x1C,0x00,0x00,0x30,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,};
const byte appNameClass::icon[] PROGMEM = { //128
  //////////////////////////////////////////////////////////////
  //    PUT YOUR ICON HERE
  #ifdef colorScreen
    0x02,0x01,0x02,0x20,0x02,0x20,0x04,0xff,0xff,0xff,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x0C,0x00,0x00,0x38,0x1C,0x00,0x00,0x1C,0x38,0x00,0x00,0x0E,0x70,0x00,0x00,0x07,0xE0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x07,0xE0,0x00,0x00,0x0E,0x70,0x00,0x00,0x1C,0x38,0x00,0x00,0x38,0x1C,0x00,0x00,0x30,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,
  #else
    0x02,0x01,0x02,0x20,0x02,0x20,0x04,0xff,0xff,0xff,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x0C,0x00,0x00,0x38,0x1C,0x00,0x00,0x1C,0x38,0x00,0x00,0x0E,0x70,0x00,0x00,0x07,0xE0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x07,0xE0,0x00,0x00,0x0E,0x70,0x00,0x00,0x1C,0x38,0x00,0x00,0x38,0x1C,0x00,0x00,0x30,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,
  #endif
  //
  //////////////////////////////////////////////////////////////
};

void TouchCalibration_bootFunc(){
  currentApp = new TouchCalibration();
}