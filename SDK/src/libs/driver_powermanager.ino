void power_manager_setup(){
    //Buttins power
    pinMode(0, OUTPUT);
    digitalWrite(0, 1);

    #ifdef device_has_accelerometer
        pinMode(1, OUTPUT);
        digitalWrite(1, 1);
    #endif

    #ifdef device_has_backlight_control
        pinMode(10, OUTPUT);
        #ifdef backlight_init
            power_manager_set_backlight_strength(backlight_init);
        #endif
    #endif    
    
}

#ifdef device_has_backlight_control
    void power_manager_set_backlight_strength(byte backlight_strength){
        analogWrite(10, 255 - backlight_strength);
    }
#endif

#ifdef device_has_accelerometer
    void power_manager_start_accelerometer(){
        digitalWrite(1, 1);
        delay(25); //need wait for reseting accelerometer
        accelerometer_wake();
    }

    void power_manager_end_accelerometer(){
      accelerometer_sleep();
      digitalWrite(1, 0);
    }
#endif