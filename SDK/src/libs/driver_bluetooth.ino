#ifdef platform_esp8266
#endif

#ifdef platform_m5stack
#endif

byte driver_bt_isPowerOn(){
    return false;
}

byte driver_bt_isConnected(){
    return false;
}