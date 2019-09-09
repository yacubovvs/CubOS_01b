//#include "libs_h/BMP180_Breakout_Arduino_Library/src/SFE_BMP180.h"
#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;


double barometer_T,barometer_P,p0,a,baseline;

void barometer_setup()
{
  pressure.begin();
}


boolean getPressure_barometer(){
  char status;
  
  status = pressure.startTemperature();

  
  if (status != 0)
  {
    delay(status);

    status = pressure.getTemperature(barometer_T);
    if (status != 0)
    {
      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(barometer_P,barometer_T);
        if (status != 0)
        {
          
          drawDebugString((int)(barometer_P*1000), 20);
          drawDebugString((int)(barometer_T*1000), 30);
          //drawDebugString((int)(p0*1000), 36);
          //drawDebugString((int)(a*1000), 42);
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