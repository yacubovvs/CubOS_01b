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

        //Background
        setDrawColor(0x06, 0x07, 0x10);
        drawRect(0, 0, SCREEN_WIDTH, tabletView_statusBarHeight, true);
        setDrawColor_contrast();
    
        // Time
        char v1[3];
        char v2[3];
        char time_string[6];
        int_to_char(v1, os_clock_currentTime_hour(), true);
        int_to_char(v2, os_clock_currentTime_minutes(), true);
        sprintf(time_string, "%s:%s", v1, v2);
        drawString(time_string, 8, (tabletView_statusBarHeight - FONT_CHAR_HEIGHT)/2-1);

        // Battery 
        drawIcon((const unsigned char *)getIcon(BATTERY_UNKNOWN), SCREEN_WIDTH - 32, 6);


        //FRAME
        drawRect(0, tabletView_statusBarHeight ,SCREEN_WIDTH-1, tabletView_statusBarHeight-2, true);
    #endif
}

// 1 bit array operations
void set_bit_to_byte(unsigned char &b, unsigned char position, bool value){ if (value) b|=1<<position; else b&=~(1<<position);}
bool get_bit_from_byte(unsigned char b, unsigned char position){return (b&1<<position);}

/*
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    #                                                                   #
    #                           READ RAW DATA                           #
    #                                                                   #
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
*/

// Also this func need for B apps
uint64_t bytes_to_value(byte byte0, byte byte1, byte byte2, byte byte3, byte byte4, byte byte5, byte byte6, byte byte7){
  return (byte7<<56)|(byte6<<48)|(byte5<<40)|(byte4<<32)|(byte3<<24)|(byte2<<16)|(byte1<<8)|byte0;
}

int readRawParam(const unsigned char* data, long &position){
    byte paramType = redRawChar(data, position);

    if (paramType==0x02){
      return (byte)redRawChar(data, position);
    }else if(paramType==0x03){
      return (unsigned int)bytes_to_value(redRawChar(data, position), redRawChar(data, position),0,0,0,0,0,0);
    }
}

long redRawChar(const unsigned char* data, long &position){
    unsigned char data_char = (char)pgm_read_word(&(data[position]));
    position ++;
    return data_char;
}   