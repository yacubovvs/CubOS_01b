/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                          >>>   ADD YOUR APPLICATION HERE   <<<                          *
 *                                                                                         *
 */

    Application *getApp(byte i){
      
        if (i==0) return new ClockApp; 
        if (i==1) return new SettingApp;
        if (i==2) return new TestApp;
        if (i==3) return new SampleGame;
        if (i==4) return new Barometer;
        if (i==5) return new Accelerometer;
        if (i==6) return new Battery;

        // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ADD YOUR APP HERE
        else return new MainMenu;
    }

    const unsigned char * getAppParams(byte i, byte type){
        if(i==0){
            ClockApp *app; return ((*app).getParams(type));
        }else if(i==1){
            SettingApp *app; return ((*app).getParams(type));
        }else if(i==2){
            TestApp *app; return ((*app).getParams(type));
        }else if(i==3){
            SampleGame *app; return ((*app).getParams(type));
        }else if(i==4){
            Barometer *app; return ((*app).getParams(type));
        }else if(i==5){
            Accelerometer *app; return ((*app).getParams(type));
        }else if(i==6){
            Battery *app; return ((*app).getParams(type));
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