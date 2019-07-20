//#define OS_MENU_COUNT_OF_APPLICATIONS 16

byte current_app = 0x00; // Splashscreen
unsigned int dtime = 0;

#define SCREEN_WIDTH            84     // Note: x-coordinates go wide
#define SCREEN_HEIGHT           48     // Note: y-coordinates go high

#define FONT_CHAR_WIDTH         6
#define FONT_CHAR_HEIGHT        8

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
	currentApp = new MainMenu(); // Start first app
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
}
