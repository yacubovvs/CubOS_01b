/*
    ############################################################################################
    #                                                                                          #
    #                                 NODEMCU MINI PC SETTINGS                                 #
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
#define conf_esp8266_led128             // Name of Mconfiguration
#define platform_esp8266                // Platform

#define hasHardwareButtons              // Conf of controls with hardware btns 

//#define device_has_barometer
//#define device_has_accelerometer

// #####################################
// ##           POWER CONTROL           
#define device_has_power_manager
#define device_can_sleep

#define control_buttons_pins {D0, D4, D10, D3, D6, D9}
#define control_buttons_count 6
#define control_buttons_on_LOW_level


//#define isTouchScreen                 // Conf of controls

//#define tabletView                      // View
//#define tabletView_statusBarHeight 24   // Height of status bar at top of screen

//#define colorScreen                   // Screen is colored
//#define noAnimation                     // Caurse of framebuffer type
#define os_MAINMENU_APP_COUNT 7         // How much apps in menu

//#define mainMenu_iconsInRow 3           // Count of apps in row in tabview in mainMenu
//#define frame_selected_app_padding 10   // Padding of frame on hardware buttons navigate in menu

//#define mainMenu_scrollSize 16          // Size of scrollbar at right of screen
//#define mainMenu_icon_element_size ((SCREEN_WIDTH-1)/mainMenu_iconsInRow - mainMenu_scrollSize/mainMenu_iconsInRow)

//#define appArea_margin_top tabletView_statusBarHeight

// Max ram for apllications runs from TFCard
//#define MAX_RAM_SIZE_FOR_B_APPS 255     //in bytes

/*
    ###   #   ##    #   ## ##   ##      
    # #  # #  # #  # #  # # #  #        
    ###  ###  ##   ###  #   #   ##    #####     
    #    # #  # #  # #  #   #    #      
    #    # #  # #  # #  #   #  ##       
*/