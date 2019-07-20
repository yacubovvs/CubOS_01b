/* -- core.cpp -- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <cstring>
#include <ctime>
#include <cmath>

#define boolean bool
#define byte unsigned char

#define PROGMEM /**/

#define ICON_ARROW_RIGHT 	0x01
#define ICON_ARROW_LEFT 	0x02
#define ICON_ARROW_UP 		0x03
#define ICON_ARROW_DOWN 	0x04

/* Predeclared function + */
int min(int a1, int a2){if (a1<a2) return a1; else return a2;}
int max(int a1, int a2){if (a1>a2) return a1; else return a2;}
byte min(byte a1, byte a2){if (a1<a2) return a1; else return a2;}
byte max(byte a1, byte a2){if (a1>a2) return a1; else return a2;}
void delay(int t){}
unsigned long millis(){return clock()/4;}
void setup();
void loop();
bool digitalRead_buf[6] = {false, false, false, false, false, false};
////////////////////////////////////////////////////
//      PREDECLARATE ALL PLATFORMS FUNCTIONS
//boolean app_settings_isampm();
void set_app_settings_watchface(byte val);
byte get_app_settings_watchface();
void drawIcon(const unsigned char* data, int x, int y, byte width, byte height);
void os_control_setup();
void setup_displayDriver();
void clearscreen_displayDriver();
unsigned int os_clock_update();
void os_control_loop();
void loop_os_splashscreen();
void app_clock_loop();
void app_settings_loop();
void app_game_loop();
void loop_os_menu();
void loop_os_splashscreen();
void updatescreen_displayDriver();
void draw_application_icon(int num, int x);
void drawLine(int x0, int y0, int x1, int y1);
void drawLine(int x0, int y0, int x1, int y1, bool no_limits);
void setStr(char * dString, int x, int y);
void setStr_d(char * dString, int x, int y);
void draw_arror_select_dateTime(int left_margin, int right_margin, int position_counts, int y);
void app_settings_onPressSelect();
void draw_digit(byte digit, byte pos, int scale, int label_x, int label_y);
void draw_menu_element(char element, char position);
char* getValue_ofMenuElement(char element);
void draw_menu();
void drawRect(int x0, int y0, int x1, int y1);
void drawRect(int x0, int y0, int x1, int y1, boolean fill);
void drawRect(int x0, int y0, int x1, int y1, boolean fill, bool no_limits);
void setPixel(int x, int y, bool no_limits);
void drawString(char * dString, int x, int y);
void drawString(char * dString, int x, int y, bool no_limits);
const unsigned char * getAppParams(byte i, unsigned char type);
const byte get_application_count();
void showFreeMemory();
const byte* getIcon(byte icon);
boolean isPressStart_Left();
boolean isPressStart_Right();
void int_to_char(char *string, int num, bool fillNull);
void drawRect_custom( int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, boolean fill, boolean no_limits);
//
////////////////////////////////////////////////////
//void drawIcon(unsigned char* data, int x, int y, byte width, byte height);
void drawIcon(const unsigned char* data, int x, int y, byte width, byte height);
/* Predeclared function - */

const unsigned char pgm_read_word(const unsigned char * ch){
  return *ch;
}

const unsigned char pgm_read_word(const unsigned char ch){
  return ch;
}

bool screen_map[] = {
1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

char hash_screen[2048];

char char_to_hashcode(int ch){
    switch(ch){
        case 0:return "a"[0];
        case 1:return "b"[0];
        case 2:return "c"[0];
        case 3:return "d"[0];
        case 4:return "e"[0];
        case 5:return "f"[0];
        case 6:return "g"[0];
        case 7:return "h"[0];
        case 8:return "i"[0];
        case 9:return "j"[0];
        case 10:return "k"[0];
        case 11:return "l"[0];
        case 12:return "m"[0];
        case 13:return "n"[0];
        case 14:return "o"[0];
        case 15:return "p"[0];

        default: return " "[0];
    }
}

void generateScreenHash(){
    //hash_screen[0] = char_to_hashcode(3);
    
    for (int i=0; i<128*64/4; i++){
        int val = 
        screen_map[i*4 + 0] * 1 + 
        screen_map[i*4 + 1] * 2 + 
        screen_map[i*4 + 2] * 4 + 
        screen_map[i*4 + 3] * 8;

        hash_screen[i] = char_to_hashcode(val);
    }
    
}

int main()
{
  setup();
  int one = 1, client_fd;
  struct sockaddr_in svr_addr, cli_addr;
  socklen_t sin_len = sizeof(cli_addr);
 
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    err(1, "can't open socket");
 
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
 
  int port = 8081;
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = INADDR_ANY;
  svr_addr.sin_port = htons(port);
 
  if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
    close(sock);
    err(1, "Can't bind");
  }
 
  //listen(sock, 2);
  listen(sock, 5);// - default

  while (1) {

    loop();

    //setStr_d("FFF debug string", 10, 10);
    generateScreenHash();

    client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
    const int max_client_buffer_size = 1024;

    if (client_fd == -1) {
      perror("Can't accept");
      continue;
    }
 
    char resp_header[] = "HTTP/1.1 200 OK\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "Access-Control-Allow-Credentials: false\r\n"
    "Access-Control-Allow-Methods: GET,POST\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n\r\n";

    char resp_answer_start[] = 
    "{\"rsv_btns\":\"000000\",\"width\":128,\"height\":64,\"colors\":1,\"buttons\":4,\"data\":\""; //width height colors buttons screen_data


    char resp3_answer_end[] = "\"}"
    "\r\n";

    char buf[1024];
    bzero(buf,sizeof(buf));
    recv(client_fd, buf, sizeof(buf),0);
    
    if (buf[5]=="1"[0]){  resp_answer_start[13] = "1"[0]; digitalRead_buf[0]=true;}else{digitalRead_buf[0]=false;}
    if (buf[6]=="1"[0]){  resp_answer_start[14] = "1"[0]; digitalRead_buf[1]=true;}else{digitalRead_buf[1]=false;}
    if (buf[7]=="1"[0]){  resp_answer_start[15] = "1"[0]; digitalRead_buf[2]=true;}else{digitalRead_buf[2]=false;}
    if (buf[8]=="1"[0]){  resp_answer_start[16] = "1"[0]; digitalRead_buf[3]=true;}else{digitalRead_buf[3]=false;}
    if (buf[9]=="1"[0]){  resp_answer_start[17] = "1"[0]; digitalRead_buf[4]=true;}else{digitalRead_buf[4]=false;}
    if (buf[10]=="1"[0]){ resp_answer_start[18] = "1"[0]; digitalRead_buf[5]=true;}else{digitalRead_buf[5]=false;}
    

    char response[
      strlen(resp_header) + 
      strlen(resp_answer_start) + 
      strlen(resp3_answer_end) + 
      strlen(hash_screen)];

    //sprintf(response, "%s%s%s%s", buf, resp1, hash_screen, resp3);
    sprintf(response, "%s%s%s%s", resp_header, resp_answer_start, hash_screen, resp3_answer_end);


    write(client_fd, response, sizeof(response) - 1); /*-1:'\0'*/



    close(client_fd);
  }
}

/* -- settings/sdk.ino -- */
/*
    SDK SETTINGS
*/

#define useNativeMenu/* -- os_icons.ino -- */

//unsigned char arrow_right[] = {0b00101111, 0b10110010};
//unsigned char arrow_left[] = {0b10011011, 0b11101000};

const unsigned char arrow_left[]  PROGMEM = {0b11001000, 0b11111110, 0b11001110, 0b00001000}; //4x7
const unsigned char arrow_right[] PROGMEM = {0b00110001, 0b11110111, 0b00110111, 0b00000001}; //4x7

const unsigned char arrow_up[] PROGMEM = {0b00010000, 0b00111000, 0b01111100, 0b11111110};    //8x4
const unsigned char arrow_down[] PROGMEM = {0b11111110, 0b01111100, 0b00111000, 0b00010000};  //8x4

const byte* getIcon(byte icon){
  switch (icon){
    case ICON_ARROW_RIGHT: return arrow_right;
    case ICON_ARROW_LEFT: return arrow_left;
    case ICON_ARROW_UP: return arrow_up;
    case ICON_ARROW_DOWN: return arrow_down;
    default: return {0};
  }
}

/*
byte* getIcon(byte icon){
  return os_icons_getIcon_bin_48;
}
*/

/*
unsigned char os_icons_bin_32[] = {
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
};

unsigned char os_icons_clock_32[] = {
0x00, 0xF0, 0x0F, 0x00, 0x00, 0xFE, 0x7F, 0x00, 
0x80, 0x9F, 0xF9, 0x00, 0xC0, 0x83, 0xC1, 0x03, 
0xE0, 0x01, 0x80, 0x07, 0x70, 0x00, 0x00, 0x0E, 
0x38, 0x80, 0x01, 0x1C, 0x18, 0x80, 0x01, 0x38, 
0x1C, 0x80, 0x01, 0x38, 0x0E, 0x80, 0x01, 0x70, 
0x06, 0x80, 0x01, 0x60, 0x06, 0x80, 0x01, 0x60, 
0x07, 0x80, 0x01, 0xE0, 0x03, 0x80, 0x01, 0xC0, 
0x03, 0x80, 0x01, 0xC0, 0x0F, 0xE0, 0x7F, 0xF0, 
0x0F, 0xE0, 0x7F, 0xF0, 0x03, 0x80, 0x01, 0xC0, 
0x03, 0x80, 0x01, 0xC0, 0x07, 0x00, 0x00, 0xE0, 
0x06, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x60, 
0x0E, 0x00, 0x00, 0x70, 0x1C, 0x00, 0x00, 0x38, 
0x1C, 0x00, 0x00, 0x18, 0x38, 0x00, 0x00, 0x1C, 
0x70, 0x00, 0x00, 0x0E, 0xE0, 0x01, 0x80, 0x07, 
0xC0, 0x83, 0xC1, 0x03, 0x00, 0x9F, 0xF9, 0x01, 
0x00, 0xFE, 0x7F, 0x00, 0x00, 0xF0, 0x0F, 0x00, 
};

unsigned char os_icons_virtualmachine_32[] = {
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
};

unsigned char os_icons_settings_32[] = {
0x00, 0x0C, 0x30, 0x00, 0x00, 0x1E, 0x78, 0x00, 
0x00, 0x3F, 0xFC, 0x00, 0x00, 0x7F, 0xFE, 0x00, 
0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 
0x00, 0xFF, 0xFF, 0x00, 0x80, 0xFF, 0xFF, 0x01, 
0xFE, 0x1F, 0xF8, 0x7F, 0xFF, 0x0F, 0xF0, 0xFF, 
0xFF, 0x07, 0xE0, 0xFF, 0xFE, 0x03, 0xC0, 0x7F, 
0xFC, 0x01, 0x80, 0x3F, 0xF8, 0x01, 0x80, 0x1F, 
0xF0, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x0F, 
0xF0, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x1F, 
0xFC, 0x01, 0x80, 0x3F, 0xFE, 0x01, 0x80, 0x7F, 
0xFF, 0x03, 0xC0, 0xFF, 0xFF, 0x07, 0xE0, 0xFF, 
0xFF, 0x0F, 0xF0, 0xFF, 0xFE, 0x3F, 0xFC, 0x7F, 
0x80, 0xFF, 0xFF, 0x01, 0x00, 0xFF, 0xFF, 0x00, 
0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 
0x00, 0x3F, 0xFC, 0x00, 0x00, 0x1F, 0xF8, 0x00, 
0x00, 0x1E, 0x78, 0x00, 0x00, 0x0C, 0x30, 0x00, 
};

unsigned char os_icons_game_32[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x80, 0x07, 
0xE0, 0x01, 0x80, 0x07, 0xE0, 0x01, 0x80, 0x07, 
0xE0, 0x01, 0x80, 0x07, 0xE0, 0x0F, 0xF0, 0x07, 
0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 
0x80, 0xFF, 0xFF, 0x01, 0xC0, 0xFF, 0xFF, 0x03, 
0xE0, 0xFF, 0xFF, 0x07, 0xF0, 0xF7, 0xEF, 0x0F, 
0xF8, 0xE3, 0xC7, 0x1F, 0xF8, 0xE3, 0xC7, 0x1F, 
0xFF, 0xE3, 0xC7, 0xFF, 0xFF, 0xF7, 0xEF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xF3, 
0xCF, 0xFF, 0xFF, 0xF3, 0xCF, 0xFF, 0xFF, 0xF3, 
0xCF, 0x01, 0x80, 0xF3, 0xCF, 0x01, 0x80, 0xF3, 
0xCF, 0x3F, 0xFC, 0xF3, 0x00, 0x3F, 0xFC, 0x00, 
0x00, 0x3F, 0xFC, 0x00, 0x00, 0x3F, 0xFC, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
*//* -- cubos.ino -- */


byte current_app = 0x00; // Splashscreen
unsigned int dtime = 0;

/*
**************************************
*                                    *
*            APPLICATIONS +          *
*                                    *
**************************************
*/
#define ICON_ARROW_RIGHT 	0x01
#define ICON_ARROW_LEFT 	0x02
#define ICON_ARROW_UP 		0x03
#define ICON_ARROW_DOWN 	0x04

#define PARAM_TYPE_ICON 0x01
#define PARAM_TYPE_NAME 0x02

/////////////////////////////////////
// APPLICATION CLASS
class Application{
	public:
		int scroll_x	= 0;
		int scroll_y	= 0;
		int scroll_to_x			= 0;
		int scroll_to_y			= 0;
		virtual void loop()=0;
		void loop_app(){
			loop();

			int dy=0; int dx =0;

			if(scroll_x!=scroll_to_x){
				dx = abs(scroll_x-scroll_to_x)/7 + 2;
				if(scroll_x>scroll_to_x) dx *= -1;
				scroll_x+=dx;

				if (abs(scroll_x-scroll_to_x)<abs(dx)) scroll_to_x=scroll_x;
			}

			if(scroll_y!=scroll_to_y){
				dy = abs(scroll_y-scroll_to_y)/7 + 2;
        if(scroll_y>scroll_to_y) dy *= -1;
        scroll_y+=dy;

        if (abs(scroll_y-scroll_to_y)<abs(dy)) scroll_y=scroll_to_y;
			}
		}
        Application(){};
};

Application* currentApp;
//
/////////////////////////////////////
#ifdef useNativeMenu
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
			
		private:
			static char current_app_menu;
	};

	char MainMenu::current_app_menu=0;
	const byte MainMenu::icon[] PROGMEM= {
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
	};

	Application *getApp(byte i);
	////////////////////////////////////

	void os_switch_to_app(byte app_numm){
		delete currentApp;
		currentApp = getApp(app_numm);
	}
#endif
/*
**************************************
*                                    *
*            APPLICATIONS -          *
*                                    *
**************************************
*/
void setup()
{ 
  setup_displayDriver();
	os_control_setup();
	//setup_os_menu();
	#ifdef useNativeMenu
		currentApp = new MainMenu(); // Start first app
	#else
		BOOT_FUNC();
	#endif
}

void loop(){
	clearscreen_displayDriver();
	dtime = os_clock_update();
	
	os_control_loop(); // Check buttons
	currentApp->loop_app();
	
	

  ////////////////////////////////////////////////////////////////////
  //  Debug string data
      showFreeMemory(); // show free memory
      //drawDebugString(1000/dtime, 10); // show time need for 1 loop
      //drawDebugString(millis()/1000, 55); // show time need for 1 loop
  //
  ////////////////////////////////////////////////////////////////////

  updatescreen_displayDriver();
}/* -- os_controls_sdk.ino -- */

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
  PARAMS
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/
// device buttons count
const byte os_control_buttons = 6; 

boolean os_control_pressStart[] = {false, false, false, false, false, false};
boolean os_control_pressEnd[]   = {false, false, false, false, false, false};
boolean os_control_press[]      = {false, false, false, false, false, false};

int os_control_buttonsAdr[] = {0,1,2,3,4,5};
/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
  HENDLER
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/
bool digitalRead(byte btn){
  return !digitalRead_buf[btn];
}


void os_control_setup(){
  
  
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button started to press
boolean isPressStart(int num){
  if (num>=os_control_buttons) return false;
  else return os_control_pressStart[num];
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button [ress finished
boolean isPressEnd(int num){
  if (num>=os_control_buttons) return false;
  else return os_control_pressEnd[num];
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button pressed
boolean isPress(int num){
  if (num>=os_control_buttons) return false;
  else return os_control_press[num];
}

//////////////////
//  User friendly btns
boolean controls_Right(byte num){
  return isPressStart(num);
}

boolean controls_Left(byte num){
  return isPressStart(num);
}

boolean controls_Select(byte num){
  return isPressStart(num);
}
/////////////////
void os_control_loop(){
  
  for (byte i=0; i<os_control_buttons; i++){
    if (!digitalRead(os_control_buttonsAdr[i])){
      if(os_control_pressStart[i]){
        // 2-nd loop after press
        os_control_pressStart[i]  = false;
      }else{
        if (os_control_press[i]){
          // 3+ loop after press
          // do nothing
        }else{
          // just pressed
          os_control_pressStart[i]  = true;
          os_control_press[i]       = true;
        }
      }
    }else{
      // Not pressed
      if (os_control_press[i]){
        os_control_pressStart[i]  = false;
        os_control_press[i]       = false;
        os_control_pressEnd[i]    = true;
      }else{
        if (os_control_pressEnd[i]){
          // 2-nd loop after press;
          os_control_pressEnd[i] = false;
        }else{
          // Not pressed more 2 loops
          // Do nothing, relax
        }
      }
    }
  }
  
}

//////////////////////////////////////////////////////////////////////////////
//  Events for apps
boolean isPressStart_Left(){
  return isPressStart(0);
}

boolean isPressStart_Select(){
  return isPressStart(1);
}

boolean isPressStart_Right(){
  return isPressStart(2);
}
//
///////////////////////////////////////////////////////////////////////////////* -- os_menu.ino -- */


//////////////////////////////////////////////////////////////
// SETTING TIME AND DATE

unsigned int preset_day = 1; // 0 - 65534

char preset_hour = 0;
char preset_minute = 0;
char preset_second = 0;

//////////////////////////////////////////////////////////////
// HARDWARE CLOCK

unsigned long os_clock_time = 0;

unsigned int os_clock_update(){

  if (os_clock_time>millis()){
    // millis was reseted
    os_clock_time = millis();
    return 0;
  }

  //drawDebugString( os_clock_currentTime_hour(), 0);
  //drawDebugString( os_clock_currentTime_minutes(), 10);
  //drawDebugString( os_clock_currentTime_seconds(), 20);
  
  int dt = millis() - os_clock_time;
  os_clock_time = millis();
  return dt;
}

//////////////////////////////////////////////////////////////
// GETTING TIME 

char* os_clock_get_currentTime_String(){
  return "12:37";
}


bool os_clock_currentTime_hour_isam(){
  return false;
  //return app_settings_isampm();
}

byte os_clock_currentTime_hour(){
  byte hour = (preset_hour + ((millis()/1000 + preset_second)/60 + preset_minute)/60)%24;
  if (os_clock_currentTime_hour_isam() && hour>12) return hour%12;
  else return hour;
}

byte os_clock_currentTime_minutes(){
  return (preset_minute + (millis()/1000 + preset_second)/60)%60;
}

byte os_clock_currentTime_seconds(){
  return (preset_second + millis()/1000)%60;
}

void set_preset_hour(char val){
  preset_hour = val;
  if (preset_hour<0) preset_hour += 24;
  preset_hour = preset_hour%24;
}

void set_preset_minute(char val){
  preset_minute = val;
  if (preset_minute<0) preset_minute += 60;
  preset_minute = preset_minute%60;
}

void set_preset_second(char val){
  preset_second += (60-val);
  preset_second = preset_second%60;
}

char get_preset_hour(){return preset_hour;}
char get_preset_minute(){return preset_minute;}
char get_preset_second(){return preset_second;}/* -- os_basic.ino -- */
/*
*************************************
*                                   *
*          BASIC FUNCTIONS          *
*                                   *
*************************************
*/

const float pi = 3.141592;

// Finish application (go to the main app)
void app_finish(){
    current_app = 0x01;
}

const float get_pi(){
    return pi;
}

char * int_to_char(int val){
    char str[2] = "";
    printf(str, "%d", val);
    return str;
}

void int_to_char(char *string, int num, bool fillNull){
    sprintf(string, (num<10&&fillNull?"0%d":"%d"), num);
}
/* -- os_display.ino -- */

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

                                  DISPLAY FUNCTIONS

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

//////////////////////////////////////////////////
// Function needed for CubOS
void drawString(char * dString, int x, int y){
  setStr(dString, x, y);
}

void drawString_centered(char * dString, int y){
  drawString(dString, (SCREEN_WIDTH - strlen(dString)*FONT_CHAR_WIDTH)/2, y);  
}

void drawString_centered(char * dString, int x, int y){
  drawString(dString, x - strlen(dString)*FONT_CHAR_WIDTH/2, y);  
}

void drawPixel(int x, int y, bool no_limits){
  setPixel(x, y, no_limits);
}

void drawPixel(int x, int y){
  drawPixel(x, y, false);
}

void drawLine(int x0, int y0, int x1, int y1){
    drawLine(x0, y0, x1, y1, false);
}

void drawLine(int x0, int y0, int x1, int y1, bool no_limits){
  int dy = y1 - y0; // Difference between y0 and y1
  int dx = x1 - x0; // Difference between x0 and x1
  int stepx, stepy;

  if (dy < 0)
  {
    dy = -dy;
    stepy = -1;
  }
  else
    stepy = 1;

  if (dx < 0)
  {
    dx = -dx;
    stepx = -1;
  }
  else
    stepx = 1;

  dy <<= 1; // dy is now 2*dy
  dx <<= 1; // dx is now 2*dx
  drawPixel(x0, y0, no_limits); // Draw the first pixel.

  if (dx > dy) 
  {
    int fraction = dy - (dx >> 1);
    while (x0 != x1)
    {
      if (fraction >= 0)
      {
        y0 += stepy;
        fraction -= dx;
      }
      x0 += stepx;
      fraction += dy;
      drawPixel(x0, y0, no_limits);
    }
  }
  else
  {
    int fraction = dx - (dy >> 1);
    while (y0 != y1)
    {
      if (fraction >= 0)
      {
        x0 += stepx;
        fraction -= dy;
      }
      y0 += stepy;
      fraction += dx;
      drawPixel(x0, y0, no_limits);
    }
  }
}

void drawRect(int x0, int y0, int x1, int y1){
  drawRect(x0, y0, x1, y1, false, false);
}

void drawRect(int x0, int y0, int x1, int y1, boolean fill){
  drawRect(x0, y0, x1, y1, fill, false);
}

void drawRect(int x0, int y0, int x1, int y1, boolean fill, boolean no_limits){
  // check if the rectangle is to be filled
  if (fill == 1)
  {
    int xDiff;

    if(x0 > x1)
      xDiff = x0 - x1; //Find the difference between the x vars
    else
      xDiff = x1 - x0;

    while(xDiff > 0)
    {
      drawLine(x0, y0, x0, y1, no_limits);

      if(x0 > x1)
        x0--;
      else
        x0++;

      xDiff--;
    }
  }
  else 
  {
    // best way to draw an unfilled rectangle is to draw four lines
    drawLine(x0, y0, x1, y0, no_limits);
    drawLine(x0, y1, x1, y1, no_limits);
    drawLine(x0, y0, x0, y1, no_limits);
    drawLine(x1, y0, x1, y1, no_limits);
  }
}

int treangle_area(int x0, int y0, int x1, int y1, int x2, int y2){
  //a-0
  //b-1
  //c-2
   return round(abs((x0 - x2)*(y1 - y2) + (x1-x2)*(y2-y0)));
}

void drawRect_custom( int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, boolean fill){
  drawRect_custom(x0, y0, x1, y1, x2, y2, x3, y3, fill, false);
}


void drawRect_custom( int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, boolean fill, boolean no_limits){
  if (fill){
    // all angles should be less thаn 180 degrees
    const int min_x = min(min(x0, x1), min(x2, x3));
    const int max_x = max(max(x0, x1), max(x2, x3));
    const int min_y = min(min(y0, y1), min(y2, y3));
    const int max_y = max(max(y0, y1), max(y2, y3));

    for (int i_x=min_x; i_x<max_x; i_x++){
      for (int i_y=min_y; i_y<max_y; i_y++){

        if (
          treangle_area(x0, y0, x1, y1, x2, y2) ==
          treangle_area(x0, y0, x1, y1, i_x, i_y) + 
          treangle_area(x0, y0, x2, y2, i_x, i_y) + 
          treangle_area(x2, y2, x1, y1, i_x, i_y)
          || 
          treangle_area(x0, y0, x3, y3, x2, y2) ==
          treangle_area(x0, y0, x3, y3, i_x, i_y) + 
          treangle_area(x0, y0, x2, y2, i_x, i_y) + 
          treangle_area(x2, y2, x3, y3, i_x, i_y)
        ){
          drawPixel(i_x, i_y, no_limits);
        }
      }
    }    
  }else{
    drawLine(x0, y0, x1, y1, no_limits);
    drawLine(x1, y1, x2, y2, no_limits);
    drawLine(x2, y2, x3, y3, no_limits);
    drawLine(x3, y3, x0, y0, no_limits);
  }
}

void drawIcon(const unsigned char* data, int x, int y, byte width, byte height){

  byte icon_x = 0;
  byte icon_y = 0;

  //if (width<8) x = x - 8 + width; // Костыль
  for (uint8_t data_i=0; data_i<width*height; data_i++){
    //unsigned char data_char = data[data_i];
    unsigned char data_char = (char)pgm_read_word(&(data[data_i]));
    
    for (unsigned char d=0; d<8; d++){
      if (data_char&1<<d)  drawPixel(x + icon_x%8 + (icon_x/8)*8,y + icon_y, false);
      icon_x ++;

      if (icon_x==width){
        icon_x = 0;
        icon_y++;
      }
      if (icon_y==height) return;
    }

  }

}

//////////////////////////////////////////////////
// For debugging
void drawDebugString(int val, int y){  
  char str[11];
  int number = val;
  sprintf(str, "%d", number);
  drawString( str, 0, y);
}

void drawDebugString(char * val){
  
  // DEBUGGING
  // Problems in SDK
  /*
  int a=val;
  char b[10];
  String str;
  str=String(a);
  str.toCharArray(b,10);
  drawString( b, 0, y);
  */
}/* -- driver_display_sdk.ino -- */

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            CUBOS PARAMS / FUNCTION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/
#define LCD_WIDTH   128 // Note: x-coordinates go wide
#define LCD_HEIGHT  64  // Note: y-coordinates go high

static const unsigned char font[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
	0x18, 0x3C, 0x7E, 0x3C, 0x18,
	0x1C, 0x57, 0x7D, 0x57, 0x1C,
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
	0x00, 0x18, 0x3C, 0x18, 0x00,
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
	0x00, 0x18, 0x24, 0x18, 0x00,
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
	0x30, 0x48, 0x3A, 0x06, 0x0E,
	0x26, 0x29, 0x79, 0x29, 0x26,
	0x40, 0x7F, 0x05, 0x05, 0x07,
	0x40, 0x7F, 0x05, 0x25, 0x3F,
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
	0x7F, 0x3E, 0x1C, 0x1C, 0x08,
	0x08, 0x1C, 0x1C, 0x3E, 0x7F,
	0x14, 0x22, 0x7F, 0x22, 0x14,
	0x5F, 0x5F, 0x00, 0x5F, 0x5F,
	0x06, 0x09, 0x7F, 0x01, 0x7F,
	0x00, 0x66, 0x89, 0x95, 0x6A,
	0x60, 0x60, 0x60, 0x60, 0x60,
	0x94, 0xA2, 0xFF, 0xA2, 0x94,
	0x08, 0x04, 0x7E, 0x04, 0x08,
	0x10, 0x20, 0x7E, 0x20, 0x10,
	0x08, 0x08, 0x2A, 0x1C, 0x08,
	0x08, 0x1C, 0x2A, 0x08, 0x08,
	0x1E, 0x10, 0x10, 0x10, 0x10,
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
	0x30, 0x38, 0x3E, 0x38, 0x30,
	0x06, 0x0E, 0x3E, 0x0E, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5F, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x07, 0x00,
	0x14, 0x7F, 0x14, 0x7F, 0x14,
	0x24, 0x2A, 0x7F, 0x2A, 0x12,
	0x23, 0x13, 0x08, 0x64, 0x62,
	0x36, 0x49, 0x56, 0x20, 0x50,
	0x00, 0x08, 0x07, 0x03, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00,
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
	0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0x80, 0x70, 0x30, 0x00,
	0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x60, 0x60, 0x00,
	0x20, 0x10, 0x08, 0x04, 0x02,
	0x3E, 0x51, 0x49, 0x45, 0x3E,
	0x00, 0x42, 0x7F, 0x40, 0x00,
	0x72, 0x49, 0x49, 0x49, 0x46,
	0x21, 0x41, 0x49, 0x4D, 0x33,
	0x18, 0x14, 0x12, 0x7F, 0x10,
	0x27, 0x45, 0x45, 0x45, 0x39,
	0x3C, 0x4A, 0x49, 0x49, 0x31,
	0x41, 0x21, 0x11, 0x09, 0x07,
	0x36, 0x49, 0x49, 0x49, 0x36,
	0x46, 0x49, 0x49, 0x29, 0x1E,
	0x00, 0x00, 0x14, 0x00, 0x00,
	0x00, 0x40, 0x34, 0x00, 0x00,
	0x00, 0x08, 0x14, 0x22, 0x41,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x41, 0x22, 0x14, 0x08,
	0x02, 0x01, 0x59, 0x09, 0x06,
	0x3E, 0x41, 0x5D, 0x59, 0x4E,
	0x7C, 0x12, 0x11, 0x12, 0x7C,
	0x7F, 0x49, 0x49, 0x49, 0x36,
	0x3E, 0x41, 0x41, 0x41, 0x22,
	0x7F, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x49, 0x49, 0x49, 0x41,
	0x7F, 0x09, 0x09, 0x09, 0x01,
	0x3E, 0x41, 0x41, 0x51, 0x73,
	0x7F, 0x08, 0x08, 0x08, 0x7F,
	0x00, 0x41, 0x7F, 0x41, 0x00,
	0x20, 0x40, 0x41, 0x3F, 0x01,
	0x7F, 0x08, 0x14, 0x22, 0x41,
	0x7F, 0x40, 0x40, 0x40, 0x40,
	0x7F, 0x02, 0x1C, 0x02, 0x7F,
	0x7F, 0x04, 0x08, 0x10, 0x7F,
	0x3E, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x09, 0x09, 0x09, 0x06,
	0x3E, 0x41, 0x51, 0x21, 0x5E,
	0x7F, 0x09, 0x19, 0x29, 0x46,
	0x26, 0x49, 0x49, 0x49, 0x32,
	0x03, 0x01, 0x7F, 0x01, 0x03,
	0x3F, 0x40, 0x40, 0x40, 0x3F,
	0x1F, 0x20, 0x40, 0x20, 0x1F,
	0x3F, 0x40, 0x38, 0x40, 0x3F,
	0x63, 0x14, 0x08, 0x14, 0x63,
	0x03, 0x04, 0x78, 0x04, 0x03,
	0x61, 0x59, 0x49, 0x4D, 0x43,
	0x00, 0x7F, 0x41, 0x41, 0x41,
	0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x41, 0x7F,
	0x04, 0x02, 0x01, 0x02, 0x04,
	0x40, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x03, 0x07, 0x08, 0x00,
	0x20, 0x54, 0x54, 0x78, 0x40,
	0x7F, 0x28, 0x44, 0x44, 0x38,
	0x38, 0x44, 0x44, 0x44, 0x28,
	0x38, 0x44, 0x44, 0x28, 0x7F,
	0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02,
	0x18, 0xA4, 0xA4, 0x9C, 0x78,
	0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x44, 0x7D, 0x40, 0x00,
	0x20, 0x40, 0x40, 0x3D, 0x00,
	0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00,
	0x7C, 0x04, 0x78, 0x04, 0x78,
	0x7C, 0x08, 0x04, 0x04, 0x78,
	0x38, 0x44, 0x44, 0x44, 0x38,
	0xFC, 0x18, 0x24, 0x24, 0x18,
	0x18, 0x24, 0x24, 0x18, 0xFC,
	0x7C, 0x08, 0x04, 0x04, 0x08,
	0x48, 0x54, 0x54, 0x54, 0x24,
	0x04, 0x04, 0x3F, 0x44, 0x24,
	0x3C, 0x40, 0x40, 0x20, 0x7C,
	0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x44, 0x28, 0x10, 0x28, 0x44,
	0x4C, 0x90, 0x90, 0x90, 0x7C,
	0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00,
	0x00, 0x00, 0x77, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00,
	0x02, 0x01, 0x02, 0x04, 0x02,
	0x3C, 0x26, 0x23, 0x26, 0x3C,
	0x1E, 0xA1, 0xA1, 0x61, 0x12,
	0x3A, 0x40, 0x40, 0x20, 0x7A,
	0x38, 0x54, 0x54, 0x55, 0x59,
	0x21, 0x55, 0x55, 0x79, 0x41,
	0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
	0x21, 0x55, 0x54, 0x78, 0x40,
	0x20, 0x54, 0x55, 0x79, 0x40,
	0x0C, 0x1E, 0x52, 0x72, 0x12,
	0x39, 0x55, 0x55, 0x55, 0x59,
	0x39, 0x54, 0x54, 0x54, 0x59,
	0x39, 0x55, 0x54, 0x54, 0x58,
	0x00, 0x00, 0x45, 0x7C, 0x41,
	0x00, 0x02, 0x45, 0x7D, 0x42,
	0x00, 0x01, 0x45, 0x7C, 0x40,
	0x7D, 0x12, 0x11, 0x12, 0x7D, // A-umlaut
	0xF0, 0x28, 0x25, 0x28, 0xF0,
	0x7C, 0x54, 0x55, 0x45, 0x00,
	0x20, 0x54, 0x54, 0x7C, 0x54,
	0x7C, 0x0A, 0x09, 0x7F, 0x49,
	0x32, 0x49, 0x49, 0x49, 0x32,
	0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
	0x32, 0x4A, 0x48, 0x48, 0x30,
	0x3A, 0x41, 0x41, 0x21, 0x7A,
	0x3A, 0x42, 0x40, 0x20, 0x78,
	0x00, 0x9D, 0xA0, 0xA0, 0x7D,
	0x3D, 0x42, 0x42, 0x42, 0x3D, // O-umlaut
	0x3D, 0x40, 0x40, 0x40, 0x3D,
	0x3C, 0x24, 0xFF, 0x24, 0x24,
	0x48, 0x7E, 0x49, 0x43, 0x66,
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
	0xFF, 0x09, 0x29, 0xF6, 0x20,
	0xC0, 0x88, 0x7E, 0x09, 0x03,
	0x20, 0x54, 0x54, 0x79, 0x41,
	0x00, 0x00, 0x44, 0x7D, 0x41,
	0x30, 0x48, 0x48, 0x4A, 0x32,
	0x38, 0x40, 0x40, 0x22, 0x7A,
	0x00, 0x7A, 0x0A, 0x0A, 0x72,
	0x7D, 0x0D, 0x19, 0x31, 0x7D,
	0x26, 0x29, 0x29, 0x2F, 0x28,
	0x26, 0x29, 0x29, 0x29, 0x26,
	0x30, 0x48, 0x4D, 0x40, 0x20,
	0x38, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x38,
	0x2F, 0x10, 0xC8, 0xAC, 0xBA,
	0x2F, 0x10, 0x28, 0x34, 0xFA,
	0x00, 0x00, 0x7B, 0x00, 0x00,
	0x08, 0x14, 0x2A, 0x14, 0x22,
	0x22, 0x14, 0x2A, 0x14, 0x08,
	0x55, 0x00, 0x55, 0x00, 0x55, // #176 (25% block) missing in old code
	0xAA, 0x55, 0xAA, 0x55, 0xAA, // 50% block
	0xFF, 0x55, 0xFF, 0x55, 0xFF, // 75% block
	0x00, 0x00, 0x00, 0xFF, 0x00,
	0x10, 0x10, 0x10, 0xFF, 0x00,
	0x14, 0x14, 0x14, 0xFF, 0x00,
	0x10, 0x10, 0xFF, 0x00, 0xFF,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x14, 0x14, 0x14, 0xFC, 0x00,
	0x14, 0x14, 0xF7, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x14, 0x14, 0xF4, 0x04, 0xFC,
	0x14, 0x14, 0x17, 0x10, 0x1F,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0x1F, 0x00,
	0x10, 0x10, 0x10, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0xF0, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xFF, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x14,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x1F, 0x10, 0x17,
	0x00, 0x00, 0xFC, 0x04, 0xF4,
	0x14, 0x14, 0x17, 0x10, 0x17,
	0x14, 0x14, 0xF4, 0x04, 0xF4,
	0x00, 0x00, 0xFF, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0xF7, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x17, 0x14,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0xF4, 0x14,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x00, 0x00, 0x1F, 0x10, 0x1F,
	0x00, 0x00, 0x00, 0x1F, 0x14,
	0x00, 0x00, 0x00, 0xFC, 0x14,
	0x00, 0x00, 0xF0, 0x10, 0xF0,
	0x10, 0x10, 0xFF, 0x10, 0xFF,
	0x14, 0x14, 0x14, 0xFF, 0x14,
	0x10, 0x10, 0x10, 0x1F, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x38, 0x44, 0x44, 0x38, 0x44,
	0xFC, 0x4A, 0x4A, 0x4A, 0x34, // sharp-s or beta
	0x7E, 0x02, 0x02, 0x06, 0x06,
	0x02, 0x7E, 0x02, 0x7E, 0x02,
	0x63, 0x55, 0x49, 0x41, 0x63,
	0x38, 0x44, 0x44, 0x3C, 0x04,
	0x40, 0x7E, 0x20, 0x1E, 0x20,
	0x06, 0x02, 0x7E, 0x02, 0x02,
	0x99, 0xA5, 0xE7, 0xA5, 0x99,
	0x1C, 0x2A, 0x49, 0x2A, 0x1C,
	0x4C, 0x72, 0x01, 0x72, 0x4C,
	0x30, 0x4A, 0x4D, 0x4D, 0x30,
	0x30, 0x48, 0x78, 0x48, 0x30,
	0xBC, 0x62, 0x5A, 0x46, 0x3D,
	0x3E, 0x49, 0x49, 0x49, 0x00,
	0x7E, 0x01, 0x01, 0x01, 0x7E,
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
	0x44, 0x44, 0x5F, 0x44, 0x44,
	0x40, 0x51, 0x4A, 0x44, 0x40,
	0x40, 0x44, 0x4A, 0x51, 0x40,
	0x00, 0x00, 0xFF, 0x01, 0x03,
	0xE0, 0x80, 0xFF, 0x00, 0x00,
	0x08, 0x08, 0x6B, 0x6B, 0x08,
	0x36, 0x12, 0x36, 0x24, 0x36,
	0x06, 0x0F, 0x09, 0x0F, 0x06,
	0x00, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x00, 0x10, 0x10, 0x00,
	0x30, 0x40, 0xFF, 0x01, 0x01,
	0x00, 0x1F, 0x01, 0x01, 0x1E,
	0x00, 0x19, 0x1D, 0x17, 0x12,
	0x00, 0x3C, 0x3C, 0x3C, 0x3C,
	0x00, 0x00, 0x00, 0x00, 0x00  // #255 NBSP
};



void clearscreen_displayDriver(){
    //for (int i; i< driver_display_screenWidth*driver_display_screenHeight; i++){
    //    bzero(screen_map,sizeof(screen_map));
    //}
    bzero(screen_map,sizeof(screen_map)); 
}

void updatescreen_displayDriver(){
}

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            INITING ON SETUP
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

void setup_displayDriver(){
}

void setStr(char * dString, int x, int y){
        
    for (int i=0; i<strlen(dString); i++){

        unsigned char data[5] = {font[dString[i] *5 + 0], font[dString[i] *5 + 1], font[dString[i] *5 + 2], font[dString[i] *5 + 3], font[dString[i] *5 + 4]};
        
        unsigned char icon_x = 0;
        unsigned char icon_y = 0;

        for (char data_i=0; data_i<5; data_i++){
            unsigned char data_char = data[data_i];
            
            for (unsigned char d=0; d<8; d++){

            int delv = 256;
            switch(d){
                case 0: delv = 256; break;   case 1: delv = 128; break;   case 2: delv = 64; break;   case 3: delv = 32; break;
                case 4: delv = 16; break;    case 5: delv = 8; break;     case 6: delv = 4; break;    case 7: delv = 2; break;
            }
            
            data_char = (data_char % delv );
            if (data_char / (delv / 2) ==1) drawPixel(x + icon_y + i*driver_display_charWidth,y + (8 - icon_x%8) + (icon_x/8)*8);
            icon_x ++;

            //drawPixel(x + icon_x,y + icon_y);

            if (icon_x==8){
                icon_x = 0;
                icon_y++;
            }
            if (icon_y==6) return;
            }

        }
    }
}

void setStr_d(char * dString, int x, int y){
    //perror("Debugging string output");
    
    for (int i=0; i<strlen(dString); i++){

        unsigned char data[5] = {font[dString[i] *5 + 0], font[dString[i] *5 + 1], font[dString[i] *5 + 2], font[dString[i] *5 + 3], font[dString[i] *5 + 4]};
        
        unsigned char icon_x = 0;
        unsigned char icon_y = 0;

        for (int data_i=0; data_i<4; data_i++){
            unsigned char data_char = data[data_i];
            
            for (unsigned char d=0; d<8; d++){

            int delv = 256;
            switch(d){
                case 0: delv = 256; break;   case 1: delv = 128; break;   case 2: delv = 64; break;   case 3: delv = 32; break;
                case 4: delv = 16; break;    case 5: delv = 8; break;     case 6: delv = 4; break;    case 7: delv = 2; break;
            }
            
            data_char = (data_char % delv );
            if (data_char / (delv / 2) ==1) drawPixel(x + icon_y + i*driver_display_charWidth,y + (8 - icon_x%8) + (icon_x/8)*8);
            icon_x ++;

            //drawPixel(x + icon_x,y + icon_y);

            if (icon_x==8){
                icon_x = 0;
                icon_y++;
            }
            if (icon_y==5) return;
            }

        }
    }
}

void setPixel(int x, int y, bool no_limits){
    if (y*SCREEN_WIDTH + x>=128*64) return;
    if (y*SCREEN_WIDTH + x<0) return;
	if (y>=SCREEN_HEIGHT || y<0 || x<0 || x>=SCREEN_WIDTH) return;
    screen_map[y*SCREEN_WIDTH + x] = true;
}/* -- app_*.ino -- */
char current_watchface = 0;

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                                                                                         *
 *                                  >>>   IMPORTANT!   <<<                                 *
 *                  DO NOT FORGET TO ADD YOUR APP IN os_applications.ino                   *
 *                                                                                         *
 *                                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#define appNameClass    ClockApp           // App name without spaces
#define appName         "Clock"            // App name with spaces (max 16)

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
            app_clock_loop();

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

            // ON START APP ODE

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

		const static byte icon[] PROGMEM;

        appNameClass(){ // Constructor
            setup();
        };

    byte digitMap[11][2] = {
      { 0b11110110, 0b11011110 }, // Digit map - 0
      { 0b01001001, 0b00100100 }, // Digit map - 1
      { 0b11100111, 0b11001110 }, // Digit map - 2
      { 0b11100111, 0b10011110 }, // Digit map - 3
      { 0b10110111, 0b10010010 }, // Digit map - 4
      { 0b11110011, 0b10011110 }, // Digit map - 5
      { 0b11110011, 0b11011110 }, // Digit map - 6
      { 0b11100100, 0b10010010 }, // Digit map - 7
      { 0b11110111, 0b11011110 }, // Digit map - 8
      { 0b11110111, 0b10011110 }, // Digit map - 9
      { 0b00001000, 0b00100000 }, // Digit map - :
    };

    void draw_digit(byte digit, byte pos, int scale, int label_x, int label_y){
      for (int i=0; i<15; i++){
        if (digitMap[digit][i/8]&1<<(7-i%8)){
          
          int x = label_x + pos*4*scale + (i%3)*scale;
          int y = label_y + (i/3)*scale;     
          drawRect( x, y, x + scale, y + scale-1, true);  
          
        }
      }
    }
    
		#define WATCHFACES_COUNT 3

    ////////////////////////////
    //  WATCHFACES:
    //  1. Digital - HH:MM
    //  2. Digital - HH:MM:SS
    //  3. Analog

		void app_clock_loop(){

			if (isPressStart_Left()){
				current_watchface++;
				if (current_watchface>=WATCHFACES_COUNT) current_watchface=0;
			}else if (isPressStart_Right()){
				current_watchface--;
				if (current_watchface<0) current_watchface = WATCHFACES_COUNT-1;
			}

			const int center_x = SCREEN_WIDTH/2;
			const int center_y = SCREEN_HEIGHT/2;

			const int radius_small = min(center_x, center_y);
			const int radius_big = max(center_x, center_y);

			if (current_watchface==0 || current_watchface==1){
				int scale = min(SCREEN_WIDTH/(current_watchface==0?19:31), SCREEN_HEIGHT/5);
				int x = (SCREEN_WIDTH - scale*(current_watchface==0?19:31))/2;
				int y = (SCREEN_HEIGHT - scale*5)/2;
				
				draw_digit(os_clock_currentTime_hour()/10,  0, scale, x, y);
				draw_digit(os_clock_currentTime_hour()%10,  1, scale, x, y);
				draw_digit(10, 2, scale, x, y);
				draw_digit(os_clock_currentTime_minutes()/10, 3, scale, x, y);
				draw_digit(os_clock_currentTime_minutes()%10, 4, scale, x, y);
				
				if(current_watchface==1){
					draw_digit(10, 5, scale, x, y);
					draw_digit(os_clock_currentTime_seconds()/10, 6, scale, x, y);
					draw_digit(os_clock_currentTime_seconds()%10, 7, scale, x, y);
				}
			}else if(current_watchface==2){

				// Drawing lines
				// 1. Bold lines 

				#define analog_boldlines_height 	2
				#define analog_boldlines_width 		2
				#define analog_smalllines_height 	0

				drawRect(center_x + analog_boldlines_width - 1, center_y - radius_small, center_x - analog_boldlines_width, center_y - radius_small + analog_boldlines_height, true); // top
				drawRect(center_x + analog_boldlines_width - 1, center_y + radius_small - analog_boldlines_height-1, center_x - analog_boldlines_width, center_y + radius_small-1, true); // bottom

				drawRect(center_x + radius_small, center_y + analog_boldlines_width - 1, center_x + radius_small - analog_boldlines_height - 1, center_y - analog_boldlines_width + 1, true); // right
				drawRect(center_x - radius_small, center_y + analog_boldlines_width - 1, center_x - radius_small + analog_boldlines_height + 1, center_y - analog_boldlines_width + 1, true); // left

				// 2. Small lines
				#define i_max 24
				for (byte i=0; i<i_max; i++){
					float i_cos = cos(360/i_max*i*get_pi()/180);
					float i_sin = sin(360/i_max*i*get_pi()/180);
					drawLine(center_x + round((radius_small - analog_smalllines_height) * i_cos), center_y + round((radius_small - analog_smalllines_height) * i_sin), center_x + round(radius_small * i_cos), center_y + round(radius_small * i_sin));
				}
				
				// 3. Drawing arrows
				#define analog_arrow_hour_length 			    radius_small*0.70
				#define analog_arrow_hour_back_length     radius_small*0.20
				#define analog_arrow_hour_width 			    radius_small*0.06

				#define analog_arrow_minutes_length 		  radius_small*0.87
				#define analog_arrow_minutes_back_length 	radius_small*0.30
				#define analog_arrow_minutes_width 			  radius_small*0.04

				#define analog_arrow_seconds_length 		  radius_small*0.95
				#define analog_arrow_seconds_back_length 	radius_small*0.35
				#define analog_arrow_seconds_width			  0

				// Hours
				byte hours = os_clock_currentTime_hour();
				float radian_angle_arrow_cos 	= cos(-360/12*((hours+3)%12)*get_pi()/180);
				float radian_angle_arrow_sin    = sin(-360/12*((hours+3)%12)*get_pi()/180);

				drawRect_custom(
					center_x - analog_arrow_hour_length*radian_angle_arrow_cos - analog_arrow_hour_width*radian_angle_arrow_sin, 			center_y + analog_arrow_hour_length*radian_angle_arrow_sin - analog_arrow_hour_width*radian_angle_arrow_cos,
					center_x + analog_arrow_hour_back_length*radian_angle_arrow_cos - analog_arrow_hour_width*radian_angle_arrow_sin, 	center_y - analog_arrow_hour_back_length*radian_angle_arrow_sin - analog_arrow_hour_width*radian_angle_arrow_cos,
					center_x + analog_arrow_hour_back_length*radian_angle_arrow_cos + analog_arrow_hour_width*radian_angle_arrow_sin, 	center_y - analog_arrow_hour_back_length*radian_angle_arrow_sin + analog_arrow_hour_width*radian_angle_arrow_cos,
					center_x - analog_arrow_hour_length*radian_angle_arrow_cos + analog_arrow_hour_width*radian_angle_arrow_sin, 			center_y + analog_arrow_hour_length*radian_angle_arrow_sin + analog_arrow_hour_width*radian_angle_arrow_cos,
					true
				);

				// Minutes
				byte minutes = os_clock_currentTime_minutes();
				radian_angle_arrow_cos 	= cos(-360/60*((minutes+15)%60)*get_pi()/180);
				radian_angle_arrow_sin  = sin(-360/60*((minutes+15)%60)*get_pi()/180);


				drawRect_custom(
					center_x - analog_arrow_minutes_length*radian_angle_arrow_cos - analog_arrow_minutes_width*radian_angle_arrow_sin, 		center_y + analog_arrow_minutes_length*radian_angle_arrow_sin - analog_arrow_minutes_width*radian_angle_arrow_cos,
					center_x + analog_arrow_minutes_back_length*radian_angle_arrow_cos - analog_arrow_minutes_width*radian_angle_arrow_sin, 	center_y - analog_arrow_minutes_back_length*radian_angle_arrow_sin - analog_arrow_minutes_width*radian_angle_arrow_cos,
					center_x + analog_arrow_minutes_back_length*radian_angle_arrow_cos + analog_arrow_minutes_width*radian_angle_arrow_sin, 	center_y - analog_arrow_minutes_back_length*radian_angle_arrow_sin + analog_arrow_minutes_width*radian_angle_arrow_cos,
					center_x - analog_arrow_minutes_length*radian_angle_arrow_cos + analog_arrow_minutes_width*radian_angle_arrow_sin, 		center_y + analog_arrow_minutes_length*radian_angle_arrow_sin + analog_arrow_minutes_width*radian_angle_arrow_cos,
					true
				);

				// Seconds
				byte seconds = os_clock_currentTime_seconds();
				radian_angle_arrow_cos = cos(-360/60*((seconds+15)%60)*get_pi()/180);
				radian_angle_arrow_sin = sin(-360/60*((seconds+15)%60)*get_pi()/180);

				drawLine(
					center_x - analog_arrow_seconds_length*radian_angle_arrow_cos - analog_arrow_seconds_width*radian_angle_arrow_sin, 			center_y + analog_arrow_seconds_length*radian_angle_arrow_sin - analog_arrow_seconds_width*radian_angle_arrow_cos,
					center_x + analog_arrow_seconds_back_length*radian_angle_arrow_cos - analog_arrow_seconds_width*radian_angle_arrow_sin, 	center_y - analog_arrow_seconds_back_length*radian_angle_arrow_sin - analog_arrow_seconds_width*radian_angle_arrow_cos
				);
			}

		}

};

const byte appNameClass::icon[] PROGMEM =  {  //128
	//////////////////////////////////////////////////////////////
	//		PUT YOUR ICON HERE
	
	0x00, 0xF0, 0x0F, 0x00, 0x00, 0xFE, 0x7F, 0x00, 
	0x80, 0x9F, 0xF9, 0x00, 0xC0, 0x83, 0xC1, 0x03, 
	0xE0, 0x01, 0x80, 0x07, 0x70, 0x00, 0x00, 0x0E, 
	0x38, 0x80, 0x01, 0x1C, 0x18, 0x80, 0x01, 0x38, 
	0x1C, 0x80, 0x01, 0x38, 0x0E, 0x80, 0x01, 0x70, 
	0x06, 0x80, 0x01, 0x60, 0x06, 0x80, 0x01, 0x60, 
	0x07, 0x80, 0x01, 0xE0, 0x03, 0x80, 0x01, 0xC0, 
	0x03, 0x80, 0x01, 0xC0, 0x0F, 0xE0, 0x7F, 0xF0, 
	0x0F, 0xE0, 0x7F, 0xF0, 0x03, 0x80, 0x01, 0xC0, 
	0x03, 0x80, 0x01, 0xC0, 0x07, 0x00, 0x00, 0xE0, 
	0x06, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x60, 
	0x0E, 0x00, 0x00, 0x70, 0x1C, 0x00, 0x00, 0x38, 
	0x1C, 0x00, 0x00, 0x18, 0x38, 0x00, 0x00, 0x1C, 
	0x70, 0x00, 0x00, 0x0E, 0xE0, 0x01, 0x80, 0x07, 
	0xC0, 0x83, 0xC1, 0x03, 0x00, 0x9F, 0xF9, 0x01, 
	0x00, 0xFE, 0x7F, 0x00, 0x00, 0xF0, 0x0F, 0x00, 

	//
	//////////////////////////////////////////////////////////////
};


/*




*/

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                                                                                         *
 *                                  >>>   IMPORTANT!   <<<                                 *
 *                  DO NOT FORGET TO ADD YOUR APP IN os_applications.ino                   *
 *                                                                                         *
 *                                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#define appNameClass    SampleGame         // App name without spaces
#define appName         "Sample game"         // App name with spaces (max 16)

class appNameClass: public Application{
    public:
        float player_y = 0;
        float player_x = 0;
        float player_v_y = 0;

        long delay_timer = 0;
        bool isGameOver = false;

        int block_y = 0;

        virtual void loop() override{
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                                >>>   MAIN APP LOOP   <<<                                *
            *                                                                                         *
            */

            //EVERY FRAME CODE
            //drawString("Sample game loop",0,10);

            //if (isPressStart_Select()){
                //os_switch_to_app(-1);
            //}
            
            if (isPressStart_Left()){
                os_switch_to_app(-1);
            }

            if (isGameOver) game_over_looop();
            else game_loop();

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };

        void new_game(){
            player_y = 0;
            player_v_y = 0;
            player_x = 0;

            delay_timer = 0;
            isGameOver = false;
        }

        void game_loop(){
            player_v_y += SCREEN_HEIGHT/30;
            
            if (isPressStart_Select()){
                player_v_y -= SCREEN_HEIGHT*2;
            }

            player_y += player_v_y * dtime/1000/2;
            player_x += 40*(float)dtime/1000;

            if (player_x>SCREEN_WIDTH*1.1 + 12){
                player_x = 0;  
                block_y = SCREEN_HEIGHT*2*(millis()%100)/3/100;
            }

            if (player_y<0){
                player_y = 0;
                player_v_y = 0;
            }

            if (player_y + 12>SCREEN_HEIGHT){
                gameOver();
            }

            // Check collision
            int playerx = SCREEN_WIDTH/6;
            int playerx1 = SCREEN_WIDTH/6 + 16;
            int playery = player_y;
            int playery1 = player_y + 12;

            int blockx = (int)(SCREEN_WIDTH - player_x);
            int blockx1 = ( (int)(SCREEN_WIDTH - player_x) ) + 12;
            int blocky = block_y;
            int blocky1 = block_y + SCREEN_HEIGHT/3;

            if (playerx < blockx1 && playerx1 > blockx && playery < blocky1 && playery1 > blocky){
                gameOver();
            }

            drawIcon(player,SCREEN_WIDTH/6,player_y, 16,12);

            drawLine(0, SCREEN_HEIGHT-1, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
            
            drawRect(  (int)(SCREEN_WIDTH - player_x) , block_y, ( (int)(SCREEN_WIDTH - player_x) ) + 12, block_y + SCREEN_HEIGHT/3, true); 
        }

        void gameOver(){
            player_y = 0; player_v_y = 0;

            delay_timer = millis();
            isGameOver = true;
        }

        void game_over_looop(){
          drawString_centered("GAME OVER",SCREEN_WIDTH/2,SCREEN_HEIGHT/2 - FONT_CHAR_HEIGHT - 2);

          if (abs( (int)(delay_timer-millis())) >3000){ isGameOver = false; new_game();}
          if (abs( (int)(delay_timer-millis()))>500 && isPressStart_Select()){ isGameOver = false; new_game();}
        }

        void setup(){
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                              >>>   APP SETUP ON START   <<<                             *
            *                                                                                         *
            */
            new_game();
            // ON START APP CODE

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

		const static byte icon[] PROGMEM;
        const static byte player[] PROGMEM; 

        appNameClass(){ // Constructor
            setup();
        };        

};

const byte appNameClass::icon[] PROGMEM = {
	//////////////////////////////////////////////////////////////
	//		PUT YOUR APP ICON HERE
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x80, 0x07, 
    0xE0, 0x01, 0x80, 0x07, 0xE0, 0x01, 0x80, 0x07, 
    0xE0, 0x01, 0x80, 0x07, 0xE0, 0x0F, 0xF0, 0x07, 
    0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 
    0x80, 0xFF, 0xFF, 0x01, 0xC0, 0xFF, 0xFF, 0x03, 
    0xE0, 0xFF, 0xFF, 0x07, 0xF0, 0xF7, 0xEF, 0x0F, 
    0xF8, 0xE3, 0xC7, 0x1F, 0xF8, 0xE3, 0xC7, 0x1F, 
    0xFF, 0xE3, 0xC7, 0xFF, 0xFF, 0xF7, 0xEF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xF3, 
    0xCF, 0xFF, 0xFF, 0xF3, 0xCF, 0xFF, 0xFF, 0xF3, 
    0xCF, 0x01, 0x80, 0xF3, 0xCF, 0x01, 0x80, 0xF3, 
    0xCF, 0x3F, 0xFC, 0xF3, 0x00, 0x3F, 0xFC, 0x00, 
    0x00, 0x3F, 0xFC, 0x00, 0x00, 0x3F, 0xFC, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//
	//////////////////////////////////////////////////////////////
};

const byte appNameClass::player[] PROGMEM  = { //16x12
    0b11000000, 0b00000111,
    0b00110000, 0b00001010,
    0b00001000, 0b00010001,
    0b00011110, 0b00101001,
    0b00100001, 0b00101001,
    0b01000001, 0b00100001,
    0b01000001, 0b01111110,
    0b00100010, 0b10000001,
    0b10011100, 0b01111110,
    0b00001000, 0b01000001,
    0b00010000, 0b00111110,
    0b11100000, 0b00000001,
    
}; void MainMenu::setup(){}

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
            drawString_centered("New app",SCREEN_WIDTH/2,10);

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
unsigned char delay_before_turnoff   = 6; 
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

#define appNameClass    SettingApp         // App name without spaces
#define appName         "Settings"         // App name with spaces (max 16)

class appNameClass: public Application{
    public:

        byte current_menu_position  = 0;
        byte current_menu           = 0;

        virtual void loop() override{
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                                >>>   MAIN APP LOOP   <<<                                *
            *                                                                                         *
            */

            //EVERY FRAME CODE
            switch(current_menu){
                case 0: drawSettingsMenu(); break;
                case 1: drawingSelectDeleayTurnOff(); break;
                case 2: drawSetTime(); break;
            }
            

            /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };

        #define drawSettingsElement_height                29
        #define drawSettingsElement_margin                2
        #define drawSettingsElement_margin_left           10
        #define drawSettingsElement_padding               3
        #define drawSettingsElement_padding_label_value   3

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
            
            if (isPressStart_Select())isActivated = !isActivated;

            if (!isActivated){
                if (isPressStart_Left()) activeElement--;
                if (isPressStart_Right()) activeElement++;

                if (activeElement>2||activeElement<0){
                    activeElement = 0;
                    current_menu = 0;
                }
            }else{
                //edit time
                if (isPressStart_Left()){
                    if (activeElement==2){
                        set_preset_second(os_clock_currentTime_seconds());
                    }else if (activeElement==1){
                        set_preset_minute(get_preset_minute() - 1);
                    }else if (activeElement==0){
                        set_preset_hour(get_preset_hour() - 1);
                    }
                }else if(isPressStart_Right()){
                    if (activeElement==2){
                        set_preset_second(os_clock_currentTime_seconds());
                    }else if (activeElement==1){
                        set_preset_minute(get_preset_minute() + 1);
                    }else if (activeElement==0){
                        set_preset_hour(get_preset_hour() + 1);
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
                        drawIcon( (const unsigned char *)getIcon(ICON_ARROW_UP), val1_x - 5, val_y_strike + 2, 8, 4);
                        break;
                    case 1: 
                        drawIcon( (const unsigned char *)getIcon(ICON_ARROW_UP), val2_x - 5, val_y_strike + 2, 8, 4);
                        break;
                    case 2: 
                        drawIcon( (const unsigned char *)getIcon(ICON_ARROW_UP), val3_x - 5, val_y_strike + 2, 8, 4);
                        break;
                }
            } 
            
            //draw_arror_select_dateTime(SCREEN_WIDTH/5, SCREEN_WIDTH/5, 3, SCREEN_HEIGHT*0.75 );

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

            drawString_centered(getDelayBeforTurnOff(), SCREEN_WIDTH/2, diagram_height + top_margin + diagram_padding*2);

            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_RIGHT), SCREEN_WIDTH-4, diagram_height + top_margin + diagram_padding*2, 4, 7); // Arrow right
            drawIcon( (const unsigned char *)getIcon(ICON_ARROW_LEFT), 0,                                  diagram_height + top_margin + diagram_padding*2, 4, 7); // Arrow left  
        }

        char * getDelayBeforTurnOff(){
            switch(delay_before_turnoff){
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
                default: return "Never";
            }
        }

        void drawSettingsMenu(){
            if (isPressStart_Left() && current_menu_position>0) current_menu_position--;
            if (isPressStart_Right() && current_menu_position<2) current_menu_position++;

            this->scroll_to_y = 1-current_menu_position * drawSettingsElement_height + drawSettingsElement_margin + drawSettingsElement_height/2;

            drawIcon( 
                this-> scroll_x + (const unsigned char *)getIcon(0x01), drawSettingsElement_margin_left/2 - 2, 
                SCREEN_HEIGHT/2-3,
                4, 
                7
            );

            char v1[3];
            char v2[3];
            char v3[3];

            char time_string[9];
            
            int_to_char(v1, os_clock_currentTime_hour(), true);
            int_to_char(v2, os_clock_currentTime_minutes(), true);
            int_to_char(v3, os_clock_currentTime_seconds(), true);

            sprintf(time_string, "%s:%s:%s", v1, v2, v3);

            drawSettingsElement("Sleep after",getDelayBeforTurnOff(),0);
            drawSettingsElement("Set time", time_string, 1);
            drawSettingsElement("Exit", "", 2);

            if (isPressStart_Select()){
                switch (current_menu_position){
                    case 2: os_switch_to_app(-1); break;
                    case 0: current_menu = 1; break;
                    case 1: current_menu = 2; break;
                }
                
            }
        }
      
        void drawSettingsElement(char *label, char *value, byte position){
          drawRect(this-> scroll_x + drawSettingsElement_margin_left, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_margin, this-> scroll_x + SCREEN_WIDTH - drawSettingsElement_margin, this-> scroll_y + position * drawSettingsElement_height - drawSettingsElement_margin + drawSettingsElement_height);
          drawString(label, this-> scroll_x + drawSettingsElement_margin_left + drawSettingsElement_padding, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_padding + drawSettingsElement_margin);
          drawString(value, this-> scroll_x + SCREEN_WIDTH - drawSettingsElement_margin - drawSettingsElement_padding - strlen(value)*FONT_CHAR_WIDTH, this-> scroll_y + position * drawSettingsElement_height + drawSettingsElement_padding + drawSettingsElement_margin + FONT_CHAR_HEIGHT + drawSettingsElement_padding_label_value);
        }
        
        void setup(){
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                              >>>   APP SETUP ON START   <<<                             *
            *                                                                                         *
            */

            // ON START APP CODE
            this->scroll_y = 1-current_menu_position * drawSettingsElement_height + drawSettingsElement_margin + drawSettingsElement_height/2;

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

const byte appNameClass::icon[] PROGMEM = { //128
	//////////////////////////////////////////////////////////////
	//		PUT YOUR ICON HERE
    0x00, 0x0C, 0x30, 0x00, 0x00, 0x1E, 0x78, 0x00, 
    0x00, 0x3F, 0xFC, 0x00, 0x00, 0x7F, 0xFE, 0x00, 
    0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 
    0x00, 0xFF, 0xFF, 0x00, 0x80, 0xFF, 0xFF, 0x01, 
    0xFE, 0x1F, 0xF8, 0x7F, 0xFF, 0x0F, 0xF0, 0xFF, 
    0xFF, 0x07, 0xE0, 0xFF, 0xFE, 0x03, 0xC0, 0x7F, 
    0xFC, 0x01, 0x80, 0x3F, 0xF8, 0x01, 0x80, 0x1F, 
    0xF0, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x0F, 
    0xF0, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x1F, 
    0xFC, 0x01, 0x80, 0x3F, 0xFE, 0x01, 0x80, 0x7F, 
    0xFF, 0x03, 0xC0, 0xFF, 0xFF, 0x07, 0xE0, 0xFF, 
    0xFF, 0x0F, 0xF0, 0xFF, 0xFE, 0x3F, 0xFC, 0x7F, 
    0x80, 0xFF, 0xFF, 0x01, 0x00, 0xFF, 0xFF, 0x00, 
    0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 
    0x00, 0x3F, 0xFC, 0x00, 0x00, 0x1F, 0xF8, 0x00, 
    0x00, 0x1E, 0x78, 0x00, 0x00, 0x0C, 0x30, 0x00, 
	//
	//////////////////////////////////////////////////////////////
};/* -- os_applications.ino -- */
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                          >>>   ADD YOUR APPLICATION HERE   <<<                          *
 *                                                                                         *
 */

    const byte applications_count = 4; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CHANGE THIS VALUE

    Application *getApp(byte i){
      
        if (i==0) return new ClockApp; 
        if (i==1) return new SettingApp;
        if (i==2) return new SampleGame;
        if (i==3) return new TestApp;
        // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ADD YOUR APP HERE
        else return new MainMenu;
    }

    const unsigned char * getAppParams(byte i, byte type){
        if(i==0){
            ClockApp *app; return ((*app).getParams(type));
        }else if(i==1){
            SettingApp *app; return ((*app).getParams(type));
        }else if(i==2){
            SampleGame *app; return ((*app).getParams(type));
        }else if(i==3){
            TestApp *app; return ((*app).getParams(type));
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
    return applications_count;
}void showFreeMemory(){}/* -- platform_x86.ino -- */
