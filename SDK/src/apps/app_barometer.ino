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
#define appName         "Barometer"      // App name with spaces (max 8)

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


            if(getPressure_barometer()){
              drawString_centered("Gata got",SCREEN_WIDTH/2,10);
              //drawDebugString((int)(barometer_T*1000), 20);
              //drawDebugString((int)(barometer_P*1000), 30);
            }else{
              drawString_centered("Barometer failed",SCREEN_WIDTH/2,10);
            }
            

            if (isPressStart_Select()){
                os_switch_to_app(-1);
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