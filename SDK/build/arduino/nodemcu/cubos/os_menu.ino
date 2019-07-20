#define appNameClass    MainMenu                // App name without spaces
#define appName         "Main menu"             // App name with spaces (max 16)

/*
class appNameClass: public Application{
    private:
        //Label *title = new Label("Tex");
        //Label *title;
    public:
        void loop() override{
            //title.draw();
            drawString("s1s",0,0);
        };
        void setup(){
            //interfaceElements = interface;
            //title = new Label("h");
            
        };

        appNameClass(){ // Constructor
            strcpy(name, appName); // Setting name of app
            //app_loop = &loop;
            setup();
        };

};*/

/*
#define os_menu_AppLabelBottomPadding  2

char* os_menu_elements[127];


byte os_menu_apps[] = {
  0x01, //"Test app 1", 
  0x01, //"Test app 2", 
  0x02, //"Clock",
  0x03, //"Settings", 
  0x04, //"Game example",
  0x01, //"APP Script VM"
};

byte os_menu_elements_length = (sizeof (os_menu_elements))/sizeof(os_menu_elements[0]);

byte os_menu_currentElement = 0;
byte os_menu_fromElement = 0;

int os_menu_x_scroll = 0;
int os_menu_tox_scroll = 0;

void setup_os_menu(){
  os_menu_initApplications();
  //os_menu_apps[0] = "Test1";
  //os_menu_apps[0] = os_menu_elements[0].getName();

  os_menu_elements[0] = "Test app 1"; 
  os_menu_elements[1] = "Test app 2"; 
  os_menu_elements[2] = "Clock";
  os_menu_elements[3] = "Settings";
  os_menu_elements[4] = "Game example";
  os_menu_elements[5] = "APP Script VM";

  os_menu_elements[0] = os_applications_list[0].getName();
  
}



/*
void loop_os_menu(){
  
  //////////////////////////////////////////////////////////////////////////////
  // Lets check the buttons
  
  if (isPressStart(2)){
    //Pressed left
    if (os_menu_currentElement == os_menu_elements_length - 1) os_menu_currentElement = 0;
    else os_menu_currentElement ++;

    os_menu_tox_scroll -= SCREEN_WIDTH; // Menu animation right
  }
  
  if (isPressStart(0)){ 
    //Pressed right
    if (os_menu_currentElement == 0) os_menu_currentElement = os_menu_elements_length - 1;
    else os_menu_currentElement --;

    os_menu_tox_scroll += SCREEN_WIDTH; // Menu animation left
  }

  //////////////////////////////////////////////////////////////////////////////
  //  Last check in case of not button change of position
  
  if (os_menu_currentElement > os_menu_elements_length - 1) os_menu_currentElement = 0;

  if (os_menu_tox_scroll!=os_menu_x_scroll){
    // Setting change of X (for animation)
    byte dx_scroll = abs(os_menu_tox_scroll-os_menu_x_scroll)/10 + 2; // X scrolling in this loop;
    //byte dx_scroll = 1; // Need for animation debugging
    
    if (os_menu_tox_scroll>os_menu_x_scroll) os_menu_x_scroll += dx_scroll;
    else os_menu_x_scroll -= dx_scroll;

    if (abs(os_menu_tox_scroll-os_menu_x_scroll)<dx_scroll) os_menu_x_scroll = os_menu_tox_scroll; // Scroll finished
  }

  //////////////////////////////////////////////////////////////////////////////
  // Draw the animation
  
  if (os_menu_x_scroll!=os_menu_tox_scroll){
    // Animation enable
    byte os_menu_currentScreenPosition = 0;

    //draw_application_icon(os_menu_currentElement, 0 + os_menu_x_scroll - os_menu_tox_scroll);
    //draw_application_icon(os_menu_fromElement, 0 + os_menu_x_scroll);

    int app_position1 = 0;
    int app_position2 = 0;
    int app_num1 = 0;
    int app_num2 = 0;

    app_position1 = os_menu_x_scroll%SCREEN_WIDTH;
    app_num1 = os_menu_fromElement - os_menu_x_scroll/SCREEN_WIDTH;
    
    if (os_menu_x_scroll<0){  
      app_position2 = os_menu_x_scroll%SCREEN_WIDTH + SCREEN_WIDTH;
      app_num2 = os_menu_fromElement - os_menu_x_scroll/SCREEN_WIDTH + 1;
    }else{
      app_position2 = os_menu_x_scroll%SCREEN_WIDTH - SCREEN_WIDTH;
      app_num2 = os_menu_fromElement - (os_menu_x_scroll/SCREEN_WIDTH + 1);
    }
    
    draw_application_icon(app_num1, app_position1);
    draw_application_icon(app_num2, app_position2);
    
    
  }else{
    os_menu_x_scroll = 0;
    os_menu_tox_scroll = 0;
    os_menu_fromElement = os_menu_currentElement;

    draw_application_icon(os_menu_currentElement, 0 + os_menu_x_scroll);
  }

  // Drawing current icon
  byte icon_size = 32;

  
  //////////////////////////////////////////////////////////////////////////////
  // Drawing arrows

  for (byte a=0; a<5; a++){
    // Arrow left  
    drawLine(a, SCREEN_HEIGHT/2-a, a, SCREEN_HEIGHT/2+a);
    // Arrow right
    drawLine(SCREEN_WIDTH - 1 - a, SCREEN_HEIGHT/2-a, SCREEN_WIDTH - 1 - a, SCREEN_HEIGHT/2+a);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Drawing image 
  
  if (os_menu_currentElement==2){
    drawIcon(os_icons_clock_32, SCREEN_WIDTH/2 - icon_size/2, 12, icon_size, icon_size);
  }else if (os_menu_currentElement==5){
    drawIcon(os_icons_virtualmachine_32, SCREEN_WIDTH/2 - icon_size/2, 12, icon_size, icon_size);
  }else if (os_menu_currentElement==3){
    drawIcon(os_icons_settings_32, SCREEN_WIDTH/2 - icon_size/2, 12, icon_size, icon_size);
  }else if (os_menu_currentElement==4){
    drawIcon(os_icons_game_32, SCREEN_WIDTH/2 - icon_size/2, 12, icon_size, icon_size);
  }else{
    drawIcon(os_icons_bin_32, SCREEN_WIDTH/2 - icon_size/2, 12, icon_size, icon_size);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Select app
  
  if (isPressStart(1)){
    current_app = os_menu_apps[os_menu_currentElement];
  }
  
}

//////////////////////////////////////////////////////////////////////////////
// App icon drawing function
void draw_application_icon(int num, int x){
  if (num >= os_menu_elements_length){
    num = num - 6;
    draw_application_icon(num, x);
  }

  if (num < 0){
    num = num + 6;
    draw_application_icon(num, x);
  }

  // Label, center of screen at bottom
  drawString(os_menu_elements[num], x + (SCREEN_WIDTH - strlen(os_menu_elements[num])*FONT_CHAR_WIDTH)/2, SCREEN_HEIGHT - FONT_CHAR_HEIGHT - os_menu_AppLabelBottomPadding);

  // Icon (Now static)
  //drawRect(x + 10, 30, x+20, 50, false);
  //byte icon_size = 32;
  //drawIcon(os_icons_getIcon_bin_32, x + SCREEN_WIDTH/2 - icon_size/2, 0, icon_size, icon_size);
}
*/