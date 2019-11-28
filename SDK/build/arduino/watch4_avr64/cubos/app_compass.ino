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

#define appNameClass    Compass         // App name without spaces
#define appName         "Compass"      // App name with spaces 

class appNameClass: public Application{
    public:
    
        virtual void loop() override{
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                                >>>   MAIN APP LOOP   <<<                                *
            *                                                                                         *
            */

            //EVERY FRAME CODE
            //drawString_centered("Compass",SCREEN_WIDTH/2,10);

            #ifdef control_has_backbtn
              if (isPressStart_Select() || isPressStart_Back()){
                finish();
              }
            #else
              if (isPressStart_Select()){
                finish();
              }
            #endif

            accelerometer_loop();

            int compass_angle;
            driver_magnitometer_loop();
            compass_angle = 360*2 - driver_magnitometer_get_azimuth();

            float radian_angle_cos  = cos((compass_angle-90)*get_pi()/180);
            float radian_angle_sin  = sin((compass_angle-90)*get_pi()/180);

            if(!driver_acelerometer_device_is_horizontally()){
              drawString_centered("Keep your device",SCREEN_WIDTH/2,20);
              drawString_centered("horizontally",SCREEN_WIDTH/2,30);
            }

            compass_angle = compass_angle%360;

            if(abs(compass_angle) < 23){
              drawString("N",SCREEN_WIDTH - 6,0);
            }else if(abs(compass_angle) - 45*1 < 23){
              drawString("NW",SCREEN_WIDTH - 12,0);
            }else if(abs(compass_angle) - 45*2 < 23){
              drawString("W",SCREEN_WIDTH - 6,0);
            }else if(abs(compass_angle) - 45*3 < 23){
              drawString("SW",SCREEN_WIDTH - 12,0);
            }else if(abs(compass_angle) - 45*4 < 23){
              drawString("S",SCREEN_WIDTH - 6,0);
            }else if(abs(compass_angle) - 45*5 < 23){
              drawString("SE",SCREEN_WIDTH - 12,0);
            }else if(abs(compass_angle) - 45*6 < 23){
              drawString("E",SCREEN_WIDTH - 6,0);
            }else if(abs(compass_angle) - 45*7 < 23){
              drawString("NE",SCREEN_WIDTH - 12,0);
            }else if(abs(compass_angle) - 45*8 < 23){
              drawString("N",SCREEN_WIDTH - 6,0);
            }

            drawString(compass_angle,0,0);

            //SCREEN_CENTER_X
            #define x_scale 1
            
            drawRect_custom(
                SCREEN_CENTER_X + 20*radian_angle_cos*x_scale,  SCREEN_CENTER_Y + 20*radian_angle_sin,
                SCREEN_CENTER_X - 10*radian_angle_sin*x_scale - 20*radian_angle_cos*x_scale,   SCREEN_CENTER_Y + 10*radian_angle_cos - 20*radian_angle_sin,
                SCREEN_CENTER_X - 16*radian_angle_cos*x_scale,  SCREEN_CENTER_Y - 16*radian_angle_sin,
                SCREEN_CENTER_X + 10*radian_angle_sin*x_scale - 20*radian_angle_cos*x_scale,   SCREEN_CENTER_Y - 10*radian_angle_cos - 20*radian_angle_sin,
                false
            );


            if(isPressStart_Left()){
              driver_magnitometer_recalibrate(); 
            }

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };

        void finish(){
          driver_magnitometr_off();
          power_manager_end_accelerometer();
          os_switch_to_app(-1);
        }


        void setup(){
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                              >>>   APP SETUP ON START   <<<                             *
            *                                                                                         *
            */

            set_prevent_displayoff_flag(true); 

            // ON START CODE
            #ifdef tabletView
                this->showStatusBar = true;
            #endif

            //driver_magnitometer_setup();
            #ifdef device_has_power_manager
              power_manager_start_accelerometer();
              driver_magnitometr_on();
            #endif
            
           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */
        };

        appNameClass(){ // Constructor
            setup();
        };

        const static byte icon[];

            static unsigned const char* getParams(unsigned char type){
            switch(type){ 
              case PARAM_TYPE_NAME: return (unsigned char*)appName; 
              case PARAM_TYPE_ICON: return icon;
              default: return (unsigned char*)""; }
        };

};

const byte appNameClass::icon[] PROGMEM = { //128
  //////////////////////////////////////////////////////////////
  //    PUT YOUR ICON HERE
  #ifdef colorScreen
    0x02,0x01,0x02,0x20,0x02,0x18,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x00,0x00,0x80,0xD8,0x00,0x02,0x86,0xA9,0xC6,0x50,0x89,0x8A,0x49,0x6A,0xC9,0x8A,0x49,0x4A,0x89,0x8A,0x49,0x4A,0x89,0x89,0xA7,0x4A,0x66,0x00,0x01,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x40,0x00,0x05,0x46,0x45,0x00,0x06,0xA9,0x66,0x80,0x04,0xAF,0x44,0x00,0x04,0xA8,0x44,0x00,0x04,0xA6,0x34,0x00,0x00,0x00,0x00,0x00,0x44,0x00,0x00,0x1C,0x64,0x00,0x04,0x22,0x54,0x00,0x06,0x20,0x4C,0xFF,0xFF,0x1C,0x44,0x00,0x06,0x02,0x44,0x00,0x04,0x1C,0x00,0x00,0x00,0x00,
  #else
    0x02,0x01,0x02,0x20,0x02,0x18,0x04,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x1F,0xF8,0x00,0x00,0x1F,0xF8,0x00,0x00,0x3F,0xFC,0x00,0x00,0x3F,0xFC,0x00,0x00,0x3F,0xFC,0x00,0x00,0x7F,0xFE,0x00,0x00,0x7F,0xFE,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x01,0xFF,0xFF,0x80,0x01,0xFF,0xFF,0x80,0x03,0xFE,0x7F,0xC0,0x03,0xF8,0x1F,0xC0,0x03,0xC0,0x03,0xC0,
  #endif
  //
  //////////////////////////////////////////////////////////////
};