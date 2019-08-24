/*
    ################################################################################################
    ######################################   ATTENTION!!!   ########################################

     If you are using arduino mega, set software spi to 1 (#define ENABLE_SOFTWARE_SPI_CLASS 1) in
     /Users/mac/Documents/Arduino/libraries/SdFat/src/SdFatConfig.h

    ################################################################################################
    ################################################################################################
*/

//#include <SPI.h>
#include "SdFat.h"

const uint8_t SOFT_MISO_PIN = 12;
const uint8_t SOFT_MOSI_PIN = 11;
const uint8_t SOFT_SCK_PIN  = 13;
const uint8_t SD_CHIP_SELECT_PIN = 10;

// SdFat software SPI template
#ifdef conf_uno_touch_shield
  SdFat sd;
#else
  SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> sd;
#endif

File file;

boolean driver_sdcard_init(){

  if (!sd.begin(SD_CHIP_SELECT_PIN)) {
    //sd.initErrorHalt();
    return false;
  }

  return true;
    
}


boolean os_openFile(char* path){
  file = sd.open(path);
  return file.available();
}

boolean os_toPosition(long position){
  file.seek(position);
  return file.available();
}

boolean os_fileIsAvailable(){
  return file.available();
}

byte os_readChar(){
  return file.read();
}

boolean os_closeFile(){
  file.close();
  return true;
}

boolean os_seekFile(long position){
  return file.seek(position);
}
