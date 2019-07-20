
#ifndef conf_m5stack
	#include "libs_h/CyberLib/CyberLib.h"
#endif

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
#define BATTERY_UNKNOWN		0x05

#define PARAM_TYPE_ICON 	0x01
#define PARAM_TYPE_NAME 	0x02


/////////////////////////////////////
// APPLICATION CLASS
#ifndef do_Not_use_native_apps
	class Application{
		public:
		#ifdef tabletView
		boolean showStatusBar = false;
		#endif
		
			int scroll_x	      	= 0;
			int scroll_y	      	= 0;
			int scroll_to_x			= 0;
			int scroll_to_y			= 0;
			virtual void loop() = 0;
			void loop_app(){
				loop();

				#ifdef noAnimation
					scroll_to_x = scroll_x;
					scroll_y = scroll_to_y;
				#else
					int dy=0; int dx =0;
		
					if(scroll_x!=scroll_to_x){
						dx = abs(scroll_x-scroll_to_x)/5 + 2;
						if(scroll_x>scroll_to_x) dx *= -1;
						scroll_x+=dx;
		
						if (abs(scroll_x-scroll_to_x)<abs(dx)) scroll_to_x=scroll_x;
					}
		
					if(scroll_y!=scroll_to_y){
						dy = abs(scroll_y-scroll_to_y)/5 + 2;
						if(scroll_y>scroll_to_y) dy *= -1;
						scroll_y+=dy;
				
						if (abs(scroll_y-scroll_to_y)<abs(dy)) scroll_y=scroll_to_y;
					}
				#endif
			}
			Application(){};
	};

	Application* currentApp;

#else
	int scroll_x	      = 0;
	int scroll_y	      = 0;
	int scroll_to_x		  = 0;
	int scroll_to_y		  = 0;

	void appsetup(){
		no_native_apps_SETUP();
	}

	void apploop(){

		#ifdef noAnimation
			scroll_to_x = scroll_x;
			scroll_y = scroll_to_y;
		#else
			int dy=0; int dx =0;

			if(scroll_x!=scroll_to_x){
				dx = abs(scroll_x-scroll_to_x)/5 + 2;
				if(scroll_x>scroll_to_x) dx *= -1;
				scroll_x+=dx;

				if (abs(scroll_x-scroll_to_x)<abs(dx)) scroll_to_x=scroll_x;
			}

			if(scroll_y!=scroll_to_y){
				dy = abs(scroll_y-scroll_to_y)/5 + 2;
				if(scroll_y>scroll_to_y) dy *= -1;
				scroll_y+=dy;
		
				if (abs(scroll_y-scroll_to_y)<abs(dy)) scroll_y=scroll_to_y;
			}
		#endif
		
		no_native_apps_LOOP();
	}
#endif
//
/////////////////////////////////////

#ifdef useNativeMenu
	Application *getApp(byte i);
	////////////////////////////////////

	void os_switch_to_app(byte app_numm){
		delete currentApp;
		#ifdef colorScreen
			// for correct drawing background
			driver_clearScreen();
		#endif
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

	#ifndef do_Not_use_native_apps
		#ifdef BOOT_FUNC
			BOOT_FUNC();
		#else
			app_mainmenu_start(); // Start first app
		#endif
	#else
		no_native_apps_SETUP();
	#endif

}

void loop(){
	clearscreen_displayDriver();

	#ifdef tabletView
    	if (currentApp->showStatusBar) os_draw_statusbar();
	#endif

	dtime = os_clock_update();
	
	os_control_loop(); // Check buttons

	#ifndef do_Not_use_native_apps
		currentApp->loop_app();
	#else
		no_native_apps_LOOP();
	#endif
	

////////////////////////////////////////////////////////////////////
  //  Debug string data
      setDrawColor_background();
      drawRect(0,310, 30, 320, true);
      setDrawColor_contrast();
      //showFreeMemory(); // show free memory
      drawDebugString(dtime, 310); // show time need for 1 loop
      //drawDebugString(1000/dtime, 10); // FPS
      //drawDebugString(millis()/1000, 55); // Timer (if you want to know is os freezing)
  //
  ////////////////////////////////////////////////////////////////////

  updatescreen_displayDriver();
}