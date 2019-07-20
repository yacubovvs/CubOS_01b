

/*
  Version 0.0
  Requirements: 
    - os_display
    - os_basic
    - os_clock

  +---------------------------------+
  |  menu_element_label             |
  |             menu_element_value  |
  +---------------------------------+
  
*/

//////////////////////////////////////////////////////////////////
// STYLES

#define menu_frame_margin_top               2
#define menu_frame_margin_right             2
#define menu_frame_margin_bottom            4
#define menu_frame_margin_left              10

#define menu_element_label_padding_left     6
#define menu_element_label_padding_top      4
#define menu_element_label_padding_bottom   2

#define menu_element_value_padding_right    4
#define menu_element_value_padding_top      2
#define menu_element_value_padding_bottom   4



char* app_settings_elements[] = {
  "",                 // 0
  "Back",             // 1
  "Exit",             // 2
  "Time and date",    // 3
  "Watch face",       // 4
  "Turn off screen",  // 5

  "Type",             // 6 - 3.0
  "24h",              // 7 - 3.0.0
  "AM/PM",            // 8 - 3.0.1

  "HH:MM",            // 9  - 4.0
  "HH:MM.ss",         // 10 - 4.1
  "Analog",           // 11 - 4.2

  "5 sec.",           // 12 - 5.0
  "10 sec.",          // 13 - 5.1
  "20 sec.",          // 14 - 5.2
  "40 sec.",          // 15 - 5.3
  "1 min",            // 16 - 5.4
  "5 min",            // 17 - 5.5
  "Allways on",       // 18 - 5.6

  "Set time",         // 19 - 3.1     
  "Set date",         // 20 - 3.2

  "Show date",        // 21
  "Yes",              // 22
  "No",               // 23

  "Analog + HH:MM",   // 24 - 4.3

};

char app_settings_values[] = {
    0,   0,   0,   0,   9, 
    18,  7,   0,   0,   0,
    0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,
    0,   22,  0,   0,   0,
};

//////////////////////////////////////////////////////
//  GET PARAMS FROM OTHER MODULES

boolean app_settings_isampm(){
  return app_settings_values[6]==8;
}

byte get_app_settings_watchface(){
  return app_settings_values[4];
}

boolean get_app_settings_showdate(){
  app_settings_values[21]==22;
}

void set_app_settings_watchface(byte val){
  app_settings_values[4] = val;
}

//
//////////////////////////////////////////////////////

char menu_size = 1;
char app_settings_mainmenu[] =      {  3,  5,  2 };                       // 0
char app_settings_timemenu[] =      {  1,  4,  21, 6, 19, 20 };           // 3
char app_settings_watchface[] =     {  1,  9,  10, 11};                  // 4
char app_settings_showdate[] =      { 1,  22,  23 };                      // 21
char app_settings_turnoffscreen[] = {  1, 12,  13, 14, 15, 16, 17, 18 };  // 5
char app_settings_time_typemenu[] = {  1,  7,  8 };                       // 6

const int single_menu_elemen_height = FONT_CHAR_HEIGHT * 2 + menu_frame_margin_top + menu_frame_margin_bottom + menu_element_label_padding_top + menu_element_label_padding_bottom + menu_element_value_padding_top + menu_element_value_padding_bottom;

int  app_setting_scroll_y = (SCREEN_HEIGHT - single_menu_elemen_height)/2 + 1;
int  app_setting_scroll_to_y = app_setting_scroll_y;

byte activeElement = 0;

byte currentElement = 0;
byte currentMenu = 0;

bool isActivated = false;

void app_settings_loop(){
  if (isPressStart(1) && currentMenu!=19 && currentMenu!=20){
    app_settings_onPressSelect();
  }
  
  draw_menu();

  if (isPressStart(3)){
    app_finish(); //Exit to menu
  }
  
}

void draw_menu(char* menu, byte menu_size_arr){
  // Drawing arrow
  for (byte a=0; a<5; a++){
    drawLine(4-a, SCREEN_HEIGHT/2-a, 4-a, SCREEN_HEIGHT/2+a);
  }
  
  menu_size = menu_size_arr;
  currentElement = menu[activeElement];
  
  for (int i=0; i<menu_size; i++){
    draw_menu_element(menu[i],  i);
  }

  ////////////////////////////////////////////////////
  // Scroll and scroll animation

  // Buttons hendlers
  if (isPressStart(2) && menu_size-1>activeElement){
    activeElement ++;
    app_setting_scroll_to_y = (SCREEN_HEIGHT - single_menu_elemen_height)/2 + 1 - activeElement*single_menu_elemen_height;
  }else if(isPressStart(0) && activeElement!=0){
    activeElement --;
    app_setting_scroll_to_y = (SCREEN_HEIGHT - single_menu_elemen_height)/2 + 1 - activeElement*single_menu_elemen_height;
  }

  // Animation
  if (app_setting_scroll_to_y != app_setting_scroll_y){
    int d_y_animation = abs(app_setting_scroll_to_y - app_setting_scroll_y)/10 + 2;
    if (app_setting_scroll_to_y<app_setting_scroll_y) d_y_animation *= -1;
    
    app_setting_scroll_y += d_y_animation; 

    // If scroll finished
    if (abs(app_setting_scroll_to_y - app_setting_scroll_y)<=d_y_animation) app_setting_scroll_to_y = app_setting_scroll_y;
  }

  // Drawing arrow
  for (byte a=0; a<5; a++){
    drawLine(4-a, SCREEN_HEIGHT/2-a, 4-a, SCREEN_HEIGHT/2+a);
  }
  
}


// Drawing menu element
void draw_menu_element(char element, char position){
  drawRect(menu_frame_margin_left, app_setting_scroll_y + single_menu_elemen_height*position + menu_frame_margin_top, SCREEN_WIDTH - menu_frame_margin_right, app_setting_scroll_y + single_menu_elemen_height*(position+1) - menu_frame_margin_bottom);

  // Element label
  drawString(app_settings_elements[element], menu_frame_margin_left + menu_element_label_padding_left, app_setting_scroll_y + position * single_menu_elemen_height + menu_frame_margin_top + menu_element_label_padding_top);

  // Element value
  char* value_label = getValue_ofMenuElement(element);
  drawString(value_label, SCREEN_WIDTH - strlen(value_label)*FONT_CHAR_WIDTH - menu_frame_margin_right - menu_element_value_padding_right, app_setting_scroll_y + position * single_menu_elemen_height + menu_frame_margin_top + menu_element_label_padding_top + menu_element_label_padding_bottom + menu_element_value_padding_top + FONT_CHAR_HEIGHT);
  
}

char* getValue_ofMenuElement(char element){
  if (element==19)        return os_clock_get_currentTime_String();
  else if (element==20)   return os_clock_get_currentDate_String();
  else                    return app_settings_elements[app_settings_values[element]];
}

///////////////////////////////////////////////////////////////////////
//  DRAW SELECT TIME
void draw_select_time(){
  drawString_centered("Setting time", 0);

  char* val1 = "am 12";
  char* val2 = "02";
  char* val3 = "59";

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

  if (isPressStart(1)) isActivated = !isActivated;

  if (isActivated){
      if (activeElement == 0) drawLine(val1_x - 1 - FONT_CHAR_WIDTH*strlen(val1)/2, val_y_strike, val1_x - 1 + FONT_CHAR_WIDTH*strlen(val1)/2, val_y_strike);
      if (activeElement == 1) drawLine(val2_x - 1 - FONT_CHAR_WIDTH*strlen(val2)/2, val_y_strike, val2_x - 1 + FONT_CHAR_WIDTH*strlen(val2)/2, val_y_strike);
      if (activeElement == 2) drawLine(val3_x - 1 - FONT_CHAR_WIDTH*strlen(val3)/2, val_y_strike, val3_x - 1 + FONT_CHAR_WIDTH*strlen(val3)/2, val_y_strike);
  }
  
  draw_arror_select_dateTime(SCREEN_WIDTH/5, SCREEN_WIDTH/5, 3, SCREEN_HEIGHT*0.75 );
}

///////////////////////////////////////////////////////////////////////
//  DRAW SELECT DATE
void draw_select_date(){
  drawString_centered("Setting date", 0);

  char* val1 = "01";
  char* val2 = "Jun";
  char* val3 = "2019";
  
  const int val_y = SCREEN_HEIGHT/2 - FONT_CHAR_HEIGHT/2;
  const int val_y_strike = SCREEN_HEIGHT/2 + FONT_CHAR_HEIGHT/2 + 3;
  
  const int val1_x = SCREEN_WIDTH * 1 / 5;
  const int val2_x = SCREEN_WIDTH * 1 / 2;
  const int val3_x = SCREEN_WIDTH * 4 / 5;
  
  drawString_centered(val1, val1_x, val_y);
  drawString_centered(val2, val2_x, val_y);
  drawString_centered(val3, val3_x, val_y);

  if (isPressStart(1)) isActivated = !isActivated;

  if (isActivated){
      if (activeElement == 0) drawLine(val1_x - 1 - FONT_CHAR_WIDTH*strlen(val1)/2, val_y_strike, val1_x - 1 + FONT_CHAR_WIDTH*strlen(val1)/2, val_y_strike);
      if (activeElement == 1) drawLine(val2_x - 1 - FONT_CHAR_WIDTH*strlen(val2)/2, val_y_strike, val2_x - 1 + FONT_CHAR_WIDTH*strlen(val2)/2, val_y_strike);
      if (activeElement == 2) drawLine(val3_x - 1 - FONT_CHAR_WIDTH*strlen(val3)/2, val_y_strike, val3_x - 1 + FONT_CHAR_WIDTH*strlen(val3)/2, val_y_strike);
  }
  
  draw_arror_select_dateTime(SCREEN_WIDTH/5, SCREEN_WIDTH/5, 3, SCREEN_HEIGHT*0.75 );
}

///////////////////////////////////////////////////////////////////////
//  DRAWNG ARROW FOR SETTING DATE AND TIME

int app_setting_scroll_x = 0;

void draw_arror_select_dateTime(int left_margin, int right_margin, int position_counts, int y){
  
  ////////////////////////////////////////////////////
  // Scroll and scroll animation for arrow X
  int app_setting_scroll_to_x = 0;
  
  // Buttons hendlers
  if (isPressStart(2)){
    if (isActivated){
    }else{
      if (position_counts-1>activeElement) activeElement ++;
      else app_settings_onPressSelect();
    }
  }else if(isPressStart(0)){
    if (isActivated){
    }else{
      if (activeElement!=0) activeElement --;
      else app_settings_onPressSelect();
    }
  }

  app_setting_scroll_to_x = left_margin + (SCREEN_WIDTH - left_margin - right_margin)/(position_counts-1)*activeElement - 2;
  
  // Animation
  if (app_setting_scroll_to_x != app_setting_scroll_x){
    int d_x_animation = abs(app_setting_scroll_to_x - app_setting_scroll_x)/10 + 1;
    if (app_setting_scroll_to_x<app_setting_scroll_x) d_x_animation *= -1;
    
    app_setting_scroll_x += d_x_animation; 

    // If scroll finished
    if (abs(app_setting_scroll_to_x - app_setting_scroll_x)<=d_x_animation) app_setting_scroll_x = app_setting_scroll_to_x;
    //drawDebugString(d_x_animation, 0);
    //app_setting_scroll_to_x = app_setting_scroll_x;
  }  

  // Drawing arrow
  for (byte a=0; a<5; a++){
    drawLine(app_setting_scroll_x + (a), y + a, app_setting_scroll_x - (a), y + a);
  }

  
  
}

///////////////////////////////////////////////////////////////////////
//  USER ACTIONS
void draw_menu(){
  if (currentMenu==0)         draw_menu(app_settings_mainmenu,       sizeof (app_settings_mainmenu)      /  sizeof(app_settings_mainmenu[0])      );
  else if (currentMenu==3)    draw_menu(app_settings_timemenu,       sizeof (app_settings_timemenu)      /  sizeof(app_settings_timemenu[0])      );
  else if (currentMenu==4)    draw_menu(app_settings_watchface,      sizeof (app_settings_watchface)     /  sizeof(app_settings_watchface[0])     );
  else if (currentMenu==21)   draw_menu(app_settings_showdate,       sizeof (app_settings_showdate)      /  sizeof(app_settings_showdate[0])     );
  else if (currentMenu==5)    draw_menu(app_settings_turnoffscreen,  sizeof (app_settings_turnoffscreen) /  sizeof(app_settings_turnoffscreen[0]) );
  else if (currentMenu==6)    draw_menu(app_settings_time_typemenu,  sizeof (app_settings_time_typemenu) /  sizeof(app_settings_time_typemenu[0]) );
  else if (currentMenu==19)   draw_select_time();
  else if (currentMenu==20)   draw_select_date();
  else                        draw_menu(app_settings_mainmenu,       sizeof (app_settings_mainmenu)      /  sizeof(app_settings_mainmenu[0])      );
}

// On select press
void app_settings_onPressSelect(){
  activeElement = 0;
  
  if (currentMenu==0){
    if (currentElement==2){
      app_finish(); //Exit to menu
    }
    else if (currentElement==3){
      currentMenu = 3; 
    }
    else if (currentElement==5){
      currentMenu = 5; 
    }
    /*
    char app_settings_timemenu[] = {6,19,20,1}; // 3
    char app_settings_watchface[] = {9,10,11,1}; // 4
    char app_settings_turnoffscreen[] = {12,13,14,15,16,17,18,1};//5
    */
  }

  else if (currentMenu==3){ // Time menu
    
    if (currentElement==6){ // Go to the Time -> Type menu
      currentMenu = 6; 
    }else if (currentElement==19){ // Go to the Time -> Change time
      //app_setting_scroll_x = SCREEN_WIDTH * 2 / 5;
      currentMenu = 19; 
      activeElement = 0;
      isActivated = true;
    }else if (currentElement==20){ // Go to the Time -> Change date
      //app_setting_scroll_x = SCREEN_WIDTH * 2 / 5;
      currentMenu = 20;
      activeElement = 0; 
      isActivated = true;
    }else if (currentElement==4){
      currentMenu = 4; 
    }else if (currentElement==21){ // Go to the Time -> Change date
      //app_setting_scroll_x = SCREEN_WIDTH * 2 / 5;
      currentMenu = 21;
      activeElement = 0; 
      isActivated = true;
    }else{
      currentMenu = 0; 
    }
  }

  else if (currentMenu==4){ // Watchface
    
    if(currentElement==9){
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==10){
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==11){
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==24){
      app_settings_values[currentMenu]=currentElement;
    }

    currentMenu = 3; 
    activeElement = 1;

  }

  else if (currentMenu==5){

    if(currentElement==12){ // 5 sec.
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==13){ // 10 sec.
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==14){ // 15 sec.
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==15){ // 20 sec
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==16){ // 1 min
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==17){ // 5 min
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==18){ // Allways on
      app_settings_values[currentMenu]=currentElement;
    }

    currentMenu = 0; 
    activeElement = 1;
  }

  else if (currentMenu==6){ // Time time (24h / am-pm)
    
    if(currentElement==7){
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==8){
      app_settings_values[currentMenu]=currentElement;
    }

    currentMenu = 3; 
    activeElement = 3;
  }

  else if (currentMenu==21){ // Time show date (Yes/No)
    
    if(currentElement==22){
      app_settings_values[currentMenu]=currentElement;
    }else if(currentElement==23){
      app_settings_values[currentMenu]=currentElement;
    }

    currentMenu = 3; 
    activeElement = 2;
  }

  ///////////////////////////////////////////////////////
  // In select date and time
  else if (currentMenu==19){
    activeElement = 4;
    currentMenu = 3;
  }
  else if(currentMenu==20){
    activeElement = 5;
    currentMenu = 3;
  }

  app_setting_scroll_y = ((SCREEN_HEIGHT - single_menu_elemen_height)/2 + 1 - activeElement*single_menu_elemen_height);
  app_setting_scroll_to_y = app_setting_scroll_y;
}
