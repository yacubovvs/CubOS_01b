
/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
  PARAMS
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/
// device buttons count
const byte os_control_buttons = 3; 

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
  HENDLER
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

void os_control_setup(){}
void os_control_loop(){};

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button started to press
boolean isPressStart(byte num){
  if (num>=os_control_buttons) return false;
  else{
    switch(num){
        case 0: return M5.BtnA.wasReleased();
        case 1: return M5.BtnB.wasReleased();
        case 2: return M5.BtnC.wasReleased();
    }
  } 
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button press finished
boolean isPressEnd(int num){
  if (num>=os_control_buttons) return false;
  else{
    switch(num){
        case 0: return M5.BtnA.wasReleased();
        case 1: return M5.BtnB.wasReleased();
        case 2: return M5.BtnC.wasReleased();
        default: return false;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Call to check is button pressed
boolean isPress(int num){
  if (num>=os_control_buttons) return false;
  else{
    switch(num){
        case 0: return M5.BtnA.wasReleased();
        case 1: return M5.BtnB.wasReleased();
        case 2: return M5.BtnC.wasReleased();
        default: return false;
    }
  }
}

boolean isPressStart_Left(){
    return isPressStart(0);
}

boolean isPressStart_Select(){
    return isPressStart(1);
}

boolean isPressStart_Right(){
    return isPressStart(2);
}