//#define debug_output

// COMMAND
#define DISPLAY   0x01
  // SUB COMMAND
  #define STRING    0x02
  #define LINE      0x03
  #define ICON      0x04

// COMMAND
#define GOTO      0x02
  // SUB COMMAND
  #define GOTO_NO_CONDITION    0x01
  #define GOTO_CONDITION       0x02
  
// COMMAND
#define VARIABLE  0x03
  // SUB COMMAND
  #define SET_VALUE   0x01

  #define MATH_OPERATION    0x03
    #define MATH_ADDITION               0x01  // +
    #define MATH_SUBTRACTION            0x02  // -
    #define MATH_MULTIPLICATION         0x03  // *
    #define MATH_DIVISION               0x04  // /
    #define MATH_REMAINDER_OF_DIVISION  0x05  // %
    #define MATH_REVERSE                0x06  // !
    #define MATH_ISMORE                 0x07  // >
    #define MATH_SHIFT_LEFT             0x08  // <<
    #define MATH_SHIFT_RIGHT            0x09  // >>  
    #define MATH_RANDOM                 0x0A  // random
    #define MATH_EQUAL                  0x0B  // ==

//PARAMS TYPE
#define PARAM_BOOLEAN           0x01
#define PARAM_UNSIGNED_BYTE     0x02
#define PARAM_UNSIGNED_INT2     0x03
#define PARAM_UNSIGNED_INT3     0x04
#define PARAM_UNSIGNED_INT4     0x05
#define PARAM_UNSIGNED_INT6     0x06
#define PARAM_UNSIGNED_INT8     0x07
#define PARAM_VAR               0x08
#define PARAM_STRING            0x09
#define PARAM_SYSTEM_VALUE      0x0A
  #define SYSTEM_VALUE_IS_TOUCH_SCREEN                0x01
  #define SYSTEM_VALUE_IS_TOUCHED                     0x02
  #define SYSTEM_VALUE_GET_TOUCH_X                    0x03
  #define SYSTEM_VALUE_GET_YOUCH_Y                    0x04
  #define SYSTEM_VALUE_BUTTONS_COUNT                  0x05
  #define SYSTEM_VALUE_IS_BUTTON_CLICKED              0x06
  #define SYSTEM_VALUE_IS_BUTTON_LEFT_CLICK_START     0x07
  #define SYSTEM_VALUE_IS_BUTTON_RIGHT_CLICK_START    0x08
  #define SYSTEM_VALUE_IS_BUTTON_SELECT_CLICK_START   0x09
  #define SYSTEM_VALUE_SCREEN_WIDTH                   0x0A
  #define SYSTEM_VALUE_SCREEN_HEIGHT                  0x0B
#define PARAM_LABEL             0x0B

// COMMAND
#define SYSTEM_CALL       0x04
  #define SYSTEM_CALL_CLEAR_SCREEN                0x01
  #define SYSTEM_CALL_ENABLE_AUTOREDRAW_SCREEN    0x02
  #define SYSTEM_CALL_DISABLE_AUTOREDRAW_SCREEN   0x03
  #define SYSTEM_CALL_FINISH_APP                  0x04

//////////////////////////////////////////////////
#define CHECK_FILE_AVAILABLE os_fileIsAvailable()

byte b_vars[MAX_RAM_SIZE_FOR_B_APPS];

byte dp = 0;
byte repeats = 0;
boolean fileOpened = false;

#define OS_CONSTROL_EVERY_MS 30
byte timer_in_b = 0;
void check_os_controls_ifneed(){
  if(_millis() - os_clock_time - timer_in_b*OS_CONSTROL_EVERY_MS > OS_CONSTROL_EVERY_MS){
    timer_in_b++;
    os_control_loop();

    //drawDebug("Check os_controls");
  }
}

void os_run_b(char * path){
  dp = 0;
  repeats = 0;
  timer_in_b = 0;
  //d_rawDebugString(b_vars[0], 0);
  //d_rawDebugString(b_vars[1], 10);

  if (!fileOpened){
    if (os_openFile(path)) fileOpened = true;  
  }
  
  if (fileOpened){

    if (!os_seekFile(0)){
      fileOpened = false;
      return;
    }
    
    while(CHECK_FILE_AVAILABLE){
      repeats++;
      if (repeats>1025){
        #ifdef debug_output
          drawDebug("No answer app");  
        #endif
        return;
      }
      //d_rawDebug("Read string");
      #ifdef isTouchScreen
        check_os_controls_ifneed();
        //os_control_loop();
      #endif
      
      os_run_b_readString();
    }

    //os_closeFile();
  }else{
    #ifdef debug_output
      drawDebug("File is not opened");
    #endif
  }
}

void os_run_b_readString(){
  byte current=0xFF;
  byte last=0xFF;

  byte command = 0;
  byte subCommand = 0;
  
  //d_rawDebug("New string");
  
  if(CHECK_FILE_AVAILABLE){
    char command = os_readChar();

    if (command==DISPLAY){
      if(CHECK_FILE_AVAILABLE){
        subCommand = os_readChar();
        //d_rawDebug("Command Display");
        if (subCommand==LINE){
          //d_rawDebug("Subcommand Line");
          
          int param1 = os_run_b_readParam(); // X1
          int param2 = os_run_b_readParam(); // Y1
          int param3 = os_run_b_readParam(); // X2
          int param4 = os_run_b_readParam(); // Y2
          int param5 = os_run_b_readParam(); // Color

          drawLine(param1, param2, param3, param4);

          //  Finish string
          go_to_the_end_of_string();
           
        }else if(subCommand==STRING){
          //d_rawDebug("Text");
          int param1 = os_run_b_readParam(); // X
          int param2 = os_run_b_readParam(); // Y
          int param3 = os_run_b_readParam(); // color

          //Getting type of text for printing
          byte type_string = 0;
          if(CHECK_FILE_AVAILABLE) type_string = os_readChar();
          if(type_string==0x00) return;

          if(type_string==PARAM_STRING){
            while(CHECK_FILE_AVAILABLE && (current!=0 || last!=0) ){
              last = current;
              current = os_readChar();
              
              char stringToWrite[2] = {current};
              drawString(stringToWrite, param1, param2);
              param1 += FONT_CHAR_WIDTH;
              
            }
          }

          //os_readChar();
          
        }else if(subCommand==ICON){
          int param1 = os_run_b_readParam(); // x
          int param2 = os_run_b_readParam(); // y
          int param3 = os_run_b_readParam(); // type
          int param4 = os_run_b_readParam(); // width
          int param5 = os_run_b_readParam(); // height

          int icon_x=0;
          int icon_y=0;

          if(param3==0x01){
            
            while(1){

              byte color_var = os_readChar();
              
              if (color_var==0x04){
                
                byte red    = os_readChar(); 
                byte green  = os_readChar(); 
                byte blue   = os_readChar(); 

                setDrawColor(red, green, blue);
                 
                icon_x = 0;
                icon_y = 0;

                #ifdef isTouchScreen
                  check_os_controls_ifneed();
                #endif

                for (int reading_byte=0; reading_byte<(param4*param5%8==0?param4*param5/8:param4*param5/8+1); reading_byte++){
                  current = os_readChar();

                  if(current!=0x00 && current!=0xFF){
                    for (unsigned char d=0; d<8; d++){
                      if (icon_x>=param4){
                        icon_y+=icon_x/param4;
                        icon_x %= param4;
                        //icon_y++;
                      }

                      if (current&1<<(7-d)) drawPixel(param1 + icon_x, param2 + icon_y);
                      icon_x ++;
                    }
                  }else if(current==0xFF){ // Saving 1ms!!!!

                    if (icon_x>=param4){
                      icon_y+=icon_x/param4;
                      icon_x %= param4;
                    }

                    drawLine(param1 + icon_x, param2 + icon_y, param1 + icon_x+7, param2 + icon_y); 
                    icon_x+=8;
                  }else{
                    icon_x+=8;
                  }
                }
                
              }else{
                current = os_readChar();
                break;
              } 

            }
              
            setDrawColor_contrast();
          }else{
            #ifdef debug_output
              drawDebug("Unknown icon type");
            #endif
          }
        }else{
          //d_rawDebug("Unknown subcommand");
          go_to_the_end_of_string();
        }
      }    
    }else if (command==GOTO){
      //d_rawDebug("GOTO command");
      
      subCommand = os_readChar();
      if (subCommand==GOTO_NO_CONDITION){
        
        //byte byte0 = os_readChar();
        //byte byte1 = os_readChar();
        //byte byte2 = os_readChar();
        //byte byte3 = os_readChar();

        //long position = (long)bytes_to_value(byte3, byte2, byte1, byte0,0,0,0,0);

        unsigned long position = os_run_b_readParam();
        if(!os_seekFile(position)) go_to_the_end_of_string();
      }else if (subCommand==GOTO_CONDITION){
        
        //byte byte0 = os_readChar();
        //byte byte1 = os_readChar();
        //byte byte2 = os_readChar();
        //byte byte3 = os_readChar();

        //long position = (long)bytes_to_value(byte3, byte2, byte1, byte0,0,0,0,0);

        unsigned long position = os_run_b_readParam();
        unsigned int condition = os_run_b_readParam(); // Condition        
        
        if(condition!=0){
          //d_rawDebug("GORO condition true");
          if(!os_seekFile(position)) go_to_the_end_of_string();
          
        }else{
          //d_rawDebug("GOTO condition false");
          go_to_the_end_of_string();  
        }
      }else{

        //int_to_char(char *string, int num, bool fillNull);
        #ifdef debug_output
          drawDebug("Unknown GOTO subcommand");
        #endif
        
        //char address[3] = "";
        //int_to_char(address, subCommand, false);
        //d_rawDebug(address);
        
        go_to_the_end_of_string();
      }

    }else if (command==VARIABLE){
      subCommand = os_readChar();
      if (subCommand==SET_VALUE){
        int address   = os_run_b_readParam();
        int size      = os_run_b_readParam();
        uint64_t value     = os_run_b_readParam();

        //d_rawDebug("Var setted");
        //b_vars[address] = value; // Only for bytes
        set_b_var(address, size, value);

        go_to_the_end_of_string();
      }else if(subCommand==MATH_OPERATION){
        byte math_operation = os_readChar();

          #ifdef debug_output
            if(os_readChar()!=PARAM_VAR) drawDebug("Math operation has no variable");
          #else 
            os_readChar();
          #endif

          int address   = os_run_b_readParam();
          int size      = os_run_b_readParam();
          uint64_t value     = os_run_b_readParam();

        if(math_operation==MATH_ADDITION){
          set_b_var(address, size, get_b_var(address, size) + value);
        }else if(math_operation==MATH_SUBTRACTION){
          set_b_var(address, size, get_b_var(address, size) - value);
        }else if(math_operation==MATH_MULTIPLICATION){
          set_b_var(address, size, get_b_var(address, size) * value);
        }else if(math_operation==MATH_DIVISION){
          set_b_var(address, size, get_b_var(address, size) / value);
        }else if(math_operation==MATH_REMAINDER_OF_DIVISION){
          set_b_var(address, size, get_b_var(address, size) % value);
        }else if(math_operation==MATH_REVERSE){
          set_b_var(address, size, (value==0?1:0));
        }else if(math_operation==MATH_ISMORE){
          set_b_var(address, size, get_b_var(address, size) > value);
        }else if(math_operation==MATH_SHIFT_LEFT){
          set_b_var(address, size, get_b_var(address, size) << value);
        }else if(math_operation==MATH_SHIFT_RIGHT){
          set_b_var(address, size, get_b_var(address, size) >> value);
        }else if(math_operation==MATH_RANDOM){
          set_b_var(address, size, random(value));
        }else if(math_operation==MATH_EQUAL){
          set_b_var(address, size, get_b_var(address, size) == value);

        #ifdef debug_output
          }else{
            drawDebug("Unknown math operation");
        #endif
        }
        go_to_the_end_of_string();
      }else{
        #ifdef debug_output
          drawDebug("Unknown variable subcommand");
        #endif
        go_to_the_end_of_string();    
      }
    }else if (command==SYSTEM_CALL){
      subCommand = os_readChar();

      if(subCommand==SYSTEM_CALL_CLEAR_SCREEN){
        driver_clearScreen();
      }else if(subCommand==SYSTEM_CALL_ENABLE_AUTOREDRAW_SCREEN){
        set_os_auto_redraw_screen(true);
      }else if(subCommand==SYSTEM_CALL_DISABLE_AUTOREDRAW_SCREEN){
        set_os_auto_redraw_screen(false);
      }else if(subCommand==SYSTEM_CALL_FINISH_APP){
        #ifdef useNativeMenu
          os_switch_to_app(-1);
        #endif
      }

      go_to_the_end_of_string();  
    }else{
      #ifdef debug_output
        drawDebug("Unknown command");
      #endif
      go_to_the_end_of_string();  
    }
    
  }
}

void set_b_var(int address, byte size, uint64_t value){
  //byte *bytes_value = (byte*) &value;

  /* * /
  drawDebugString((int)((int)value&0x000000FF), 200);
  drawDebugString((int)((int)value&0x0000FF00)>>8, 210);
  drawDebugString((int)((int)value&0x00FF0000)>>16, 220);
  drawDebugString((int)((int)value&0xFF000000)>>24, 230);

  drawDebugString((int)((int)value&(0xFF<<0)), 260);
  drawDebugString((int)((int)value&(0xFF<<8))>>8, 270);
  drawDebugString((int)((int)value&(0xFF<<16))>>16, 280);
  drawDebugString((int)((int)value&(0xFF<<24))>>24, 290);
  //*/

  for(byte i=0; i<size; i++){
    b_vars[address + i] = ((value&(0xFF<<(i*8))))>>(i*8);
  }

}

uint64_t get_b_var(int address, byte size){

 switch(size){
    case 1: return b_vars[address];
    case 2: return (unsigned int)  bytes_to_value(b_vars[address], b_vars[address+1], 0, 0, 0, 0, 0, 0);
    case 3: return (unsigned long) bytes_to_value(b_vars[address], b_vars[address+1], b_vars[address+2], 0, 0, 0, 0, 0);
    case 4: return (unsigned long) bytes_to_value(b_vars[address], b_vars[address+1], b_vars[address+2], b_vars[address+3], 0, 0, 0, 0);
    case 6: return (unsigned long) bytes_to_value(b_vars[address], b_vars[address+1], b_vars[address+2], b_vars[address+3], b_vars[address+4], b_vars[address+5], 0, 0);
    case 8: return (unsigned long) bytes_to_value(b_vars[address], b_vars[address+1], b_vars[address+2], b_vars[address+3], b_vars[address+4], b_vars[address+5], b_vars[address+6], b_vars[address+7]);
    default: return b_vars[address];
  } 
}

byte get_size_of_b_var(byte var){
  switch(var){
    case  PARAM_BOOLEAN: return 1;
    case  PARAM_UNSIGNED_BYTE: return 1;
    case  PARAM_UNSIGNED_INT2: return 2;
    case  PARAM_UNSIGNED_INT3: return 3;
    case  PARAM_UNSIGNED_INT4: return 4;
    case  PARAM_UNSIGNED_INT6: return 6;
    case  PARAM_UNSIGNED_INT8: return 8;
    default: return 1;
  }
}

void go_to_the_end_of_string(){
  byte current=0xFF;
  byte last=0xFF;
  
  while(CHECK_FILE_AVAILABLE && (current!=0x00 || last!=0x00) ){
    last = current;
    current = os_readChar();
  }
}

uint64_t os_run_b_readParam(){
  if(CHECK_FILE_AVAILABLE){
    byte paramType = os_readChar();
    if (!CHECK_FILE_AVAILABLE) return 0;

    /*
    
    #define PARAM_BOOLEAN           0x01
    #define PARAM_UNSIGNED_BYTE     0x02
    #define PARAM_UNSIGNED_INT2     0x03
    #define PARAM_UNSIGNED_INT3     0x04
    #define PARAM_UNSIGNED_INT4     0x05
    #define PARAM_UNSIGNED_INT6     0x06
    #define PARAM_UNSIGNED_INT8     0x07
    #define PARAM_VAR               0x08
    #define PARAM_STRING            0x09
    #define PARAM_SYSTEM_VALUE      0x0A
    
    */

    if (paramType==PARAM_UNSIGNED_BYTE || paramType==PARAM_BOOLEAN){
      return (byte)os_readChar();
    //##########################################################
    }else if(paramType==PARAM_UNSIGNED_INT2){
      //int address = os_run_b_readParam();
      //int address_size = os_run_b_readParam();
      
      //d_rawDebug("Var getted");
      return (unsigned int)bytes_to_value(os_readChar(), os_readChar(),0,0,0,0,0,0);
    }else if(paramType==PARAM_UNSIGNED_INT3){
      //int address = os_run_b_readParam();
      //int address_size = os_run_b_readParam();
      
      //d_rawDebug("Var getted");
      return (unsigned long)bytes_to_value(os_readChar(), os_readChar(), os_readChar(),0,0,0,0,0);
    }else if(paramType==PARAM_UNSIGNED_INT4 || paramType==PARAM_LABEL){
      //int address = os_run_b_readParam();
      //int address_size = os_run_b_readParam();
      
      //d_rawDebug("Var getted");
      return (unsigned long)bytes_to_value(os_readChar(), os_readChar(), os_readChar(), os_readChar(),0,0,0,0);

    }else if(paramType==PARAM_UNSIGNED_INT6){
      //int address = os_run_b_readParam();
      //int address_size = os_run_b_readParam();
      
      //d_rawDebug("Var getted");
      return (uint64_t)bytes_to_value(os_readChar(), os_readChar(), os_readChar(), os_readChar(), os_readChar(), os_readChar(),0,0);
    }else if(paramType==PARAM_UNSIGNED_INT8){
      //int address = os_run_b_readParam();
      //int address_size = os_run_b_readParam();
      
      //d_rawDebug("Var getted");
      return (uint64_t)bytes_to_value(os_readChar(), os_readChar(), os_readChar(), os_readChar(), os_readChar(), os_readChar(), os_readChar(), os_readChar());
    //##########################################################  
    }else if(paramType==PARAM_VAR){
      int address = os_run_b_readParam();
      byte address_size = os_run_b_readParam();
      
      //d_rawDebug("Var getted");
      if (address_size==1){
        return b_vars[address];
      }else if(address_size==2){
        return bytes_to_value(b_vars[address], b_vars[address+1],0,0,0,0,0,0);
      }else if(address_size==3){
        return bytes_to_value(b_vars[address], b_vars[address+1], b_vars[address+2],0,0,0,0,0);
      }else if(address_size==4){
        return bytes_to_value(b_vars[address], b_vars[address+1], b_vars[address+2], b_vars[address+3],0,0,0,0);
      }else if(address_size==6){
        return bytes_to_value(b_vars[address], b_vars[address+1], b_vars[address+2], b_vars[address+3], b_vars[address+4], b_vars[address+5],0,0);
      }else if(address_size==8){
        return bytes_to_value(b_vars[address], b_vars[address+1], b_vars[address+2], b_vars[address+3], b_vars[address+4], b_vars[address+5], b_vars[address+6], b_vars[address+7]);
      }
      
      
    }else if(paramType==PARAM_SYSTEM_VALUE){
      byte get_sys_param = os_readChar();
      
      if(get_sys_param==SYSTEM_VALUE_IS_TOUCH_SCREEN){
        #ifdef isTouchScreen
          return 1;
        #else
          return 0;
        #endif
      }else if(get_sys_param==SYSTEM_VALUE_IS_TOUCHED){
        #ifdef isTouchScreen
          return touchScreen_isTouch_Start();
        #else
          return false;
        #endif
      }else if(get_sys_param==SYSTEM_VALUE_GET_TOUCH_X){
        #ifdef isTouchScreen
          return os_touch_x;
        #else
          return 0;
        #endif
      }else if(get_sys_param==SYSTEM_VALUE_GET_YOUCH_Y){
        #ifdef isTouchScreen
          return os_touch_y;
        #else
          return 0;
        #endif
      }else if(get_sys_param==SYSTEM_VALUE_BUTTONS_COUNT){
        return os_control_buttons;
      }else if(get_sys_param==SYSTEM_VALUE_IS_BUTTON_CLICKED){
        int address_btn = os_run_b_readParam();
        #ifndef conf_m5stack
          return os_control_pressStart[address_btn];
        #endif
      }else if(get_sys_param==SYSTEM_VALUE_IS_BUTTON_LEFT_CLICK_START){
        return isPressStart_Left();
      }else if(get_sys_param==SYSTEM_VALUE_IS_BUTTON_RIGHT_CLICK_START){
        return isPressStart_Right();
      }else if(get_sys_param==SYSTEM_VALUE_IS_BUTTON_SELECT_CLICK_START){
        return isPressStart_Select();
      }else if(get_sys_param==SYSTEM_VALUE_SCREEN_WIDTH){
        return SCREEN_WIDTH;
      }else if(get_sys_param==SYSTEM_VALUE_SCREEN_HEIGHT){
        return SCREEN_HEIGHT;
      }

    }
  }else return 0;
  
}


void drawDebug(char * string){
  dp ++;
  drawString(string, 10, 140 + 10*dp);
}