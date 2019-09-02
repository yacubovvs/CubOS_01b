#ifdef platform_esp8266
#endif

#ifdef platform_m5stack
#endif

byte driver_wifi_isPowerOn(){
    return false;
}

byte driver_wifi_isConnected(){
    return false;
}
