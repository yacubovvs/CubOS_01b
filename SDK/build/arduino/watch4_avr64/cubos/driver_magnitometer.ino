#include <Wire.h>
#include <MechaQMC5883.h>

MechaQMC5883 qmc;
int driver_magnitometer_max_x;
int driver_magnitometer_min_x;
int driver_magnitometer_max_y;
int driver_magnitometer_min_y;
int driver_magnitometer_max_z;
int driver_magnitometer_min_z;

int azimuth = 0;
int driver_magnitometer_x = 0;
int driver_magnitometer_y = 0;
int driver_magnitometer_z = 0;

void driver_magnitometer_recalibrate(){
  driver_magnitometer_max_x = -32000;
  driver_magnitometer_min_x = 32000;
  driver_magnitometer_max_y = -32000;
  driver_magnitometer_min_y = 32000;
  driver_magnitometer_max_z = -32000;
  driver_magnitometer_min_z = 32000;
}

void driver_magnitometer_setup(){
  Wire.begin();
  
  qmc.init();
  driver_magnitometer_recalibrate();

  #ifdef device_has_power_manager        
    driver_magnitometr_off();
  #endif
} 


void driver_magnitometr_on(){
  qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_256);
}

void driver_magnitometr_off(){
  qmc.setMode(Mode_Standby,ODR_200Hz,RNG_8G,OSR_256);
}

void driver_magnitometer_loop(){

  qmc.read(&driver_magnitometer_x, &driver_magnitometer_y, &driver_magnitometer_z, &azimuth);

  if(driver_acelerometer_device_is_horizontally()){
    if(driver_magnitometer_x>driver_magnitometer_max_x) driver_magnitometer_max_x = driver_magnitometer_x;
    if(driver_magnitometer_x<driver_magnitometer_min_x) driver_magnitometer_min_x = driver_magnitometer_x;

    if(driver_magnitometer_y>driver_magnitometer_max_y) driver_magnitometer_max_y = driver_magnitometer_y;
    if(driver_magnitometer_y<driver_magnitometer_min_y) driver_magnitometer_min_y = driver_magnitometer_y;

    if(driver_magnitometer_z>driver_magnitometer_max_z) driver_magnitometer_max_z = driver_magnitometer_z;
    if(driver_magnitometer_z<driver_magnitometer_min_z) driver_magnitometer_min_z = driver_magnitometer_z;
  }
  
  driver_magnitometer_x -= driver_magnitometer_min_x;
  driver_magnitometer_y -= driver_magnitometer_min_y;
  driver_magnitometer_z -= driver_magnitometer_min_z;

}

int driver_magnitometer_get_azimuth(){
  float x = (float)driver_magnitometer_x / (float)(driver_magnitometer_max_x - driver_magnitometer_min_x)*100 - 50;
  float y = (float)driver_magnitometer_y / (float)(driver_magnitometer_max_y - driver_magnitometer_min_y)*100 - 50;

  /*
  drawDebugString(x*10, 0);
  drawDebugString(y*10, 10);
  */

  //drawLine(64,32, -(64 + x * 100), 32 + y * 100);

  azimuth = -atan2(
    x,
    y
  )* 180 / PI + 360;

  return azimuth;
}