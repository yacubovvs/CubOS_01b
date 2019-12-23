

//////////////////////////////////////////////////////////////
// SETTING TIME AND DATE

unsigned int preset_day = 1; // 0 - 65534

char preset_hour = 0;
char preset_minute = 0;
char preset_second = 0;

//////////////////////////////////////////////////////////////
// HARDWARE CLOCK

unsigned long os_clock_time = 0;

unsigned int os_clock_update(){

  if (os_clock_time>_millis()){
    // millis was reseted
    os_clock_time = _millis();
    return 0;
  }

  //drawDebugString( os_clock_currentTime_hour(), 0);
  //drawDebugString( os_clock_currentTime_minutes(), 10);
  //drawDebugString( os_clock_currentTime_seconds(), 20);
  
  int dt = _millis() - os_clock_time;
  os_clock_time = _millis();
  return dt;
}

//////////////////////////////////////////////////////////////
// GETTING TIME 

char* os_clock_get_currentTime_String(){
  return "";
}


bool os_clock_currentTime_hour_isam(){
  return false;
  //return app_settings_isampm();
}

byte os_clock_currentTime_hour(){
  byte hour = (preset_hour + ((_millis()/1000 + preset_second)/60 + preset_minute)/60)%24;
  //byte hour = (preset_hour + (_millis()/1000)/60/60)%24;
  if (os_clock_currentTime_hour_isam() && hour>12) return hour%12;
  else return hour;
}

byte os_clock_currentTime_minutes(){
  return (preset_minute + (_millis()/1000 + preset_second)/60)%60;
  //return (preset_minute + _millis()/1000/60)%60;
}

byte os_clock_currentTime_seconds(){
  return (preset_second + _millis()/1000)%60;
}

void set_preset_hour(char val){
  preset_hour = val;
  if (preset_hour<0) preset_hour += 24;
  preset_hour = preset_hour%24;
}

void set_preset_minute(char val){
  preset_minute = val;
  if (preset_minute<0) preset_minute += 60;
  preset_minute = preset_minute%60;
}

void set_preset_second(char val){
  preset_second += (60-val);
  preset_second = preset_second%60;
}

char get_preset_hour(){return preset_hour;}
char get_preset_minute(){return preset_minute;}
char get_preset_second(){return preset_second;}

/*
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    #                                                                   #
    #                    TIMER FOR PRESCALERINF FREQ                    #
    #                                                                   #
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
*/

#ifdef conf_atm64_watch4
  unsigned long _millis_dif = 0;

  unsigned long _millis(){
    //return millis();
    return millis() + _millis_dif;
  }

  void add_miliss_dif(int dif){
    _millis_dif += dif;
  }

  #ifdef conf_atm64_watch4
    byte timer25_of_timer2 = 0;
    unsigned int timer1000_of_timer2 = 0;
  #endif

  ISR(TIMER2_OVF_vect)
  {
    // Using when clock_div_128
    _millis_dif += 33;

    #ifdef conf_atm64_watch4
      if(timer25_of_timer2==25){
        timer25_of_timer2=0;
        _millis_dif -= 1;
      }

      if(timer1000_of_timer2%10==0){
        _millis_dif -= 1;
        if(timer1000_of_timer2%100==0){
          _millis_dif -= 9;
          if(timer1000_of_timer2==1000){
            timer1000_of_timer2=0;
            _millis_dif -= 7;
          }
        }
      }
      
      
      timer25_of_timer2++;
      timer1000_of_timer2++;
    #endif  
  }


  void setup_redifined_millis(){
    pinMode(41, OUTPUT);
  }


  byte TCCR2_old;
  byte TCNT0_old;
  byte TIMSK_old;

  void sleep_millis_timer_on(){
    cli();
    
    TCCR2_old = TCCR2;
    TCNT0_old = TCNT0;
    TIMSK_old = TIMSK;
    
    TCCR2 = 0x02;
    TCNT0 = 0xB8;
    TIMSK = (1<<TOIE2);
    sei();
  }

  void sleep_millis_timer_off(){
    cli();
    
    TCCR2 = TCCR2_old;
    TCNT0 = TCNT0_old;
    TIMSK = TIMSK_old;
    
    sei();
  }
#else
  //unsigned long _millis_dif = 0;

  unsigned long _millis(){
    //return millis();
    return millis();// + _millis_dif;
  }
#endif