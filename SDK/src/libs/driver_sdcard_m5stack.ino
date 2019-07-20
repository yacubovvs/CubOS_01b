
#include <M5Stack.h>

File file;

boolean driver_sdcard_init(){
  M5.begin();
  if (!SD.begin()) {
    return false;
  }

  return true;
    
}


boolean os_openFile(char* path){
  file = SD.open(path, FILE_READ);
  return true;
}

boolean os_toPosition(long position){
  file.seek(position);
  return file.available();
  //return true;
}

boolean os_fileIsAvailable(){
  return file.available();
  //return true;
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