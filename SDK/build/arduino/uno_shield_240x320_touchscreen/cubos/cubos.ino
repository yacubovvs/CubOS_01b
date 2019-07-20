
/*
    ############################################################################################
    #                                                                                          #
    #                                   ARDUINO UNO SETTINGS                                   #
    #                                                                                          #
    ############################################################################################
*/

/*
    ###   #   ##    #   ## ##   ##      
    # #  # #  # #  # #  # # #  #        #
    ###  ###  ##   ###  #   #   ##    #####     
    #    # #  # #  # #  #   #    #      #
    #    # #  # #  # #  #   #  ##       
*/

/*
    UNO SHIELD 320x240 TOUCH SCREEN SETTINGS
*/

#define SCREEN_WIDTH            240     // Note: x-coordinates go wide
#define SCREEN_HEIGHT           320     // Note: y-coordinates go high

#define FONT_CHAR_WIDTH         6     // Font letter size width
#define FONT_CHAR_HEIGHT        8     // Font letter size height

#define do_Not_use_native_apps          // No application class
#define no_native_apps_SETUP    SDAppManager_setup      // Function will be use as setup if not using native apps
#define no_native_apps_LOOP     SDAppManager_loop       // Function will be use as loop if not using native apps

#define conf_uno_touch_shield                  // Name of Mconfiguration
#define isTouchScreen                   // Conf of controls

//#define tabletView                       // Tabel view (if not active view like smart watch)
//#define tabletView_statusBarHeight 24    // Height of status bar in tableView

#define colorScreen                   
#define noAnimation                     // Becaurse of framebuffer type

#define appArea_margin_top tabletView_statusBarHeight

// Max ram for apllications runs from TFCard
#define MAX_RAM_SIZE_FOR_B_APPS 256 //in bytes
#define SDCARD_FILE_READ_BUFFER_SIZE 16 // Size of buffer for reading B files (16 bytes - works x2 faster thаn 1byte. Best choice for uno)


#define BOOT_FUNC app_manager_boot_func     // if you want to start device not on main menu



/*

    ########################################################################
    #                                                                      #
    #               LINEAR DISPLAY HASH FRAMEBUFFER SETTINGS               #
    #                                                                      #
    ########################################################################
    Needs for ATMEGA328 (arduino uno, nano and etc) and ATMEGA2560 (arduino mega2560)
    with big touch displays if using linear hash framebuffer
*/

#define LINEARHASH_FRAMEBUFFER_PIXEL_SIZE 8
#define LINEARHASH_TYPE uint16_t


/*
    ###   #   ##    #   ## ##   ##      
    # #  # #  # #  # #  # # #  #        
    ###  ###  ##   ###  #   #   ##    #####     
    #    # #  # #  # #  #   #    #      
    #    # #  # #  # #  #   #  ##       
*/

#include "libs_h/CyberLib/CyberLib.h"

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
#ifndef do_Not_use_native_apps
	class Application{
		public:
		#ifdef tabletView
		boolean showStatusBar = false;
		#endif
		
			int scroll_x	      = 0;
			int scroll_y	      = 0;
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