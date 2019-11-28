/*
    ############################################################################################
    #                                                                                          #
    #                                     WATCH4  SETTINGS                                     #
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

#define SCREEN_WIDTH            128     // Note: x-coordinates go wide
#define SCREEN_HEIGHT           64     // Note: y-coordinates go high

#define FONT_CHAR_WIDTH         6     // Font letter size width
#define FONT_CHAR_HEIGHT        8     // Font letter size height

#define useNativeMenu                   // Using default app_menu.ino
#define conf_atm64_watch4         // Name of Mconfiguration
#define platform_avr                    // Platform

#define hasHardwareButtons              // Conf of controls with hardware btns 
#define control_buttons_count 4
#define control_buttons_pins {48, 47, 46, 45}
#define control_buttons_amount 4
#define control_has_backbtn

#define control_buttons_on_side
//#define control_buttons_on_LOW_level

#define device_has_barometer
#define barometer_power_pin 3

#define device_has_accelerometer
#define accelerometer_power_pin 4

#define device_has_magnitometer
#define magnitometer_power_pin 14

#define device_has_bluetooth
#define device_bluetooth_serial Serial1
#define device_bluetooth_power_pin 27
#define device_bluetooth_stat_pin 23

#define display_invert_y
#define display_power_pin 26
// #####################################
// ##           POWER CONTROL           
#define device_has_power_manager
#define device_can_sleep

#define device_has_backlight_control
#define backlight_init 10
#define backlight_fade_init 2

#define device_can_cpu_prescale
//#define millis() (millis()*2)


//#define isTouchScreen                 // Conf of controls

//#define tabletView                      // View
//#define tabletView_statusBarHeight 24   // Height of status bar at top of screen

//#define colorScreen                   // Screen is colored
//#define noAnimation                     // Caurse of framebuffer type
#define os_MAINMENU_APP_COUNT 9         // How much apps in menu

//#define mainMenu_iconsInRow 3           // Count of apps in row in tabview in mainMenu
//#define frame_selected_app_padding 10   // Padding of frame on hardware buttons navigate in menu

//#define mainMenu_scrollSize 16          // Size of scrollbar at right of screen
//#define mainMenu_icon_element_size ((SCREEN_WIDTH-1)/mainMenu_iconsInRow - mainMenu_scrollSize/mainMenu_iconsInRow)

//#define appArea_margin_top tabletView_statusBarHeight

// Max ram for apllications runs from TFCard
//#define MAX_RAM_SIZE_FOR_B_APPS 255     //in bytes

#define draw_statusBar

#define device_has_vibro
#define device_vibro_pin 22

/*
    ###   #   ##    #   ## ##   ##      
    # #  # #  # #  # #  # # #  #        
    ###  ###  ##   ###  #   #   ##    #####     
    #    # #  # #  # #  #   #    #      
    #    # #  # #  # #  #   #  ##       
*/#define SCREEN_CENTER_X (SCREEN_WIDTH/2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT/2)

#ifdef platform_avr
  #ifndef conf_atm64_watch4
	  #include "libs_h/CyberLib/CyberLib.h"
  #endif

  #include "libs_h/avr/power.h"
#endif

unsigned int dtime = 0;

/*
**************************************
*                                    *
*            APPLICATIONS +          *
*                                    *
**************************************
*/

/*
 * # # # # # # # # # # # #
 * #        ICONS        #
 * # # # # # # # # # # # #
*/

#define ICON_ARROW_RIGHT 	    	0x01
#define ICON_ARROW_LEFT 	    	0x02
#define ICON_ARROW_UP 		    	0x03
#define ICON_ARROW_DOWN 	    	0x04
#define BATTERY_UNKNOWN		    	0x05
#define BATTERY_100			      	0x06
#define BATTERY_90			      	0x07
#define BATTERY_80			      	0x08
#define BATTERY_70			      	0x09
#define BATTERY_60			      	0x0A
#define BATTERY_50			      	0x0B
#define BATTERY_40			      	0x0C
#define BATTERY_30			      	0x0D
#define BATTERY_20			   	    0x0E
#define BATTERY_10			   		0x0F
#define BATTERY_0			        0x10
#define WIFI_CONNECTED		    	0x11
#define WIFI_NOTCONNECTED	    	0x12
#define WI_FI_IMG_OFF		      	0x13
#define BT_CONNECTED		      	0x14
#define BT_NOTCONNECTED		    	0x15
#define BT_OFF				        0x16

#define SETTINGS_BRIGHTNESS   		0x17
#define SETTINGS_FADEBRIGHTNESS   	0x18
#define SETTINGS_FADEIN   			0x19
#define SETTINGS_SCREENSAVERIN   	0x1A
#define SETTINGS_LOCKSCREENIN   	0x1B
#define SETTINGS_SCREEN				0x1C
#define SETTINGS_BACK				0x1D
#define SETTINGS_TIME				0x1E

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
					scroll_x = scroll_to_x;
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

					//Serial.println(scroll_to_y);
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
		set_prevent_displayoff_flag(false);
		set_prevent_backlightlow_flag(false);
		
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

#ifdef platform_avr
	#include <avr/sleep.h>
#endif

void setup(){

  setup_redifined_millis();

  #ifdef debug
	Serial.begin(115200);
  #endif

  #ifdef platform_avr
	//set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	//sleep_enable();

	//MCUCR = bit (BODS) | bit (BODSE);
	//MCUCR = bit (BODS);
	//sleep_cpu();
  #endif

  #ifdef device_has_power_manager
	power_manager_setup();
  #endif

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

	#ifdef device_has_barometer
		//barometer_setup();
	#endif

	#ifndef device_has_power_manager
		#ifdef device_has_accelerometer
			accelerometer_setup();
		#endif
	#else
		// if device_has_power_manager define - start accelerometer then need
	#endif

	#ifdef device_has_vibro
		driver_vibro_setup();
	#endif

	#ifdef device_has_magnitometer
		driver_magnitometer_setup();
	#endif

}

void loop(){
	dtime = os_clock_update();
	
	clearscreen_displayDriver();
	#ifdef tabletView
    	if (currentApp->showStatusBar) os_draw_statusbar();
	#endif
	os_control_loop(); // Check buttons

	#ifndef do_Not_use_native_apps
		currentApp->loop_app();
	#else
		no_native_apps_LOOP();
	#endif

	/*
	
	if(digitalRead(48)){
		drawString("1",0,0);
	}
	if(digitalRead(47)){
		drawString("2",10,0);
	}
	if(digitalRead(46)){
		drawString("3",20,0);
	}
	if(digitalRead(45)){
		drawString("4",30,0);
	}
	
	*/
	

	////////////////////////////////////////////////////////////////////
	//  Debug string data
      	
		#ifdef colorScreen
			setDrawColor_background();
			drawRect(0,310, 30, 320, true);
		#endif  
      	//showFreeMemory(); // show free memory
      	//drawDebugString(dtime, 0); // show time needed for 1 loop
      	//drawDebugString(1000/dtime, 10); // FPS
      	//drawDebugString(_millis()/1000, 55); // Timer (if you want to know is os freezing)

		#ifdef colorScreen
			setDrawColor_contrast();
		#endif  
  	//
  	////////////////////////////////////////////////////////////////////

	#ifdef device_can_sleep	
    	device_powermanager_sleep_loop();
	#endif

  	updatescreen_displayDriver();
}