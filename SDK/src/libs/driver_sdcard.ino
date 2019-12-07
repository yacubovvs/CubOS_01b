byte buffer_read_position = SDCARD_FILE_READ_BUFFER_SIZE;
byte sdcard_file_read_buffer[SDCARD_FILE_READ_BUFFER_SIZE];
int buffer_position = 0;

#define SOFT_MISO_PIN       12
#define SOFT_MOSI_PIN       11
#define SOFT_SCK_PIN        13

#include "libs_h/SdFat/src/SdFat.h"              

SdFat sd;
File file;

boolean driver_sdcard_init(){
  if (!sd.begin()) {
    return false;
  }
  return true;
}


boolean os_openFile(char* path){
  file = sd.open(path);
  buffer_position = 0;
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

boolean fileIsNotEnded(){
  return (buffer_position-1) * SDCARD_FILE_READ_BUFFER_SIZE + buffer_read_position < file.size();
}

byte os_readChar(){
  if (buffer_read_position>=SDCARD_FILE_READ_BUFFER_SIZE){
    buffer_read_position = 0;
    file.read( &sdcard_file_read_buffer, SDCARD_FILE_READ_BUFFER_SIZE);

    buffer_position++;
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