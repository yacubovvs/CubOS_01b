//#define os_MAINMENU_APP_COUNT 20

class MainMenu: public Application{
      public:
        virtual void loop() override;
        void setup();
        MainMenu(){ setup(); };
        static unsigned const char* getParams(const unsigned char type){
            switch(type){ 
              case PARAM_TYPE_NAME: return (unsigned char*)"Main menu"; 
              case PARAM_TYPE_ICON: return icon;
              default: return (unsigned char*)""; }
        };
      char* getNextAppName();
      char* getPreviousAppName();
      byte* getNextAppIcon();
      byte* getPreviousAppIcon();
      byte  checkAppId(char id);

      const static byte icon[] PROGMEM;

      #ifdef tabletView
        int mainMenu_touch_icons_position[os_MAINMENU_APP_COUNT][2];
        
        #ifdef isTouchScreen

          //int mainMenu_touch_icons_position[os_MAINMENU_APP_COUNT][2];
          
          //os_touch_x = 0;
          //os_touch_y = 0;
          
          void check_touch(){
            os_control_loop();

            if (isPressStart_Select()){
              
              uint16_t os_touch_x = get_os_touch_x();
              uint16_t os_touch_y = get_os_touch_y();
  
              for (byte i=0; i<os_MAINMENU_APP_COUNT; i++){
                if (os_touch_x>mainMenu_touch_icons_position[i][0] && os_touch_x<mainMenu_touch_icons_position[i][0] + mainMenu_icon_element_size){
                  if (os_touch_y>mainMenu_touch_icons_position[i][1] && os_touch_y<mainMenu_touch_icons_position[i][1] + mainMenu_icon_element_size){
                      os_switch_to_app(i);
                      return;
                  }
                }  
              }

              if(os_touch_x>SCREEN_WIDTH-mainMenu_scrollSize){

                const int content_height            = ((int)(os_MAINMENU_APP_COUNT/mainMenu_iconsInRow) + 1)*mainMenu_icon_element_size;
                const int content_area_height       = SCREEN_HEIGHT - appArea_margin_top;

                if(content_area_height<content_height){
                  // Here should be scroll
                  // later                
  
                  
                }
                
              }
  
            }
            
          }
          
        #endif

        #ifdef hasHardwareButtons
          
          void check_buttons(){
            //os_control_loop();

            if (isPressStart_Select()){
              os_switch_to_app(this->current_app_menu);
            }

            //drawDebugString(this->current_app_menu, 230);
            
            if (isPressStart_Left()){
               if (this->current_app_menu==0) this->current_app_menu = os_MAINMENU_APP_COUNT-1;
               else this->current_app_menu--;
            }

            if (isPressStart_Right()){
              if (this->current_app_menu==os_MAINMENU_APP_COUNT-1) this->current_app_menu=0;
              else this->current_app_menu++;
              //drawString("Right",100,100);
            }
            
          }
          
        #endif
      #endif
      
    private:
      static byte current_app_menu;
  };

  byte MainMenu::current_app_menu=0;
  const byte MainMenu::icon[] PROGMEM= {};

void MainMenu::setup(){
  #ifdef tabletView
    this->showStatusBar = true;
  #endif

  #ifdef colorScreen
    initColor_background(0x22, 0x25, 0x49);
  #endif
  
}

void MainMenu::loop(){
    
    #ifdef tabletView

    /*
     * ##################################################################################################################################
     * #                                                                                                                                #
     * #                                                         MENU FOR TABLET                                                        #
     * #                                                         (Big  displays)                                                        #
     * #                                                                                                                                #
     * ##################################################################################################################################
     * 
     */

      //#define tabletView_statusBarHeight 24
      //#define mainMenu_paddingLeft_Right 15
      //#define mainMenu_scrollSize 16
      
      //#define mainMenu_paddingLeft_Right 15
      //#define mainMenu_scrollSize 16
      
      //#define mainMenu_iconsInRow 3
      //#define SCREEN_WIDTH
      //#define SCREEN_HEIGHT
      //#define mainMenu_icon_element_size

      /////////////////////////////////////////  
      // Drawing apps icons

      const int content_height            = ((int)(os_MAINMENU_APP_COUNT/mainMenu_iconsInRow) + 1)*mainMenu_icon_element_size;
      const int content_area_height       = SCREEN_HEIGHT - appArea_margin_top;
      
      for (byte i=0; i<os_MAINMENU_APP_COUNT; i++){

        // Lets check touch between drawing
        #ifdef isTouchScreen
          check_touch();
        #endif
        
        const int ic_xpos = 0 + i%mainMenu_iconsInRow*(SCREEN_WIDTH-1)/mainMenu_iconsInRow - mainMenu_scrollSize/mainMenu_iconsInRow * (i%mainMenu_iconsInRow) + (content_height<content_area_height?mainMenu_scrollSize/2:0);
        const int ic_ypos = tabletView_statusBarHeight + i/mainMenu_iconsInRow*(SCREEN_WIDTH-1)/mainMenu_iconsInRow - (mainMenu_scrollSize/mainMenu_iconsInRow)* (int)(i/mainMenu_iconsInRow);


        #define AppIconSize 32
        const byte icon_padding_left = (mainMenu_icon_element_size - AppIconSize)/2;
        const byte icon_padding_top = (mainMenu_icon_element_size - AppIconSize - FONT_CHAR_HEIGHT/2 )/3;
        //drawIcon

        drawIcon(
          (const unsigned char * ) getAppParams( i, PARAM_TYPE_ICON),
          ic_xpos + icon_padding_left,
          ic_ypos + icon_padding_top
        );

        
        drawString_centered(
          (char* )getAppParams(i, PARAM_TYPE_NAME), 
          ic_xpos + mainMenu_icon_element_size/2, 
          ic_ypos + mainMenu_icon_element_size - icon_padding_top*3/2
        );


        //Save the position of icon
        mainMenu_touch_icons_position[i][0] = ic_xpos;
        mainMenu_touch_icons_position[i][1] = ic_ypos;
      }

      #ifdef hasHardwareButtons
        check_buttons();
      #endif
      //
      /////////////////////////////////////////
      

      /////////////////////////////////////////
      //  SHOW FRAME ON CURRENT ELEMENT IN TABLEVIEW

      #ifdef hasHardwareButtons
        const int frame_x1 = mainMenu_touch_icons_position[this->current_app_menu][0];
        const int frame_x2 = frame_x1 + mainMenu_icon_element_size;
        const int frame_y1 = mainMenu_touch_icons_position[this->current_app_menu][1];
        const int frame_y2 = frame_y1 + mainMenu_icon_element_size;
        
        drawRect(frame_x1 + frame_selected_app_padding, frame_y1 + frame_selected_app_padding, frame_x2 - frame_selected_app_padding, frame_y2 - frame_selected_app_padding);
      #endif
        
      //
      /////////////////////////////////////////
      

      /////////////////////////////////////////  
      // Drawing scroll bar

      #define scroll_y_from   tabletView_statusBarHeight + 12
      #define scroll_y_to     SCREEN_HEIGHT - 13

      const int scroll_bar_content_height = (scroll_y_to - scroll_y_from) *((float)content_area_height/(float)content_height);

      if (content_height>content_area_height){
        
        drawIcon( (const unsigned char *)getIcon(ICON_ARROW_UP), SCREEN_WIDTH - mainMenu_scrollSize/2-4 -1, tabletView_statusBarHeight + 8); // Arrow top
        
        drawLine(
          SCREEN_WIDTH - mainMenu_scrollSize/2-2, 
          scroll_y_from, 
          SCREEN_WIDTH - mainMenu_scrollSize/2-2, 
          scroll_y_to
        );
  
        drawLine(
          SCREEN_WIDTH - mainMenu_scrollSize/2-0, 
          scroll_y_from, 
          SCREEN_WIDTH - mainMenu_scrollSize/2-0, 
          scroll_y_to
        );
  
        drawRect(
          SCREEN_WIDTH - mainMenu_scrollSize/2-3,
          scroll_y_from + 2, 
          SCREEN_WIDTH - mainMenu_scrollSize/2+2, 
          min(scroll_y_from + 2 + scroll_bar_content_height-4, scroll_y_to - 3),
          true
        );
        
        drawIcon( (const unsigned char *)getIcon(ICON_ARROW_DOWN), SCREEN_WIDTH - mainMenu_scrollSize/2-4 -1 , SCREEN_HEIGHT - 12); // Arrow bottom    
        
      }
      //
      /////////////////////////////////////////
      
    #else

      /*
       * ##################################################################################################################################
       * #                                                                                                                                #
       * #                                                      MENU FOR SMART WATCH                                                      #
       * #                                                        (Small displays)                                                        #
       * #                                                                                                                                #
       * ##################################################################################################################################
       * 
       */
   
      if (this->scroll_x == this->scroll_to_x && this->scroll_x!=0){
          this->scroll_x      = 0;
          this->scroll_to_x   = 0;
      }

      #define LABEL_BOTTOM_PADDING SCREEN_HEIGHT-FONT_CHAR_HEIGHT-2

      char currentAppScreen = current_app_menu + ((int)((scroll_to_x - scroll_x)/SCREEN_WIDTH));
      int currentLabel_x = -((int)(scroll_x/SCREEN_WIDTH))*SCREEN_WIDTH;
      
      if (scroll_to_x<0){
          drawString_centered(
            (char* )getAppParams(this->checkAppId(currentAppScreen), PARAM_TYPE_NAME), 
            currentLabel_x + this->scroll_x + SCREEN_WIDTH*3/2, 
            LABEL_BOTTOM_PADDING
          );

          drawString_centered(
            (char* )getAppParams(this->checkAppId(currentAppScreen - 1), PARAM_TYPE_NAME), 
            currentLabel_x + this->scroll_x + SCREEN_WIDTH/2, 
            LABEL_BOTTOM_PADDING
          );
      
      }else if (scroll_to_x>0){
          drawString_centered(
            (char* )getAppParams(this->checkAppId(currentAppScreen), PARAM_TYPE_NAME), 
            currentLabel_x + this->scroll_x - SCREEN_WIDTH*1/2, 
            LABEL_BOTTOM_PADDING
          );

          drawString_centered(
            (char* )getAppParams(this->checkAppId(currentAppScreen + 1), PARAM_TYPE_NAME), 
            currentLabel_x + this->scroll_x + SCREEN_WIDTH/2, 
            LABEL_BOTTOM_PADDING
          );
      }else{
        drawString_centered(
          (char* )getAppParams(this->checkAppId(currentAppScreen), PARAM_TYPE_NAME), 
          currentLabel_x + this->scroll_x + SCREEN_WIDTH/2, 
          LABEL_BOTTOM_PADDING
        );  
      }
      
      //current_label   -> draw(this);


      /////////////////////////////////////////////
      //  Not scrollable element

      // Arrows
      drawIcon( (const unsigned char *)getIcon(ICON_ARROW_RIGHT), SCREEN_WIDTH-4, (SCREEN_HEIGHT-7)/2); // Arrow right
      drawIcon( (const unsigned char *)getIcon(ICON_ARROW_LEFT), 0, (SCREEN_HEIGHT-7)/2); // Arrow left  
      
      // Icons
      drawIcon( (const unsigned char *)getAppParams(this->checkAppId(this->current_app_menu),(PARAM_TYPE_ICON)), (SCREEN_WIDTH - 32)/2 -1, (SCREEN_HEIGHT - 32)/2.5);
      //
      /////////////////////////////////////////////

      //Check buttons events
      if (isPressStart_Left()){
          this->scroll_to_x += SCREEN_WIDTH;
          this->current_app_menu --;
          this->current_app_menu = this->checkAppId(this->current_app_menu);
      }
      if (isPressStart_Right()){
          this->scroll_to_x -= SCREEN_WIDTH;
          this->current_app_menu ++;
          this->current_app_menu = this->checkAppId(this->current_app_menu);
      }

      if (isPressStart_Select()){
        os_switch_to_app(this->current_app_menu);
      }   

    #endif  
}

byte  MainMenu::checkAppId(char id){
    if(id<0){
        id+=get_application_count();
        return this->checkAppId(id);
    }
    if(id>=get_application_count()){
        id-=get_application_count();
        return this->checkAppId(id);
    }
    return id;
}

void app_mainmenu_start(){
  currentApp = new MainMenu();
  driver_clearScreen();
};