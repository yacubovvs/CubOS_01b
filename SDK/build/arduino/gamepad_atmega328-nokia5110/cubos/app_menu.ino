void MainMenu::setup(){}

void MainMenu::loop(){
    
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
    drawIcon( (const unsigned char *)getIcon(0x01), SCREEN_WIDTH-4, (SCREEN_HEIGHT-7)/2, 4, 7); // Arrow right
    drawIcon( (const unsigned char *)getIcon(0x02), 0,                                  (SCREEN_HEIGHT-7)/2, 4, 7); // Arrow left  
    
    // Icons
    drawIcon( (const unsigned char *)getAppParams(this->checkAppId(this->current_app_menu),(PARAM_TYPE_ICON)), (SCREEN_WIDTH - 32)/2 -1, (SCREEN_HEIGHT - 32)/2.5, 32, 32);
    //
    /////////////////////////////////////////////

    //Check buttons events
    if (isPressStart_Left()){
        this->scroll_to_x += SCREEN_WIDTH;
        current_app_menu --;
        current_app_menu = this->checkAppId(current_app_menu);
    }
    if (isPressStart_Right()){
        this->scroll_to_x -= SCREEN_WIDTH;
        current_app_menu ++;
        current_app_menu = this->checkAppId(current_app_menu);
    }


    if (isPressStart_Select()){
      os_switch_to_app(this->current_app_menu);
    }      
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

