/*
*************************************
*                                   *
*          BASIC FUNCTIONS          *
*                                   *
*************************************
*/

//const float pi = 3.141592;

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

void os_draw_statusbar(){
    #ifdef tabletView
        char v1[3];
        char v2[3];

        char time_string[6];
        
        int_to_char(v1, os_clock_currentTime_hour(), true);
        int_to_char(v2, os_clock_currentTime_minutes(), true);

        sprintf(time_string, "%s:%s", v1, v2);

        drawString(time_string, 8, (tabletView_statusBarHeight - FONT_CHAR_HEIGHT)/2-1);

        drawRect(0, tabletView_statusBarHeight ,SCREEN_WIDTH-1, tabletView_statusBarHeight-2, true);
    #endif
}