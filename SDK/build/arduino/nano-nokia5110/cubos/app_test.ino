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

#define appNameClass    TestApp         // App name without spaces
#define appName         "Test app"      // App name with spaces (max 16)

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
            drawString_centered("New app",84/2,10);

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
    0xFC, 0xFF, 0xFF, 0x3F, 0xFE, 0xFF, 0xFF, 0x7F, 
    0xFF, 0xFF, 0x4F, 0xF2, 0xFF, 0xFF, 0x4F, 0xF2, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0x07, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xC0, 
    0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
    0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
    0x03, 0x00, 0x00, 0xC0, 0x03, 0x08, 0x00, 0xC0, 
    0x03, 0x08, 0x01, 0xC0, 0x03, 0x08, 0x00, 0xC0, 
    0x03, 0x38, 0x1D, 0xC0, 0x03, 0x48, 0x25, 0xC0, 
    0x03, 0x48, 0x25, 0xC0, 0x03, 0x38, 0x25, 0xC0, 
    0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
    0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
    0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
    0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
    0x03, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0xE0, 
    0xFE, 0xFF, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0x3F,
	//
	//////////////////////////////////////////////////////////////
};
