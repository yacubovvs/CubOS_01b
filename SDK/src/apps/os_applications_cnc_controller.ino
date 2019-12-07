/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                          >>>   ADD YOUR APPLICATION HERE   <<<                          *
 *                                                                                         *
 */

    Application *getApp(byte i){
      
        if (i==0) return new SettingApp;
        if (i==1) return new CNCCodeFromSD;

        // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ADD YOUR APP HERE
        else return new MainMenu;
    }

    const unsigned char * getAppParams(byte i, byte type){
        if(i==0){
            SettingApp *app; return ((*app).getParams(type));
        }else if(i==1){
            CNCCodeFromSD *app; return ((*app).getParams(type));
        }
        // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ADD YOUR APP HERE
        else{
            MainMenu *app; return ((*app).getParams(type));
        }
        return 0;
    }

/*
 *                                                                                         *
 *                                                                                         *
 *                                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

const byte get_application_count(){
    return os_MAINMENU_APP_COUNT;
}
