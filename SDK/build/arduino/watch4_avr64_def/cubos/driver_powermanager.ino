#ifdef platform_esp8266

  long timeInsleep = 0;

  long get_timeInsleep(){
    return timeInsleep;
  }

#endif

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

            /*
            wifi_station_disconnect();
            wifi_set_opmode_current(NULL_MODE);
            wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);

            for(byte i=0; i<control_buttons_count; i++){
                const int btns_pins[] = control_buttons_pins;
                #ifdef control_buttons_on_LOW_level
                    gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_LOLEVEL);    
                #else
                    gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_HILEVEL);    
                #endif
            }

            wifi_fpm_open();

            delay(100);
            wifi_fpm_set_wakeup_cb(wake_cb);
            wifi_fpm_do_sleep(150*100);
            delay(100);

            isInFullSleep = true;
          / */

            wifi_set_opmode_current(NULL_MODE);
            wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
            wifi_fpm_open();
            //WiFi.forceSleepBegin();
            //wifi_fpm_set_wakeup_cb(wake_cb);

            /*
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U,0);

            for(byte i=0; i<control_buttons_count; i++){
                const int btns_pins[] = control_buttons_pins;
                #ifdef control_buttons_on_LOW_level
                    gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_LOLEVEL);    
                #else
                    gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_HILEVEL);    
                #endif
            }*/

            //gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_LOLEVEL);    

            //ESP.wdtEnable(150);
            //gpio_pin_wakeup_enable(16, GPIO_PIN_INTR_HILEVEL);
            
            
            //gpio_pin_wakeup_enable(12, GPIO_PIN_INTR_HILEVEL);

            wifi_fpm_set_wakeup_cb(wake_cb); 
            
            //ESP.sleep_enable_timer_wakeup(1500);
            //esp_sleep_enable_timer_wakeup(1500);
            wifi_fpm_do_sleep(time*1000);
            delay (time-10);
            //ESP.node_set_cpu_freq(80);
            
            //isInFullSleep = false;
            #ifdef debug 
              Serial.println("Go to sleep");
              Serial.println(millis());
            #endif

            wifi_fpm_do_wakeup();

            // */

        }

        void wake_cb() {
          wifi_fpm_close();
          //wifi_set_opmode(STATION_MODE);
          display_driver_power_on();

          #ifdef debug 
            Serial.println("wakeup");
          #endif

          isInFullSleep = false;
          
            
          /*
            #ifdef debug 
              Serial.println("wakeup");
            #endif
            wifi_fpm_close();

            /*
            WiFi.forceSleepBegin();

            if(isInFullSleep){
                isInFullSleep = false;
                //#ifdef display_i2c_ssd1306
                    display_driver_power_on();
                //#endif
            }

            wifi_set_sleep_type(LIGHT_SLEEP_T);
            WiFi.forceSleepBegin(); 
            * /

            display_driver_power_on();
            //WiFi.forceSleep(); 
          */
        }
    #endif
#endif

#ifdef device_can_sleep
    void device_powermanager_sleep_loop(){
        #ifdef platform_esp8266
          if (abs(millis() - os_control_get_last_user_avtivity())>5000){  
            while( abs(millis() - os_control_get_last_user_avtivity())>5000 ){
              //delay(200);
              //wifi_fpm_do_sleep(100);
              //delay(50);
              //os_control_check_last_user_avtivity
              if(!isInFullSleep){
                  isInFullSleep = true;
                  //#ifdef display_i2c_ssd1306
                    display_driver_power_off();
                  //#endif
              }
              //os_control_loop();
              os_control_check_last_user_avtivity();

              #define sleeptime 200
              //if (abs(millis() - os_control_get_last_user_avtivity())>5000){ 
                driver_powerManager_GoSleep(sleeptime);
                
              //}
              //timeInsleep += sleeptime;
              #ifdef debug 
                Serial.println("While cycle");
              #endif
            }

            #ifdef debug 
              Serial.println("Cycle finished");
            #endif

            

            wake_cb();   
          }
            
        #endif

        #ifdef conf_atm328_nokia_watch
            if(abs(millis() - os_control_get_last_user_avtivity())>get_delay_before_turnoffBackLight()*1000 && os_control_get_last_user_avtivity()!=-1 ){
                #ifdef device_has_backlight_control
                    power_manager_set_backlight_strength(0);
                #endif
            }else{
                #ifdef device_has_backlight_control
                    power_manager_set_backlight_strength(get_backlight_light());
                #endif
            }
        #endif
    }
#endif

void power_manager_setup(){
    //Buttins power
    //pinMode(0, OUTPUT);
    //digitalWrite(0, 1);

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

            wifi_station_disconnect();
            wifi_set_opmode_current(NULL_MODE);
            wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);

            /*
            for(byte i=0; i<control_buttons_count; i++){
                const int btns_pins[] = control_buttons_pins;
                #ifdef control_buttons_on_LOW_level
                    gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_LOLEVEL);    
                #else
                    gpio_pin_wakeup_enable(btns_pins[i], GPIO_PIN_INTR_HILEVEL);    
                #endif
            }*/

            wifi_fpm_open();
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
        //accelerometer_wake();
    }

    void power_manager_end_accelerometer(){
      //accelerometer_sleep();
      digitalWrite(1, 0);
    }
#endif
