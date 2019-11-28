#ifdef platform_esp8266

  long timeInsleep = 0;

  long get_timeInsleep(){
    return timeInsleep;
  }

#endif

byte powermanager_status = 0;
  /*
    STATUS on 1 bit by position:
      0 - sleep
      1 - backlight low
      2 - display off
      3 - prevent backlight low
      4 - prevent display off
  */

#define SET_SLEEP_FLAG_ON()   set_bit_to_byte(powermanager_status, 0, 1)
#define SET_SLEEP_FLAG_OFF()  set_bit_to_byte(powermanager_status, 0, 0)
#define GET_SLEEP_FLAG()      get_bit_from_byte(powermanager_status, 0)

#define SET_BACKLIGHTLOW_FLAG_ON()   set_bit_to_byte(powermanager_status, 1, 1)
#define SET_BACKLIGHTLOW_FLAG_OFF()  set_bit_to_byte(powermanager_status, 1, 0)
#define GET_BACKLIGHTLOW_FLAG()      get_bit_from_byte(powermanager_status, 1)

#define SET_DISPLAYOFF_FLAG_ON()   set_bit_to_byte(powermanager_status, 2, 1)
#define SET_DISPLAYOFF_FLAG_OFF()  set_bit_to_byte(powermanager_status, 2, 0)
#define GET_DISPLAYOFF_FLAG()      get_bit_from_byte(powermanager_status, 2)

#define SET_PREVENT_BACKLIGHTLOW_FLAG_ON()   set_bit_to_byte(powermanager_status, 3, 1)
#define SET_PREVENT_BACKLIGHTLOW_FLAG_OFF()  set_bit_to_byte(powermanager_status, 3, 0)
#define GET_PREVENT_BACKLIGHTLOW_FLAG()      get_bit_from_byte(powermanager_status, 3)

#define SET_PREVENT_DISPLAYOFF_FLAG_ON()   set_bit_to_byte(powermanager_status, 4, 1)
#define SET_PREVENT_DISPLAYOFF_FLAG_OFF()  set_bit_to_byte(powermanager_status, 4, 0)
#define GET_PREVENT_DISPLAYOFF_FLAG()      get_bit_from_byte(powermanager_status, 4)

//For using in Apps
void set_prevent_backlightlow_flag(boolean flag){
    if(flag) SET_PREVENT_BACKLIGHTLOW_FLAG_ON();
    else SET_PREVENT_BACKLIGHTLOW_FLAG_OFF();
}

//For using in Apps
void set_prevent_displayoff_flag(boolean flag){
    if(flag) SET_PREVENT_DISPLAYOFF_FLAG_ON();
    else SET_PREVENT_DISPLAYOFF_FLAG_OFF();
}

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

        void driver_powerManager_GoSleep(uint16_t time) {

            wifi_set_opmode_current(NULL_MODE);
            wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
            wifi_fpm_open();

            wifi_fpm_set_wakeup_cb(wake_cb); 
            wifi_fpm_do_sleep(time*1000);
            delay (time-10);

            #ifdef debug 
              Serial.println("Go to sleep");
              Serial.println(_millis());
            #endif

            wifi_fpm_do_wakeup();

        }

        void wake_cb() {
          wifi_fpm_close();
          display_driver_power_on();

          #ifdef debug 
            Serial.println("wakeup");
          #endif

          isInFullSleep = false;
          
        }
    #endif

    void device_powermanager_sleep_loop(){
        #ifdef platform_esp8266
          if (abs(_millis() - os_control_get_last_user_avtivity())>5000){  
            while( abs(_millis() - os_control_get_last_user_avtivity())>5000 ){

              if(!isInFullSleep){
                  isInFullSleep = true;
                    display_driver_power_off();
              }
              //os_control_loop();
              os_control_check_last_user_avtivity();

              #define sleeptime 200
              driver_powerManager_GoSleep(sleeptime);
                
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
            //Back light of NOKA5110 Screen
            if(abs(_millis() - os_control_get_last_user_avtivity())>get_delay_before_turnoffBackLight()*1000 && os_control_get_last_user_avtivity()!=-1 ){
                #ifdef device_has_backlight_control
                    power_manager_set_backlight_strength(0);
                #endif
            }else{
                #ifdef device_has_backlight_control
                    power_manager_set_backlight_strength(get_backlight_light());
                #endif
            }
      
        #elif defined(conf_atm64_watch4)

            //Display off of SH1106 Screen
            if(abs(_millis() - os_control_get_last_user_avtivity())>get_delay_before_turnoff()*1000 && !GET_PREVENT_DISPLAYOFF_FLAG() && os_control_get_last_user_avtivity()!=-1 ){
                #ifdef device_has_backlight_control
                    if(!GET_DISPLAYOFF_FLAG()){
                        display_driver_power_off();
                        SET_DISPLAYOFF_FLAG_ON();
                        powerManager_goToSleep();
                    }
                #endif
            }else{
                #ifdef device_has_backlight_control
                    if(GET_DISPLAYOFF_FLAG()){
                        display_driver_power_on();
                        SET_DISPLAYOFF_FLAG_OFF();
                        set_cpu_prescale(clock_div_1);
                    }
                    
                #endif
            }
            
            //Back light of SH1106 Screen
            if(abs(_millis() - os_control_get_last_user_avtivity())>get_delay_before_turnoffBackLight()*1000 && !GET_PREVENT_BACKLIGHTLOW_FLAG() && os_control_get_last_user_avtivity()!=-1 ){
                #ifdef device_has_backlight_control
                    if(!GET_BACKLIGHTLOW_FLAG()){
                        set_brightness(get_backlight_fade_light());
                        SET_BACKLIGHTLOW_FLAG_ON();
                    }
                #endif
            }else{
                #ifdef device_has_backlight_control
                    if(GET_BACKLIGHTLOW_FLAG()){
                        set_brightness(get_backlight_light());
                        SET_BACKLIGHTLOW_FLAG_OFF();
                    }
                    
                #endif
            }

        #endif
    }
#endif

#ifdef conf_atm64_watch4
  void powerManager_goToSleep(){
    // Action on going sleep
    //clock_prescale_set(clock_div_16);
    SET_SLEEP_FLAG_ON();
    sleep_millis_timer_on();
    set_cpu_prescale(clock_div_128);
    while(1){
      if(powerManager_inSleepSheduler()==1) break;
      //update_millis();
      //delay(250);
    }

    //Disable new buttons press
    os_control_loop();
    
    powerManager_wakeUp();
  }

  bool powerManager_inSleepSheduler(){
    //Loop action on sleep 
    // return 1 for wake up
    // return 0 for sleeping

    os_control_check_last_user_avtivity();
    if(abs(_millis() - os_control_get_last_user_avtivity())>get_delay_before_turnoff()*1000 && os_control_get_last_user_avtivity()!=-1 ){
      //os_control_reset_last_user_avtivity();
      
      delay(5);
      //if(random(10)==5) os_control_reset_debug_last_user_avtivity();
    }else{
      return 1;  
    }    
    
    return 0;
  }

  void powerManager_wakeUp(){    
    clock_prescale_set(clock_div_1);
    sleep_millis_timer_off();

    add_miliss_dif(-38); // Исправляем погрешность
    SET_SLEEP_FLAG_OFF();
  }
  
#endif

void power_manager_setup(){

    powermanager_iic_power_init();
    powermanager_iic_power(true);

    powermanager_bluetooth_power_init();
    powermanager_bluetooth_power(false);

    /*
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
    */ 

    #ifdef device_can_sleep
        #ifdef platform_esp8266
            wifi_set_sleep_type(LIGHT_SLEEP_T);
            WiFi.forceSleepBegin(); 

            wifi_station_disconnect();
            wifi_set_opmode_current(NULL_MODE);
            wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);

            wifi_fpm_open();
        #endif
    #endif
        
}

void powermanager_iic_power_init(){
    // IIC MODULES POWER
    #ifdef display_power_pin
        pinMode(    display_power_pin,              OUTPUT); // Display
    #endif

    #ifdef barometer_power_pin
        pinMode(    barometer_power_pin,            OUTPUT); // Barometer
    #endif

    #ifdef accelerometer_power_pin
        pinMode(    accelerometer_power_pin,        OUTPUT); // Accelerometer
    #endif

    #ifdef magnitometer_power_pin
        pinMode(    magnitometer_power_pin,         OUTPUT); // Magnitometer    
    #endif

}


void powermanager_iic_power(boolean on){
    // IIC MODULES POWER
    #ifdef display_power_pin
        digitalWrite(   display_power_pin,              on); // Display
    #endif

    #ifdef barometer_power_pin
        digitalWrite(   barometer_power_pin,            on); // Barometer
    #endif

    #ifdef accelerometer_power_pin
        digitalWrite(   accelerometer_power_pin,        on); // Accelerometer
    #endif

    #ifdef magnitometer_power_pin
        digitalWrite(   magnitometer_power_pin,         on); // Magnitometer
    #endif

}

void powermanager_bluetooth_power_init(){

    #ifndef device_bluetooth_serial
        #define device_bluetooth_serial Serial
    #endif

    #ifdef device_bluetooth_power_pin
        pinMode(    device_bluetooth_power_pin,     OUTPUT); // Bluetooth
    #endif
}


void powermanager_bluetooth_power(boolean on){
    #ifdef device_bluetooth_power_pin
        digitalWrite(   device_bluetooth_power_pin,     on); // Bluetooth
    #endif

    if(on){
        device_bluetooth_serial.begin(9600);
    }else{
        device_bluetooth_serial.end();
    }
}

#ifdef device_has_backlight_control
    void power_manager_set_backlight_strength(byte backlight_strength){
        analogWrite(10, 255 - backlight_strength);
    }
#endif

#ifdef device_has_accelerometer
    void power_manager_start_accelerometer(){
        //digitalWrite(1, 1);
        delay(25); //need wait for reseting accelerometer
        accelerometer_wake();
    }

    void power_manager_end_accelerometer(){
      accelerometer_sleep();
      //digitalWrite(1, 0);
    }
#endif

bool powerManager_isRequest_to_screenSaver(){
    return (abs(_millis() - os_control_get_last_user_avtivity())>get_delay_before_ScreenSaver()*1000 && os_control_get_last_user_avtivity()!=-1 );
}