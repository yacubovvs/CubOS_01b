/*
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
*/

unsigned char delay_before_turnoff                  = 1; 
unsigned char delay_before_ScreenSaver              = 0; 
unsigned char delay_before_turnoffBackLight         = 0; 

#ifdef backlight_init
    unsigned char backlight_light = backlight_init;
#else
    unsigned char backlight_light = 0;
#endif

void powermanager_wakeup(){
    os_control_reset_last_user_avtivity();
}

byte get_backlight_light(){
    if (backlight_light*backlight_light*3>255) return 255;
    else return backlight_light*backlight_light*3;
}

byte get_backlight_light_raw(){
    // 0 .. 10
    return backlight_light;
}

void set_backlight_light_raw(char val){
    if(val<0) val = 0;
    if(val>10) val = 10;
    backlight_light = val;
    set_brightness(get_backlight_light());
}

// # # # # # # # # # # # # # # # # # # # # # # # 
//              backlight_fade_light

#ifdef backlight_fade_init
    unsigned char backlight_fade_light = backlight_fade_init;
#else
    unsigned char backlight_fade_light = 2;
#endif

byte get_backlight_fade_light(){
    if (backlight_fade_light*backlight_fade_light*3>255) return 255;
    else return backlight_fade_light*backlight_fade_light*3;
}

byte get_backlight_fade_light_raw(){
    // 0 .. 10
    return backlight_fade_light;
}

void set_backlight_fade_light_raw(char val){
    if(val<0) val = 0;
    if(val>10) val = 10;
    backlight_fade_light = val;
}

// # # # # # # # # # # # # # # # # # # # # # # # 
//              delay_before_turnoff


int get_delay_before_turnoff(){
    switch(delay_before_turnoff){
        case 0: return 5;
        case 1: return 10;
        case 2: return 15;
        case 3: return 20;
        case 4: return 30;
        case 5: return 45;
        case 6: return 60;
        case 7: return 2*60;
        case 8: return 5*60;
        case 9: return 15*60;
        default: return -1;
    }
}

void set_delay_before_turnoff_raw(char val){
    if(val<0) val = 0;
    if(val>10) val = 10;
    delay_before_turnoff = val;
}

byte get_delay_before_turnoff_raw(){
    return delay_before_turnoff;
}

// # # # # # # # # # # # # # # # # # # # # # # # 
//              delay_before_ScreenSaver

int get_delay_before_ScreenSaver(){
    switch(delay_before_ScreenSaver){
        case 0: return 5;
        case 1: return 10;
        case 2: return 15;
        case 3: return 20;
        case 4: return 30;
        case 5: return 45;
        case 6: return 60;
        case 7: return 2*60;
        case 8: return 5*60;
        case 9: return 15*60;
        default: return -1;
    }
}

void set_delay_before_ScreenSaver_raw(char val){
    if(val<0) val = 0;
    if(val>10) val = 10;
    delay_before_ScreenSaver = val;
}

byte get_delay_before_ScreenSaver_raw(){
    return delay_before_ScreenSaver;
}

// # # # # # # # # # # # # # # # # # # # # # # # 
//              delay_before_turnoffBackLight (fading)

int get_delay_before_turnoffBackLight(){
    switch(delay_before_turnoffBackLight){
        case 0: return 3;
        case 1: return 5;
        case 2: return 10;
        case 3: return 15;
        case 4: return 20;
        case 5: return 30;
        case 6: return 45;
        case 7: return 60;
        case 8: return 2*60;
        case 9: return 5*50;
        default: return -1;
    }
}

void set_delay_before_turnoffBackLight_raw(char val){
    if(val<0) val = 0;
    if(val>10) val = 10;
    delay_before_turnoffBackLight = val;
}

byte get_delay_before_turnoffBackLight_raw(){
    return delay_before_turnoffBackLight;
}

/*
case 0: return "5 sec";
case 1: return "10 sec";
case 2: return "30 sec";
case 3: return "1 min";
case 4: return "2 min";
case 5: return "5 min";
case 6: return "10 min";
case 7: return "30 min";
case 8: return "45 min";
case 9: return "1 hour";
*/

struct MenuElement{
    byte    id;
    String  title;
    byte    icon;
    byte    action;
    byte    parent;
    /*
        actions:
            0x00 - nothing
            0x01 - open new menu
            0x02 - set current time
            0x03 - set num (with "+"" and "-" buttons)
            0x04 - exit (back)
    */ 

};

#define MenuElement_lenght 9  // !!! DO NOT FORGET TO CHANGE IF ADD TO MENU LIST !!!
const MenuElement settingMenu[MenuElement_lenght] = {

    MenuElement{
        0x01,                   //  ID
        "Screen",               //  Title
        SETTINGS_SCREEN,        //  Icon
        0x01,                   //  Action
        0x00                    //  Parent ID
    },
        MenuElement{
            0x04,                   //  ID
            "Brightness",           //  Title
            SETTINGS_BRIGHTNESS,    //  Icon
            0x03,                   //  Action
            0x01                    //  Parent ID
        },
        MenuElement{
            0x05,                   //  ID
            "Fade in",              //  Title
            SETTINGS_FADEIN,        //  Icon
            0x03,                   //  Action
            0x01                    //  Parent ID
        },
        MenuElement{
            0x06,                   //  ID
            "Fade brightness",      //  Title
            SETTINGS_FADEBRIGHTNESS,//  Icon
            0x03,                   //  Action
            0x01                    //  Parent ID
        },
        MenuElement{
            0x07,                   //  ID
            "Screensaver in",       //  Title
            SETTINGS_SCREENSAVERIN, //  Icon
            0x03,                   //  Action
            0x01                    //  Parent ID
        },
        MenuElement{
            0x08,                   //  ID
            "Lock screen in",       //  Title
            SETTINGS_LOCKSCREENIN,  //  Icon
            0x03,                   //  Action
            0x01                    //  Parent ID
        },
        MenuElement{
            0x09,                   //  ID
            "Back",                 //  Title
            SETTINGS_BACK,          //  Icon
            0x04,                   //  Action
            0x01                    //  Parent ID
        },
    MenuElement{
        0x02,                   //  ID
        "Time",                 //  Title
        SETTINGS_TIME,          //  Icon
        0x02,                   //  Action
        0x00                    //  Parent ID
    },
    MenuElement{
        0x03,                   //  ID
        "Exit",                 //  Title
        SETTINGS_BACK,          //  Icon
        0x04,                   //  Action
        0x00                    //  Parent ID
    },
};

#define appNameClass    SettingApp         // App name without spaces
#define appName         "Settings"         // App name with spaces 


class appNameClass: public Application{
    public:

        byte current_menu_position          = 0;
        byte current_menu                   = 0;
        byte current_menu_element_array_id  = 0;
        byte current_action                 = 0x01;

        // #############################
        // #############################
        // #############################
        // #############################
        // #############################
        // #############################

        #define drawSettingsElement_height                29
        #define drawSettingsElement_margin                2
        #define drawSettingsElement_margin_left           10
        #define drawSettingsElement_padding               3
        #define drawSettingsElement_padding_label_value   3

        String get_ValueOfMenuElement(byte elementId){
            switch(elementId){
                case 0x01: return "Screen settings";
                case 0x02: return (os_clock_currentTime_hour()<10?"0":"") + String(os_clock_currentTime_hour(), DEC) + ":" + (os_clock_currentTime_minutes()<10?"0":"") + String(os_clock_currentTime_minutes(), DEC) + ":" + (os_clock_currentTime_seconds()<10?"0":"") + String(os_clock_currentTime_seconds(), DEC);
                case 0x03: return "";
                case 0x04: return get_value_current_set_value(0x04);
                case 0x05: return get_value_current_set_value(0x05);
                case 0x06: return get_value_current_set_value(0x06);
                case 0x07: return get_value_current_set_value(0x07);
                case 0x08: return get_value_current_set_value(0x08);
                default: return "";
            }
        }


        byte current_set_value_var = 0x00;
        byte current_set_value_val = 0x00;

        String value_sec_to_string_value(int value){
            if(value>0 && value<60){
                return String(value, DEC) + " sec.";
            }else if(value>=60){
                return String(value/60, DEC) + " min.";
            }else return "Never";
        }

        String get_value_current_set_value(byte var){
            /*
                0x04 "Brightness"
                0x05 "Fade in"
                0x06 "Fade brightness"
                0x07 "Screensaver in"
                0x08 "Lock screen in"
            */
           
            switch(var){
                case 0x00: return "0px";

                case 0x04: return String(get_backlight_light_raw() * 10, DEC) + "%";
                case 0x05: return value_sec_to_string_value(get_delay_before_turnoffBackLight());
                case 0x06: return String(get_backlight_fade_light_raw() * 10, DEC) + "%";
                case 0x07: return value_sec_to_string_value(get_delay_before_ScreenSaver());
                case 0x08: return value_sec_to_string_value(get_delay_before_turnoff());
            }
        }

        byte get_raw_current_set_value(byte var){
            /*
                0x04 "Brightness"
                0x05 "Fade in"
                0x06 "Fade brightness"
                0x07 "Screensaver in"
                0x08 "Lock screen in"
            */
           
            switch(var){
                case 0x00: return 0;

                case 0x04: return get_backlight_light_raw();
                case 0x05: return get_delay_before_turnoffBackLight_raw();
                case 0x06: return get_backlight_fade_light_raw();
                case 0x07: return get_delay_before_ScreenSaver_raw();
                case 0x08: return get_delay_before_turnoff_raw();
            }
        }

        String get_current_set_value(byte var){
            /*
                0x04 "Brightness"
                0x05 "Fade in"
                0x06 "Fade brightness"
                0x07 "Screensaver in"
                0x08 "Lock screen in"
            */
           
            switch(var){
                case 0x00: return "0px";

                case 0x04: return String(get_backlight_light(), DEC);
                case 0x05: return value_sec_to_string_value(get_delay_before_turnoffBackLight());
                case 0x06: return String(get_backlight_light(), DEC);
                case 0x07: return value_sec_to_string_value(get_delay_before_ScreenSaver());
                case 0x08: return value_sec_to_string_value(get_delay_before_turnoff());
            }
        }

        void set_value_current_set_value(byte var, byte value){
            /*
                0x04 "Brightness"
                0x05 "Fade in"
                0x06 "Fade brightness"
                0x07 "Screensaver in"
                0x08 "Lock screen in"
            */
           
            switch(var){
                case 0x00: return ;

                case 0x04: set_backlight_light_raw(value); return;
                case 0x05: set_delay_before_turnoffBackLight_raw(value); return ;
                case 0x06: set_backlight_fade_light_raw(value); return;
                case 0x07: set_delay_before_ScreenSaver_raw(value); return ;
                case 0x08: set_delay_before_turnoff_raw(value); return ;
            }
        }
        
        void drawSetValue(){

            //drawString("Set value", 0,0);

            drawString_centered(settingMenu[current_menu_element_array_id].title, SCREEN_WIDTH/2, 2);

            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_RIGHT), SCREEN_WIDTH-4,  SCREEN_HEIGHT/2); // Arrow right
            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_LEFT), 0,                SCREEN_HEIGHT/2); // Arrow left  
            drawString_centered(get_value_current_set_value(current_set_value_var), SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
            
            if (isPressStart_Left()){
                set_value_current_set_value( current_set_value_var, (byte)(get_raw_current_set_value(current_set_value_var)+1) );
            }

            if (isPressStart_Right()){
                set_value_current_set_value( current_set_value_var, (byte)(get_raw_current_set_value(current_set_value_var)-1) );
            }

            if (isPressStart_Select()
                #ifdef control_has_backbtn
                    || isPressStart_Back()
                #endif
            ){
                current_action = 0x01;
            }
        }

        void drawCurrentMenu(){

            byte element_num = 0;
            for(byte element_i=0; element_i<MenuElement_lenght; element_i++){
                if(settingMenu[element_i].parent==current_menu){

                    drawSettingsElement(settingMenu[element_i].title, get_ValueOfMenuElement(settingMenu[element_i].id), element_num, settingMenu[element_i].icon);
                    
                    if(current_menu_position==element_num) current_menu_element_array_id = element_i;

                    element_num++;
                }
            }

            //drawDebugString(1000/dtime, 10);

            if (isPressStart_Left() && current_menu_position>0) current_menu_position--;
            if (isPressStart_Right() && current_menu_position<element_num-1) current_menu_position++;


            /*
                Exit or back event
            */
            #ifdef control_has_backbtn
            if (isPressStart_Back() || isPressStart_Select()){
                if(settingMenu[current_menu_element_array_id].action==0x04 || isPressStart_Back()){
            #else
            if (isPressStart_Select()){
                if(settingMenu[current_menu_element_array_id].action==0x04){
            #endif
                    // Back or exit
                    if(settingMenu[current_menu_element_array_id].parent==0x00) finish(); // Exit event
                    else{
                        // Back event
                        // Find previous menu
                        current_menu = 0;
                        for(byte element_i=0; element_i<MenuElement_lenght; element_i++){
                            if (settingMenu[element_i].id == settingMenu[current_menu_element_array_id].parent){
                                current_menu = settingMenu[element_i].parent;
                                break;   
                            }
                        }

                        // Find previous menu position
                        byte num=0;
                        current_menu_position = 0;
                        /* */
                        for(byte element_i=0; element_i<MenuElement_lenght; element_i++){
                            if (settingMenu[element_i].parent == current_menu){
                                if(settingMenu[element_i].id == settingMenu[current_menu_element_array_id].parent)
                                current_menu_position = num;
                                break;

                                num++;
                            }
                        }//*/

                        this->scroll_y = SCREEN_HEIGHT/2-2-current_menu_position * drawSettingsElement_height + drawSettingsElement_margin - drawSettingsElement_height/2;
                    }
                }
            }
            
            /*
                Select event
            */
            if(isPressStart_Select()){
                /*
                    0x00 - nothing
                    0x01 - open new menu
                    0x02 - set current time
                    0x03 - set num (with "+"" and "-" buttons)
                    0x04 - exit (back)
                */

                // Menu
                if(settingMenu[current_menu_element_array_id].action==0x01){
                    current_menu = settingMenu[current_menu_element_array_id].id;
                    current_menu_position = 0;
                }

                // Set current time
                else if(settingMenu[current_menu_element_array_id].action==0x02){
                    current_action = 0x02;
                }
                
                // Set value
                else if(settingMenu[current_menu_element_array_id].action==0x03){
                    current_set_value_var = settingMenu[current_menu_element_array_id].id;
                    current_action = 0x03;
                }

            }

            // Central arrow
            drawIcon( 
                (const unsigned char *)getIcon(0x01), 
                this-> scroll_x + drawSettingsElement_margin_left/2 - 2, 
                SCREEN_HEIGHT/2-3
            );

            this->scroll_to_y = SCREEN_HEIGHT/2-2-current_menu_position * drawSettingsElement_height + drawSettingsElement_margin - drawSettingsElement_height/2;

            /*
            this->scroll_to_y = SCREEN_HEIGHT/2-2-current_menu_position * drawSettingsElement_height + drawSettingsElement_margin - drawSettingsElement_height/2;

            // Central arrow
            drawIcon( 
                (const unsigned char *)getIcon(0x01), 
                this-> scroll_x + drawSettingsElement_margin_left/2 - 2, 
                SCREEN_HEIGHT/2-3
            );

            char v1[3];
            char v2[3];
            char v3[3];

            char time_string[9];
            
            int_to_char(v1, os_clock_currentTime_hour(), true);
            int_to_char(v2, os_clock_currentTime_minutes(), true);
            int_to_char(v3, os_clock_currentTime_seconds(), true);

            sprintf(time_string, "%s:%s:%s", v1, v2, v3);

            drawSettingsElement("Lock watch",   getDelayBeforTurnOff_label(),0);
            drawSettingsElement("Backlight",    getBackLight_label(),1);
            drawSettingsElement("Light time",   getDelayBeforTurnOffBackLight_label(),2);
            drawSettingsElement("Set time", time_string, 3);
            drawSettingsElement("Exit", "", 4);

            #ifdef control_has_backbtn
              if (isPressStart_Back()){
                finish();
              }
            #endif

            if (isPressStart_Select()){
                switch (current_menu_position){
                    case 4: finish(); break;
                    case 0: current_menu = 1; break;
                    case 1: current_menu = 2; break;
                    case 2: current_menu = 3; break;
                    case 3: current_menu = 4; break;
                }
                
            }
            */
        }

        // #############################
        // #############################
        // #############################
        // #############################
        // #############################
        // #############################


        virtual void loop() override{
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                                >>>   MAIN APP LOOP   <<<                                *
            *                                                                                         *
            */

            if(current_action==0x01 || current_action == 0x00)           
                drawCurrentMenu();
            else if (current_action == 0x02)
                drawSetTime();
            else if (current_action == 0x03)
                drawSetValue();

            /*
            //EVERY FRAME CODE
            switch(current_menu){
                case 0: drawSettingsMenu(); break;
                case 1: drawingSelectDeleayTurnOff(); break;
                case 2: drawingSelectBacklight(); break;
                case 3: drawingSelectDeleayTurnOffBackLight(); break;
                case 4: drawSetTime(); break;
            }
            */
            

            /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };

        char activeElement = 0;
        bool isActivated = false;

        void drawSetTime(){
            drawString_centered("Setting time", 0);

            char v1[3];
            char v2[3];
            char v3[3];
            
            int_to_char(v1, os_clock_currentTime_hour(), true);
            int_to_char(v2, os_clock_currentTime_minutes(), true);
            int_to_char(v3, os_clock_currentTime_seconds(), true);
            
            char* val1 = v1;
            char* val2 = v2;
            char* val3 = v3;
            
            //showFreeMemory(); 

            const int val_y = SCREEN_HEIGHT/2 - FONT_CHAR_HEIGHT/2;
            const int val_y_strike = SCREEN_HEIGHT/2 + FONT_CHAR_HEIGHT/2 + 3;

            const int val1_x = SCREEN_WIDTH * 1 / 5 - 1;
            const int val1_5_x = SCREEN_WIDTH * 7 / 20 - 1;
            const int val2_x = SCREEN_WIDTH * 1 / 2 - 1;
            const int val2_5_x = SCREEN_WIDTH * 13 / 20 - 1;
            const int val3_x = SCREEN_WIDTH * 4 / 5 - 1;

            drawString_centered(val1, val1_x,   val_y);
            drawString_centered(":",  val1_5_x, val_y);
            drawString_centered(val2, val2_x,   val_y);
            drawString_centered(":",  val2_5_x, val_y);
            drawString_centered(val3, val3_x,   val_y);
            
            if (isPressStart_Select()) isActivated = !isActivated;

            if (!isActivated){
                if (isPressStart_Left()) activeElement--;
                if (isPressStart_Right()) activeElement++;
             
                #ifdef control_has_backbtn  
                    if (activeElement>2) activeElement = 0;
                    if (activeElement<0) activeElement = 2;
                #else
                    if (activeElement>2||activeElement<0){
                        activeElement = 0;
                        current_action = 0x01;
                    }    
                #endif
                

                #ifdef control_has_backbtn 
                    if(isPressStart_Back()){
                        current_action = 0x01;
                    }
                #endif
                
            }else{

                #ifdef control_buttons_on_side
                    #define change_time_def (-1)
                #else
                    #define change_time_def (1)
                #endif
                //edit time
                if (isPressStart_Left()){
                    if (activeElement==2){
                        set_preset_second(os_clock_currentTime_seconds());
                    }else if (activeElement==1){
                        set_preset_minute(get_preset_minute() - 1*change_time_def);
                    }else if (activeElement==0){
                        set_preset_hour(get_preset_hour() - 1*change_time_def);
                    }
                }else if(isPressStart_Right()){
                    if (activeElement==2){
                        set_preset_second(os_clock_currentTime_seconds());
                    }else if (activeElement==1){
                        set_preset_minute(get_preset_minute() + 1*change_time_def);
                    }else if (activeElement==0){
                        set_preset_hour(get_preset_hour() + 1*change_time_def);
                    }
                }

            }
            

            if (isActivated){
                switch(activeElement){
                    case 0: 
                        drawLine(val1_x - 1 - FONT_CHAR_WIDTH*strlen(val1)/2, val_y_strike, val1_x - 1 + FONT_CHAR_WIDTH*strlen(val1)/2, val_y_strike); 
                        break;
                    case 1: 
                        drawLine(val2_x - 1 - FONT_CHAR_WIDTH*strlen(val2)/2, val_y_strike, val2_x - 1 + FONT_CHAR_WIDTH*strlen(val2)/2, val_y_strike); 
                        break;
                    case 2: 
                        drawLine(val3_x - 1 - FONT_CHAR_WIDTH*strlen(val3)/2, val_y_strike, val3_x - 1 + FONT_CHAR_WIDTH*strlen(val3)/2, val_y_strike); 
                        break;
                }
            }else{
                switch(activeElement){
                    case 0: 
                        drawIcon( (const unsigned char *)getIcon(ICON_ARROW_UP), val1_x - 5, val_y_strike + 2);
                        break;
                    case 1: 
                        drawIcon( (const unsigned char *)getIcon(ICON_ARROW_UP), val2_x - 5, val_y_strike + 2);
                        break;
                    case 2: 
                        drawIcon( (const unsigned char *)getIcon(ICON_ARROW_UP), val3_x - 5, val_y_strike + 2);
                        break;
                }
            } 
            
            #ifdef control_has_backbtn 
                if(isPressStart_Back() && isActivated) isActivated = !isActivated;                        
            #endif

        }

        void finish(){
          os_switch_to_app(-1);
        }

        void drawingSelectDeleayTurnOff(){
            
            #define diagram_height  20
            #define diagram_padding 5
            #define top_margin      (SCREEN_HEIGHT-diagram_height-diagram_padding-FONT_CHAR_HEIGHT-15)/2

            drawRect_custom(
                0, 
                top_margin + diagram_padding + diagram_height,
                SCREEN_WIDTH - 1,
                top_margin + diagram_padding + diagram_height,
                SCREEN_WIDTH - 1,
                top_margin + diagram_padding,
                0, 
                top_margin + diagram_padding + diagram_height,
                false
            );

            if (isPressStart_Left() && delay_before_turnoff!=0){delay_before_turnoff--;}
            if (isPressStart_Right() && delay_before_turnoff<10){delay_before_turnoff++;}

            drawingSelectDeleayTurnOff_value(delay_before_turnoff*10);

            if (isPressStart_Select()){
                current_menu = 0;
            }
        }

        void drawingSelectDeleayTurnOffBackLight(){
            
            #define diagram_height  20
            #define diagram_padding 5
            #define top_margin      (SCREEN_HEIGHT-diagram_height-diagram_padding-FONT_CHAR_HEIGHT-15)/2

            drawRect_custom(
                0, 
                top_margin + diagram_padding + diagram_height,
                SCREEN_WIDTH - 1,
                top_margin + diagram_padding + diagram_height,
                SCREEN_WIDTH - 1,
                top_margin + diagram_padding,
                0, 
                top_margin + diagram_padding + diagram_height,
                false
            );

            if (isPressStart_Left() && delay_before_turnoffBackLight!=0){delay_before_turnoffBackLight--;}
            if (isPressStart_Right() && delay_before_turnoffBackLight<10){delay_before_turnoffBackLight++;}

            drawingSelectDeleayTurnOffBackLight_value(delay_before_turnoffBackLight*10);

            if (isPressStart_Select()){
                current_menu = 0;
            }
        }

        void drawingSelectBacklight(){
            
            #define diagram_height  20
            #define diagram_padding 5
            #define top_margin      (SCREEN_HEIGHT-diagram_height-diagram_padding-FONT_CHAR_HEIGHT-15)/2

            drawRect_custom(
                0, 
                top_margin + diagram_padding + diagram_height,
                SCREEN_WIDTH - 1,
                top_margin + diagram_padding + diagram_height,
                SCREEN_WIDTH - 1,
                top_margin + diagram_padding,
                0, 
                top_margin + diagram_padding + diagram_height,
                false
            );

            
            if (isPressStart_Left() && backlight_light!=0){
                backlight_light--;
                #ifdef device_has_backlight_control
                    power_manager_set_backlight_strength(get_backlight_light());
                #endif
            }
            if (isPressStart_Right() && backlight_light<10){
                backlight_light++;
                #ifdef device_has_backlight_control
                    power_manager_set_backlight_strength(get_backlight_light());
                #endif    
            }

            

            drawingSelectBacklight_value(backlight_light*10);

            if (isPressStart_Select()){
                current_menu = 0;
            }
        }

        void drawingSelectBacklight_value(byte percent){
            drawRect_custom(
                0, 
                top_margin + diagram_padding + diagram_height,
                // Value nums
                (SCREEN_WIDTH - 1)*percent/100 + 1,
                top_margin + diagram_padding + diagram_height - diagram_height*percent/100,
                (SCREEN_WIDTH - 1)*percent/100 + 1,
                top_margin + diagram_padding + diagram_height,
                //
                0, 
                top_margin + diagram_padding + diagram_height,
                true
            );

            drawString_centered(getBackLight_label(), SCREEN_WIDTH/2, diagram_height + top_margin + diagram_padding*2);

            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_RIGHT), SCREEN_WIDTH-4, diagram_height + top_margin + diagram_padding*2); // Arrow right
            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_LEFT), 0,                                  diagram_height + top_margin + diagram_padding*2); // Arrow left  
        }

        void drawingSelectDeleayTurnOff_value(byte percent){
            drawRect_custom(
                0, 
                top_margin + diagram_padding + diagram_height,
                // Value nums
                (SCREEN_WIDTH - 1)*percent/100 + 1,
                top_margin + diagram_padding + diagram_height - diagram_height*percent/100,
                (SCREEN_WIDTH - 1)*percent/100 + 1,
                top_margin + diagram_padding + diagram_height,
                //
                0, 
                top_margin + diagram_padding + diagram_height,
                true
            );

            drawString_centered(getDelayBeforTurnOff_label(), SCREEN_WIDTH/2, diagram_height + top_margin + diagram_padding*2);

            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_RIGHT), SCREEN_WIDTH-4, diagram_height + top_margin + diagram_padding*2); // Arrow right
            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_LEFT), 0,                                  diagram_height + top_margin + diagram_padding*2); // Arrow left  
        }

        void drawingSelectDeleayTurnOffBackLight_value(byte percent){
            drawRect_custom(
                0, 
                top_margin + diagram_padding + diagram_height,
                // Value nums
                (SCREEN_WIDTH - 1)*percent/100 + 1,
                top_margin + diagram_padding + diagram_height - diagram_height*percent/100,
                (SCREEN_WIDTH - 1)*percent/100 + 1,
                top_margin + diagram_padding + diagram_height,
                //
                0, 
                top_margin + diagram_padding + diagram_height,
                true
            );

            drawString_centered(getDelayBeforTurnOffBackLight_label(), SCREEN_WIDTH/2, diagram_height + top_margin + diagram_padding*2);

            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_RIGHT), SCREEN_WIDTH-4, diagram_height + top_margin + diagram_padding*2); // Arrow right
            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_LEFT), 0,                                  diagram_height + top_margin + diagram_padding*2); // Arrow left  
        }

        char * getBackLight_label(){
            switch(backlight_light){
                case 0: return "0%";
                case 1: return "10%";
                case 2: return "20%";
                case 3: return "30%";
                case 4: return "40%";
                case 5: return "50%";
                case 6: return "60%";
                case 7: return "70%";
                case 8: return "80%";
                case 9: return "90%";
                case 10: return "100%";
                default: return "0%";
            }
        }

        char * getDelayBeforTurnOff_label(){
            switch(delay_before_turnoff){
                case 0: return "5 sec";
                case 1: return "10 sec";
                case 2: return "15 sec";
                case 3: return "20 sec";
                case 4: return "30 sec";
                case 5: return "45 sec";
                case 6: return "1 min";
                case 7: return "2 min";
                case 8: return "5 min";
                case 9: return "15 min";
                default: return "Never";
            }
        }

        char * getDelayBeforTurnOffBackLight_label(){
            switch(delay_before_turnoffBackLight){
                case 0: return "3 sec";
                case 1: return "5 sec";
                case 2: return "10 sec";
                case 3: return "15 sec";
                case 4: return "20 sec";
                case 5: return "30 sec";
                case 6: return "45 sec";
                case 7: return "1 min";
                case 8: return "2 min";
                case 9: return "5 min";
                default: return "Never";
            }
        }

        void drawSettingsMenu(){
            if (isPressStart_Left() && current_menu_position>0) current_menu_position--;
            if (isPressStart_Right() && current_menu_position<4) current_menu_position++;

            this->scroll_to_y = SCREEN_HEIGHT/2-2-current_menu_position * drawSettingsElement_height + drawSettingsElement_margin - drawSettingsElement_height/2;

            // Central arrow
            drawIcon( 
                (const unsigned char *)getIcon(0x01), 
                this-> scroll_x + drawSettingsElement_margin_left/2 - 2, 
                SCREEN_HEIGHT/2-3
            );

            char v1[3];
            char v2[3];
            char v3[3];

            char time_string[9];
            
            int_to_char(v1, os_clock_currentTime_hour(), true);
            int_to_char(v2, os_clock_currentTime_minutes(), true);
            int_to_char(v3, os_clock_currentTime_seconds(), true);

            sprintf(time_string, "%s:%s:%s", v1, v2, v3);

            drawSettingsElement("Lock watch",   getDelayBeforTurnOff_label(),0, 0);
            drawSettingsElement("Backlight",    getBackLight_label(),1, 0);
            drawSettingsElement("Light time",   getDelayBeforTurnOffBackLight_label(),2, 0);
            drawSettingsElement("Set time", time_string, 3, 0);
            drawSettingsElement("Exit", "", 4, 0);

            #ifdef control_has_backbtn
              if (isPressStart_Back()){
                finish();
              }
            #endif

            if (isPressStart_Select()){
                switch (current_menu_position){
                    case 4: finish(); break;
                    case 0: current_menu = 1; break;
                    case 1: current_menu = 2; break;
                    case 2: current_menu = 3; break;
                    case 3: current_menu = 4; break;
                }
                
            }
        }

        void drawSettingsElement(String label, String value, byte position, byte icon){
            drawRect(this-> scroll_x + drawSettingsElement_margin_left, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_margin, this-> scroll_x + SCREEN_WIDTH - drawSettingsElement_margin, this-> scroll_y + position * drawSettingsElement_height - drawSettingsElement_margin + drawSettingsElement_height);
            drawString(label, this-> scroll_x + drawSettingsElement_margin_left + drawSettingsElement_padding, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_padding + drawSettingsElement_margin);
            drawString(value, this-> scroll_x + drawSettingsElement_margin_left + drawSettingsElement_padding, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_padding + drawSettingsElement_margin + FONT_CHAR_HEIGHT + drawSettingsElement_padding_label_value);

            drawIcon( 
                (const unsigned char *)getIcon(icon), 
                this-> scroll_x + SCREEN_WIDTH - drawSettingsElement_margin - drawSettingsElement_padding - 16, 
                this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_padding + drawSettingsElement_margin + 2
            );
        }

        /*      
        void drawSettingsElement(char *label, char *value, byte position, byte icon){
            drawRect(this-> scroll_x + drawSettingsElement_margin_left, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_margin, this-> scroll_x + SCREEN_WIDTH - drawSettingsElement_margin, this-> scroll_y + position * drawSettingsElement_height - drawSettingsElement_margin + drawSettingsElement_height);
            drawString(label, this-> scroll_x + drawSettingsElement_margin_left + drawSettingsElement_padding, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_padding + drawSettingsElement_margin);
            drawString(value, this-> scroll_x + drawSettingsElement_margin_left + drawSettingsElement_padding, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_padding + drawSettingsElement_margin + FONT_CHAR_HEIGHT + drawSettingsElement_padding_label_value);

            drawIcon( 
                (const unsigned char *)getIcon(icon), 
                this-> scroll_x + SCREEN_WIDTH - drawSettingsElement_margin - drawSettingsElement_padding - 16, 
                this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_padding + drawSettingsElement_margin + 2
            );
        }
        */
        
        void setup(){
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                              >>>   APP SETUP ON START   <<<                             *
            *                                                                                         *
            */

            // ON START APP CODE
            //this->scroll_y = 1-current_menu_position * drawSettingsElement_height + drawSettingsElement_margin + drawSettingsElement_height/2;
            this->scroll_y = SCREEN_HEIGHT/2-2-current_menu_position * drawSettingsElement_height + drawSettingsElement_margin - drawSettingsElement_height/2;
           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */
        };

    static unsigned const char* getParams(unsigned char type){
            switch(type){ 
              case PARAM_TYPE_NAME: return (unsigned char*)appName; 
              case PARAM_TYPE_ICON: return icon;
              default: return (unsigned char*)""; }
        };

    const static byte icon[];

        appNameClass(){ // Constructor
            setup();
        };

};

const byte appNameClass::icon[] PROGMEM = {
  //////////////////////////////////////////////////////////////
  //    PUT YOUR ICON HERE
  #ifdef colorScreen
    0x02,0x01,0x02,0x20,0x02,0x20,0x04,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x07,0xE0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,
    0x00,0x00,0x07,0xE0,0x00,0x00,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x04,0xb4,0xb4,0xb4,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x08,0x0F,0xF0,0x10,
    0x1C,0x3F,0xFC,0x38,0x3E,0x7F,0xFE,0x7C,0x7F,0xF8,0x1F,0xFE,0xFF,0xE0,0x07,0xFF,0xFF,0xC0,0x03,0xFF,0x7F,0x80,0x01,0xFE,0x3F,0x00,0x00,
    0xFC,0x1F,0x00,0x00,0xF8,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,
    0x00,0x70,0x1F,0x00,0x00,0xF8,0x3F,0x00,0x00,0xFC,0x7F,0x80,0x01,0xFE,0xFF,0xC0,0x03,0xFF,0xFF,0xE0,0x07,0xFF,0x7F,0xF8,0x1F,0xFE,0x3E,
    0x7F,0xFE,0x7C,0x1C,0x3F,0xFC,0x38,0x08,0x0F,0xF0,0x10,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,
    0x04,0x47,0x47,0x47,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,0x00,0x00,0x1F,0xF8,0x00,0x00,0x3F,0xFC,0x00,0x00,0x7F,0xFE,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFC,
    0x3F,0x00,0x01,0xF8,0x1F,0x80,0x01,0xF0,0x0F,0x80,0x01,0xF0,0x0F,0x80,0x01,0xF0,0x0F,0x80,0x01,0xF0,0x0F,0x80,0x01,0xF8,0x1F,0x80,0x00,
    0xFC,0x3F,0x00,0x00,0xFF,0xFF,0x00,0x00,0x7F,0xFE,0x00,0x00,0x3F,0xFC,0x00,0x00,0x1F,0xF8,0x00,0x00,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  #else
    0x02,0x01,0x02,0x20,0x02,0x20,0x04,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x08,
    0x0F,0xF0,0x10,0x1C,0x3F,0xFC,0x38,0x3E,0x7F,0xFE,0x7C,0x7F,0xF8,0x1F,0xFE,0xFF,0xE0,0x07,0xFF,0xFF,0xC0,0x03,0xFF,0x7F,0x80,0x01,0xFE,
    0x3F,0x00,0x00,0xFC,0x1F,0x03,0xC0,0xF8,0x0E,0x07,0xE0,0x70,0x0E,0x0F,0xF0,0x70,0x0E,0x0F,0xF0,0x70,0x0E,0x0F,0xF0,0x70,0x0E,0x0F,0xF0,
    0x70,0x0E,0x07,0xE0,0x70,0x1F,0x03,0xC0,0xF8,0x3F,0x00,0x00,0xFC,0x7F,0x80,0x01,0xFE,0xFF,0xC0,0x03,0xFF,0xFF,0xE0,0x07,0xFF,0x7F,0xF8,
    0x1F,0xFE,0x3E,0x7F,0xFE,0x7C,0x1C,0x3F,0xFC,0x38,0x08,0x0F,0xF0,0x10,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,
    0x0F,0xF0,0x00,
  #endif
  //
  //////////////////////////////////////////////////////////////
};