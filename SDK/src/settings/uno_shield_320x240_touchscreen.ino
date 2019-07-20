
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

