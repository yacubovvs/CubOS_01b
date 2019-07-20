/*
    ################################################################################################
    ######################################   ATTENTION!!!   ########################################

     If you are using arduino mega, set software spi to 1 (#define ENABLE_SOFTWARE_SPI_CLASS 1) in
     /Users/mac/Documents/Arduino/libraries/SdFat/src/SdFatConfig.h

    ################################################################################################
    ################################################################################################
*/


byte buffer_read_position = SDCARD_FILE_READ_BUFFER_SIZE;
byte sdcard_file_read_buffer[SDCARD_FILE_READ_BUFFER_SIZE];

#define SOFT_MISO_PIN       12
#define SOFT_MOSI_PIN       11
#define SOFT_SCK_PIN        13

#include "libs_h/SdFat/src/SdFat.h"              

// SdFat software SPI template
#ifdef conf_uno_touch_shield
  SdFat sd;
#else
  SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> sd;
#endif

File file;

boolean driver_sdcard_init(){

  if (!sd.begin()) {
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
  buffer_read_position = SDCARD_FILE_READ_BUFFER_SIZE;
  return file.available();
}

boolean os_fileIsAvailable(){
  return file.available();
}

byte os_readChar(){
  if (buffer_read_position>=SDCARD_FILE_READ_BUFFER_SIZE){
    buffer_read_position = 0;
    file.read( &sdcard_file_read_buffer, SDCARD_FILE_READ_BUFFER_SIZE);
    //drawDebugString( (int)(sdcard_file_read_buffer[0]), 0);
  }
  buffer_read_position++;
  return sdcard_file_read_buffer[buffer_read_position-1];
  //return file.read();
}

boolean os_closeFile(){
  file.close();
  return true;
}

boolean os_seekFile(long position){
  buffer_read_position = SDCARD_FILE_READ_BUFFER_SIZE;
  return file.seek(position);
}