

//////////////////////////////////////////////////////////////
// SETTING TIME AND DATE

unsigned int preset_day = 1; // 0 - 65534

byte preset_hour = 22;
byte preset_minute = 58;
byte preset_second = 45;

//////////////////////////////////////////////////////////////
// HARDWARE CLOCK

unsigned long os_clock_time = 0;

unsigned int os_clock_update(){

  if (os_clock_time>millis()){
    // millis was reseted
    os_clock_time = millis();
    return 0;
  }

  //drawDebugString( os_clock_currentTime_hour(), 0);
  //drawDebugString( os_clock_currentTime_minutes(), 10);
  //drawDebugString( os_clock_currentTime_seconds(), 20);
  
  int dt = millis() - os_clock_time;
  os_clock_time = millis();
  return dt;
}

//////////////////////////////////////////////////////////////
// GETTING TIME 

char* os_clock_get_currentTime_String(){
  return "12:37";
}


bool os_clock_currentTime_hour_isam(){
  return app_settings_isampm();
}

byte os_clock_currentTime_hour(){
  byte hour = (preset_hour + ((millis()/1000 + preset_second)/60 + preset_minute)/60)%24;
  if (os_clock_currentTime_hour_isam() && hour>12) return hour%12;
  else return hour;
}

byte os_clock_currentTime_minutes(){
  return (preset_minute + (millis()/1000 + preset_second)/60)%60;
}

byte os_clock_currentTime_seconds(){
  return (preset_second + millis()/1000)%60;
}



//////////////////////////////////////////////////////////////
// GETTING DATE 

char* os_clock_get_currentDate_String(){
  return "10 Jan 2019";
}


byte os_clock_currentDate_day(){
  return 8;
}

byte os_clock_currentDate_month(){
  return 0;
}

byte os_clock_currentDate_year(){
  return 0;
}
