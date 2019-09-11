#include <Wire.h>
#include <MechaQMC5883.h>

MechaQMC5883 qmc;

void driver_magnitometr_setup(){
  Wire.begin();
  //Serial.begin(9600);
  qmc.init();
  qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_256);
} 

int driver_magnitometer_getdata_azimuth(){
  int x, y, z;
  int azimuth;
  //float azimuth; //is supporting float too
  qmc.read(&x, &y, &z, &azimuth);

  //drawDebugString((int)(azimuth), 0);
  return 180-azimuth;
}
