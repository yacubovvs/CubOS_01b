#ifdef device_can_sleep
    boolean isInFullSleep = false;

    #ifdef platform_esp8266

        #include <ESP8266WiFi.h> 
        #include <Wire.h> 
        #define pin_wake_up1 12
        #define pin_wake_up1 13
        #define pin_wake_up1 14

        extern "C"
        {
            #include "gpio.h"
        }

        extern "C"
        {
            #include "user_interface.h"
        }

        /*
        void driver_powerManager_GoSleep(){

            wifi_station_disconnect();
            bool stopped;
            do {
                stopped = wifi_station_get_connect_status() == DHCP_STOPPED;
                if (!stopped){
                    delay(100);
                }
            } while (!stopped);

            wifi_set_opmode(NULL_MODE);
            wifi_set_sleep_type(MODEM_SLEEP_T);
            wifi_fpm_open();
            wifi_fpm_do_sleep(0xFFFFFFF);

        }*/

        // the loop function runs over and over again forever
        void driver_powerManager_GoSleep(uint16_t time) {

            wifi_set_opmode_current(NULL_MODE);
            wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
            wifi_fpm_open();
            wifi_fpm_set_wakeup_cb(wake_cb);
            
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U,3);

            for(byte i=0; i<control_buttons_amount; i++){
                const int btns_pins[] = control_buttons_pins;
                #ifdef control_buttons_on_LOW_level
                    gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_LOLEVEL);    
                #else
                    gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_LOLEVEL);    
                #endif
            }
            
            //gpio_pin_wakeup_enable(12, GPIO_PIN_INTR_HILEVEL);

            wifi_fpm_set_wakeup_cb(wake_cb); 
            
            wifi_fpm_do_sleep(time*1000);
            delay (time);

        }

        void wake_cb() {
            Serial.println("wakeup");
            wifi_fpm_close();
            WiFi.forceSleepBegin();

            if(isInFullSleep){
                isInFullSleep = false;
                //#ifdef display_i2c_ssd1306
                    display_driver_power_on();
                //#endif
            }

            wifi_set_sleep_type(LIGHT_SLEEP_T);
            WiFi.forceSleepBegin(); 
        }
    #endif
#endif

#ifdef device_can_sleep
    void device_powermanager_sleep_loop(){
        #ifdef platform_esp8266
            while( abs(millis() - os_control_get_last_user_avtivity())>5000 ){
              //os_control_check_last_user_avtivity
              if(!isInFullSleep){
                  isInFullSleep = true;
                  //#ifdef display_i2c_ssd1306
                    display_driver_power_off();
                  //#endif
              }
              os_control_loop();
              driver_powerManager_GoSleep(100);
            }
        #endif

        #ifdef conf_atm328_nokia_watch
            if(abs(millis() - os_control_get_last_user_avtivity())>5000 ){
                
            }
        #endif
    }
#endif

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

    #ifdef device_can_sleep
        #ifdef platform_esp8266
            wifi_set_sleep_type(LIGHT_SLEEP_T);
            WiFi.forceSleepBegin(); 
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