
/*
    ############################################################################################
    #                                                                                          #
    #                                  ARDUINO MEGA SETTINGS                                   #
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


#define SCREEN_WIDTH            240     // Note: x-coordinates go wide
#define SCREEN_HEIGHT           320     // Note: y-coordinates go high

#define FONT_CHAR_WIDTH         6     // Font letter size width
#define FONT_CHAR_HEIGHT        8     // Font letter size height

#define useNativeMenu                   // Using default app_menu.ino

#define conf_arduinoMega2560_touch      // Name of Mconfiguration
#define isTouchScreen                   // Conf of controls

#define tabletView                       // View
#define tabletView_statusBarHeight 24

#define colorScreen                   
#define noAnimation                     // Caurse of framebuffer type
#define os_MAINMENU_APP_COUNT 5     //How much apps in menu

#define mainMenu_iconsInRow     3

#define mainMenu_scrollSize 16
#define mainMenu_icon_element_size ((SCREEN_WIDTH-1)/mainMenu_iconsInRow - mainMenu_scrollSize/mainMenu_iconsInRow)

#define appArea_margin_top tabletView_statusBarHeight

// Max ram for apllications runs from TFCard
#define MAX_RAM_SIZE_FOR_B_APPS 255 //in bytes
#define SDCARD_FILE_READ_BUFFER_SIZE 16 // Size of buffer for reading B files (16 bytes - works x2 faster thаn 1byte. Best choice for uno)

#define framebuffer_linearhash //Type of frame buffer

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
