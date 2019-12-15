#define SCREEN_CENTER_X (SCREEN_WIDTH/2)
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
		#ifdef device_has_power_manager
			set_prevent_displayoff_flag(false);
			set_prevent_backlightlow_flag(false);
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

#ifdef platform_avr
	#include <avr/sleep.h>
#endif

void setup(){

  #ifdef conf_atm64_watch4
  	setup_redifined_millis();
  #endif

  #ifdef debug
	Serial.begin(115200);
  #endif

  #ifdef DeviceSerial
	#ifndef DeviceSerialSpeed
		#define DeviceSerialSpeed 9600
	#endif
	DeviceSerial.begin(DeviceSerialSpeed);
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