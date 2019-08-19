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

#define appNameClass    Accelerometer         // App name without spaces
#define appName         "Accel test"      // App name with spaces (max 8)

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
            //drawString_centered("New app",SCREEN_WIDTH/2,10);

            accelerometer_loop();

            if (isPressStart_Select()){
              #ifdef device_has_power_manager
                power_manager_end_accelerometer();
              #endif
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

            #ifdef device_has_power_manager
              power_manager_start_accelerometer();
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
    0x02,0x01,0x02,0x20,0x02,0x18,0x04,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0x9C,0x90,0x0E,0x4D,0xA2,0x90,0x08,0xA5,0xA0,0x90,0x08,0x25,0xA0,0x73,0xCC,0x45,0xA6,0x10,0x02,0x85,0xA2,0x90,0x02,0x85,0x9C,0x60,0x0C,0xE5,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0xBF,0xCF,0x0E,0x79,0xBF,0xCF,0x1F,0x79,0x86,0x0C,0x19,0x31,0x86,0x0C,0x18,0x31,0x86,0x0E,0x0E,0x31,0x86,0x0E,0x0F,0x31,0x86,0x0C,0x03,0x31,0x86,0x0C,0x03,0x31,0x86,0x0C,0x13,0x31,0x86,0x0F,0x1F,0x31,0x86,0x0F,0x0E,0x31,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,
  #else
    0x02,0x01,0x02,0x20,0x02,0x18,0x04,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0x9C,0x90,0x0E,0x4D,0xA2,0x90,0x08,0xA5,0xA0,0x90,0x08,0x25,0xA0,0x73,0xCC,0x45,0xA6,0x10,0x02,0x85,0xA2,0x90,0x02,0x85,0x9C,0x60,0x0C,0xE5,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0xBF,0xCF,0x0E,0x79,0xBF,0xCF,0x1F,0x79,0x86,0x0C,0x19,0x31,0x86,0x0C,0x18,0x31,0x86,0x0E,0x0E,0x31,0x86,0x0E,0x0F,0x31,0x86,0x0C,0x03,0x31,0x86,0x0C,0x03,0x31,0x86,0x0C,0x13,0x31,0x86,0x0F,0x1F,0x31,0x86,0x0F,0x0E,0x31,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,
  #endif
	//
	//////////////////////////////////////////////////////////////
};
