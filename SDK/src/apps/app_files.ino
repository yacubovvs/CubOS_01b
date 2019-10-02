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

#define appNameClass    Files         // App name without spaces
#define appName         "Files"      // App name with spaces 

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
            drawString_centered("New app",SCREEN_WIDTH/2,10);

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
    0x02,0x01,0x02,0x20,0x02,0x20,0x04,0xff,0xd9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xF8,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x03,0xFF,0xFE,0x1F,0xE0,0x00,0x06,0x3F,0xF0,0x00,0x02,0x7F,0xF8,0x00,0x02,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xF0,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x07,0xFF,0xF8,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xF8,0x00,0x00,0x02,0x04,0x00,0x00,0x07,0xF2,0x00,0x00,0x08,0x09,0xFF,0xFE,0x1F,0xE4,0x00,0x01,0x20,0x13,0xFF,0xF9,0x40,0x08,0x00,0x05,0x80,0x07,0xFF,0xE5,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x17,0x80,0x00,0x00,0x14,0x80,0x00,0x00,0x14,0x80,0x00,0x00,0x1C,0x80,0x00,0x00,0x10,0xFF,0xFF,0xFF,0xF0,
  #else
    0x02,0x01,0x02,0x20,0x02,0x20,0x04,0xff,0xd9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xF8,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x03,0xFF,0xFE,0x1F,0xE0,0x00,0x06,0x3F,0xF0,0x00,0x02,0x7F,0xF8,0x00,0x02,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE2,0x7F,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x04,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xF0,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x07,0xFF,0xF8,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xF8,0x00,0x00,0x02,0x04,0x00,0x00,0x07,0xF2,0x00,0x00,0x08,0x09,0xFF,0xFE,0x1F,0xE4,0x00,0x01,0x20,0x13,0xFF,0xF9,0x40,0x08,0x00,0x05,0x80,0x07,0xFF,0xE5,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x15,0x80,0x00,0x00,0x17,0x80,0x00,0x00,0x14,0x80,0x00,0x00,0x14,0x80,0x00,0x00,0x1C,0x80,0x00,0x00,0x10,0xFF,0xFF,0xFF,0xF0,
  #endif
	//
	//////////////////////////////////////////////////////////////
};