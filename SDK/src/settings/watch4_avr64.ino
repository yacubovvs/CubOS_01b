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
#define control_has_backbtn

#define control_buttons_on_side
//#define control_buttons_on_LOW_level

#define device_has_barometer
#define barometer_power_pin 3

#define device_has_accelerometer
#define accelerometer_power_pin 4

#define device_has_magnitometer
#define magnitometer_power_pin 14
#define magnitometr_invert

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
*/