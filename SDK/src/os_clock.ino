

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
  return false;
  //return app_settings_isampm();
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