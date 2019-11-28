//#include "libs_h/BMP180_Breakout_Arduino_Library/src/SFE_BMP180.h"
#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;


double 
        barometer_Temperature,
        barometer_Pressure
        ;

double barometer_Pressure_Current = 760;

void barometer_setup()
{
  pressure.begin();
}


void barometer_finish()
{
  //pressure.stop();
}

void barometer_reset_current_pressure()
{
  barometer_Pressure_Current = get_barometer_mm_Hg();
}

double get_barometer_Pressure(){
  return barometer_Pressure;
}

double get_barometer_mm_Hg(){
  return barometer_Pressure*100/133.322;
}

double get_altitude(){
  return ((double)760 - get_barometer_mm_Hg())*10;
}

double get_altitude_def(){
  return ((double)barometer_Pressure_Current - get_barometer_mm_Hg())*10;
}

boolean barometer_updateData(){
  char status;
  
  status = pressure.startTemperature();

  
  if (status != 0)
  {
    delay(status);

    status = pressure.getTemperature(barometer_Temperature);
    if (status != 0)
    {
      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(barometer_Pressure,barometer_Temperature);
        if (status != 0)
        {

          //barometer_Altitude
          
          //barometer_Altitude = pressure.sealevel();
          //barometer_Sealevel;

          //drawIntString( ((long)(barometer_Pressure * 10.0)), 20);
          //drawDebugString((int)(barometer_Temperature*1000), 30);

          return true;
          
        }
        return false;
      }
      return false;
    }
    return false;
  }
  return false;
}