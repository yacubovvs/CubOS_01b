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

#define appNameClass    WWW         // App name without spaces
#define appName         "WWW"      // App name with spaces 

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
            drawString_centered("WWW",SCREEN_WIDTH/2,10);

            #ifdef control_has_backbtn
              if (isPressStart_Select() || isPressStart_Back()){
                finish();
              }
            #else
              if (isPressStart_Select()){
                finish();
              }
            #endif

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };

        void finish(){
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
    0x02,0x01,0x02,0x20,0x02,0x20,0x04,0x33,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x00,0x40,0x07,0xF0,0x00,0xE0,0x0F,0xF0,0x00,0xF0,0x1F,0xC0,0x03,0xF8,0x1F,0x00,0x03,0xF8,0x3F,0x00,0x07,0xFC,0x3E,0x00,0x0F,0xFC,0x3E,0x00,0x0E,0xFC,0x7E,0x00,0x3A,0x7E,0x7C,0x00,0x3A,0x76,0x70,0x00,0x38,0xC0,0x40,0x00,0x00,0x20,0x70,0x00,0x0F,0xE0,0x78,0x00,0x1F,0xF0,0x7F,0x00,0x3F,0xF0,0x7F,0x80,0x3F,0xF0,0x3F,0x80,0x3F,0xF0,0x3F,0x80,0x1F,0xF0,0x3F,0x80,0x0F,0xE0,0x1F,0x00,0x01,0xE8,0x1E,0x00,0x01,0xE8,0x0E,0x00,0x00,0xE0,0x06,0x00,0x00,0xC0,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x66,0xff,0x00,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x7F,0xFE,0x00,0x01,0xFF,0xFF,0x80,0x00,0x3F,0xFF,0x80,0x00,0x0F,0xFF,0x00,0x00,0x0F,0xFF,0x00,0x00,0x3F,0xFC,0x00,0x00,0xFF,0xFC,0x00,0x00,0xFF,0xF8,0x00,0x01,0xFF,0xF0,0x00,0x01,0xFF,0xF1,0x00,0x01,0xFF,0xC5,0x80,0x03,0xFF,0xC5,0x88,0x0F,0xFF,0xC7,0x3E,0x3F,0xFF,0xFF,0xDE,0x0F,0xFF,0xF0,0x1E,0x07,0xFF,0xE0,0x0E,0x00,0xFF,0xC0,0x0E,0x00,0x7F,0xC0,0x0E,0x00,0x7F,0xC0,0x0C,0x00,0x7F,0xE0,0x0C,0x00,0x7F,0xF0,0x1C,0x00,0xFF,0xFE,0x10,0x01,0xFF,0xFE,0x10,0x01,0xFF,0xFF,0x10,0x01,0xFF,0xFF,0x20,0x01,0xFF,0xFF,0xC0,0x01,0xFF,0xFF,0x80,0x00,0x7F,0xFE,0x00,0x00,0x0F,0xF0,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x70,0x0E,0x00,0x01,0x80,0x01,0x80,0x02,0x00,0x00,0x40,0x04,0x00,0x00,0x20,0x08,0x00,0x00,0x10,0x10,0x00,0x00,0x08,0x20,0x00,0x00,0x04,0x20,0x00,0x00,0x04,0x40,0x00,0x00,0x02,0x40,0x00,0x00,0x02,0x40,0x00,0x00,0x02,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x40,0x00,0x00,0x02,0x40,0x00,0x00,0x02,0x40,0x00,0x00,0x02,0x20,0x00,0x00,0x04,0x20,0x00,0x00,0x04,0x10,0x00,0x00,0x08,0x08,0x00,0x00,0x10,0x04,0x00,0x00,0x20,0x02,0x00,0x00,0x40,0x01,0x80,0x01,0x80,0x00,0x70,0x0E,0x00,0x00,0x0F,0xF0,0x00,
  #else
    0x02,0x01,0x02,0x20,0x02,0x20,0x04,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xF8,0x20,0x00,0x00,0x04,0x40,0x00,0x00,0x02,0x80,0x01,0x80,0x01,0x80,
    0x06,0x60,0x01,0x80,0x18,0x18,0x01,0x80,0x60,0x06,0x01,0x80,0x80,0x01,0x01,0x80,0xE0,0x07,0x01,0x80,0x98,0x1F,0x01,0x80,0x86,0x7F,0x01,
    0x80,0x81,0xFF,0x01,0x80,0x80,0xFF,0x01,0x80,0x80,0xFF,0x01,0x80,0x80,0xFF,0x01,0x80,0x80,0xFF,0x01,0x80,0x80,0xFF,0x01,0x80,0x60,0xFE,
    0x01,0x80,0x18,0xF8,0x01,0x80,0x06,0xE0,0x01,0x80,0x01,0x80,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x20,0x80,0x01,0x80,0x20,
    0x00,0x01,0x80,0x38,0x94,0x01,0x80,0x24,0x9A,0x01,0x80,0x24,0x92,0x01,0x80,0x38,0x92,0x01,0x40,0x00,0x00,0x02,0x20,0x00,0x00,0x04,0x1F,
    0xFF,0xFF,0xF8,
  #endif
	//
	//////////////////////////////////////////////////////////////
};
