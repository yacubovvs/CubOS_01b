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

#define appNameClass    Barometer         // App name without spaces
#define appName         "Barometer"      // App name with spaces 

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
            double barometer_T,barometer_P;


            if(barometer_updateData()){
              //drawString_centered("Gata got",SCREEN_WIDTH/2,10);
              //drawDebugString((int)(barometer_T*1000), 20);
              //drawDebugString((int)(barometer_P*1000), 30);

              drawString(  "kPa:", 0, 0);
              drawIntString(  (long)get_barometer_Pressure(), 50, 0);
              
              drawString(  "mm Hg:", 0, 10);
              drawIntString(  (long)get_barometer_mm_Hg(),    50, 10);

              drawString(  "Sea(m):", 0, 20);
              drawIntString(  (long)get_altitude(),           50, 20);

              drawString(  "dAlt(m):", 0, 30);
              drawIntString(  (long)get_altitude_def(),           50, 30);
              
            }else{
              drawString_centered("Barometer failed",SCREEN_WIDTH/2,10);
            }
            
            #ifdef control_has_backbtn
              if (isPressStart_Select() || isPressStart_Back()){
                finish();
              }
            #else
              if (isPressStart_Select()){
                finish();
              }
            #endif

            if(isPressStart_Left()){
              barometer_reset_current_pressure();  
            }

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };

        void finish(){
          barometer_finish();
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
            barometer_setup();
            // ON START CODE
            #ifdef tabletView
                this->showStatusBar = true;
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
	//		PUT YOUR ICON HERE
  #ifdef colorScreen
    0x02,0x01,0x02,0x20,0x02,0x18,0x04,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0xB9,0x17,0x33,0x19,0xA5,0xB4,0x94,0xA5,0xA5,0x54,0x94,0xA5,0xB9,0x14,0x93,0x25,0xA5,0x17,0x14,0xA5,0xA5,0x14,0x14,0xA5,0xA5,0x14,0x14,0xA5,0xB9,0x14,0x13,0x19,0x80,0x00,0x00,0x01,0xBF,0xCF,0x0E,0x79,0xBF,0xCF,0x1F,0x79,0x86,0x0C,0x19,0x31,0x86,0x0C,0x18,0x31,0x86,0x0E,0x0E,0x31,0x86,0x0E,0x0F,0x31,0x86,0x0C,0x03,0x31,0x86,0x0C,0x03,0x31,0x86,0x0C,0x13,0x31,0x86,0x0F,0x1F,0x31,0x86,0x0F,0x0E,0x31,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,
  #else
    0x02,0x01,0x02,0x20,0x02,0x18,0x04,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0xB9,0x17,0x33,0x19,0xA5,0xB4,0x94,0xA5,0xA5,0x54,0x94,0xA5,0xB9,0x14,0x93,0x25,0xA5,0x17,0x14,0xA5,0xA5,0x14,0x14,0xA5,0xA5,0x14,0x14,0xA5,0xB9,0x14,0x13,0x19,0x80,0x00,0x00,0x01,0xBF,0xCF,0x0E,0x79,0xBF,0xCF,0x1F,0x79,0x86,0x0C,0x19,0x31,0x86,0x0C,0x18,0x31,0x86,0x0E,0x0E,0x31,0x86,0x0E,0x0F,0x31,0x86,0x0C,0x03,0x31,0x86,0x0C,0x03,0x31,0x86,0x0C,0x13,0x31,0x86,0x0F,0x1F,0x31,0x86,0x0F,0x0E,0x31,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,
  #endif
	//
	//////////////////////////////////////////////////////////////
};