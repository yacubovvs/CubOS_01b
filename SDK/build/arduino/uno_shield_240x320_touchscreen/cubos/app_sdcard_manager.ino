
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

#define appNameClass    SDAppManager         // App name without spaces
#define appName         "App Manager"      // App name with spaces (max 16)

#ifndef do_Not_use_native_apps
  class appNameClass: public Application{
      public:
          virtual void loop() override;
          void setup();

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
      0x03, 0x00, 0x00, 0xC0, 0x03, 0x88, 0x22, 0xC0, 
      0x03, 0x88, 0x36, 0xC0, 0x03, 0x88, 0x2A, 0xC0, 
      0x03, 0x88, 0x22, 0xC0, 0x03, 0x88, 0x22, 0xC0, 
      0x03, 0x50, 0x22, 0xC0, 0x03, 0x20, 0x22, 0xC0, 
      0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
      0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
      0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
      0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 
      0x03, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0xE0, 
      0xFE, 0xFF, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0x3F,
    //
    //////////////////////////////////////////////////////////////
  };

  void app_manager_boot_func(){
      currentApp = new SDAppManager();
  }

#endif

#ifndef do_Not_use_native_apps
  void appNameClass::setup(){
#else
  void SDAppManager_setup(){
#endif

    #ifdef tabletView
      this->showStatusBar = false;
    #endif
}

#ifndef do_Not_use_native_apps
  void appNameClass::loop(){
#else
  void SDAppManager_loop(){
#endif
    //EVERY FRAME CODE
    /* 
    #ifndef conf_uno_touch_shield
      // Do not show this label on UNO with touch screen
      drawString_centered("Booting from SD app",SCREEN_WIDTH/2,8);
    #endif
    */

    if (driver_sdcard_init()){
      //drawString("SD card read success",10,20);
      
      os_run_b("/apps/apps_manager.b"); // run bin from sdcard

      #ifndef do_Not_use_native_apps
        #ifndef isTouchScreen
          if (isPressStart_Select()){
            os_switch_to_app(-1);
          }
        #endif
      #endif
      
    }else{
      drawString("Card read fail",10,10);
    }

};