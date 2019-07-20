#include <M5Stack.h>

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            CUBOS PARAMS / FUNCTION
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

//#define color256 // 256 color on screen
#define color16  // 16 colors on screen

byte current_color = 0;

/////////////////////////////////////////////////////
//  DISPLAY BUFFER

// 4 bit per pixel (max 16 unique colors on frame)
unsigned char frameBuffer[SCREEN_WIDTH/2][SCREEN_HEIGHT];
// 1 bit oer pixel (if need to update pixel on screen)
unsigned char needToClear[SCREEN_WIDTH/8+1][SCREEN_HEIGHT];

// Initing of arrays
void init_frameBuffer(){
  for (int x=0; x<SCREEN_WIDTH/2; x++){
    for (int y=0; y<SCREEN_HEIGHT; y++){
      frameBuffer[x][y] = 0;
    }
  }

  for (int x=0; x<SCREEN_WIDTH/8; x++){
    for (int y=0; y<SCREEN_HEIGHT; y++){
      needToClear[x][y] = 1;
    }
  }
}

// 4 bits array operations 
unsigned char get_first4bit_of_byte (unsigned char b){ return (0|(b>>4));}
unsigned char get_last4bit_of_byte  (unsigned char b){ return (b & 0b00001111); }
void          set_first4bit_of_byte (unsigned char &b, unsigned char val){ b = (val<<4|get_last4bit_of_byte(b));}
void          set_last4bit_of_byte  (unsigned char &b, unsigned char val){ b = (get_first4bit_of_byte(b)<<4|val);}

// "Public" functions
void set_frameBuffer_val(uint16_t x, uint16_t y, unsigned char val){
  //if (x<0||y<0||x>=SCREEN_WIDTH||y>=SCREEN_HEIGHT || val>15) return;
  if (x%2==0){
    set_first4bit_of_byte (frameBuffer[x/2][y], val);
  }else{
    set_last4bit_of_byte  (frameBuffer[x/2][y], val);
  }
}

unsigned char get_frameBuffer_val(uint16_t x, uint16_t y){
  //if (x<0||y<0||x>=SCREEN_WIDTH||y>=SCREEN_HEIGHT) return 0;
  if (x%2==0){
    return get_first4bit_of_byte (frameBuffer[x/2][y]);
  }else{
    return get_last4bit_of_byte  (frameBuffer[x/2][y]);
  }
}

void set_needToClear_val(uint16_t x, uint16_t y, bool val){
  //if (x<0||y<0||x>=SCREEN_WIDTH||y>=SCREEN_HEIGHT) return;
  return set_bit_to_byte(needToClear[x/8][y], x%8, val);
}

bool get_needToClear_val(uint16_t x, uint16_t y){
  //if (x<0||y<0||x>=SCREEN_WIDTH||y>=SCREEN_HEIGHT) return false;
  return get_bit_from_byte(needToClear[x/8][y], x%8);
}
//
/////////////////////////////////////////////////////


void clearscreen_displayDriver(){
  for (uint16_t x=0; x<SCREEN_WIDTH; x++){
    for (uint16_t y=0; y<SCREEN_HEIGHT; y++){
      if (get_needToClear_val(x,y) && get_frameBuffer_val(x,y)!=0){
        set_frameBuffer_val(x,y, 0);
        M5.Lcd.drawPixel(x, y, get_m5ColorFromPallette(0)); //Background color
      }
      
      set_needToClear_val(x,y,1);
    }
  }

}

void updatescreen_displayDriver(){
  /*
  for (int x=0; x<SCREEN_WIDTH; x++){
    for (int y=0; y<SCREEN_HEIGHT; y++){
      //if (get_needToClear_val(x, y)){
        //M5.Lcd.drawPixel(x,y, get_frameBuffer_val(x,y));
        //set_needToClear_val(x,y,0);
      //}
    }
  }*/
  M5.update();
}

void driver_clearScreen(){
  setDrawColor_background();
  init_frameBuffer();
  M5.Lcd.fillScreen(get_m5ColorFromPallette(current_color));
  setDrawColor_contrast();
}

////////////////////////////////////////////////////////
// ##################################################

byte red;
byte green;
byte blue;

byte red_bg     = 255;
byte green_bg   = 255;
byte blue_bg    = 255;

byte palette[16][3] = {
  {0x00, 0x00, 0x00}, // Background
  {0xff, 0x00, 0x00},
  {0xff, 0xd9, 0x00},
  {0x33, 0xff, 0x00},
  {0x00, 0xff, 0xea},
  {0x00, 0x66, 0xff},
  {0x00, 0x24, 0x5a},
  {0x6f, 0x00, 0xff},
  {0xff, 0x00, 0x8c},
  {0xff, 0xff, 0xff},
  {0xd8, 0xd8, 0xd8},
  {0xb4, 0xb4, 0xb4},
  {0x8f, 0x8f, 0x8f},
  {0x6b, 0x6b, 0x6b},
  {0x47, 0x47, 0x47},
  {0x00, 0x00, 0x00},
};

uint32_t get_m5ColorFromPallette(byte num){
  return ( (palette[num][0]*31/255) <<11)|( (palette[num][1]*31/255) <<6)|( (palette[num][2]*31/255) <<0);
}

void set_CurrentColor(byte r, byte g, byte b){
  //current_color = (r<<16)|(g<<8)|(b<<0);
  byte nearest_color = 0;
  int nearest_color_vector = 255*4;

  int current_vector;
  for(int i=1; i<16; i++){
    current_vector = abs(r - palette[i][0]) + abs(g - palette[i][1]) + abs(b - palette[i][2]);
    if (current_vector==0){
      current_color =  i;
      return;
    }
    if (current_vector<nearest_color_vector){
      nearest_color = i;
      nearest_color_vector = current_vector;
    }
  }

  current_color = nearest_color;
  return;
}

void setDrawColor(byte red_set, byte green_set, byte blue_set){
  red   = red_set;
  green = green_set;
  blue  = blue_set;
  
  set_CurrentColor(red, green, blue);
}

void initColor_background(byte red_set, byte green_set, byte blue_set){
  red_bg   = red_set;
  green_bg = green_set;
  blue_bg  = blue_set;

  palette[0][0] = red_set;
  palette[0][1] = green_set;
  palette[0][2] = blue_set;
}

void setDrawColor_background(){
  //set_CurrentColor(red_bg, green_bg, blue_bg);
  current_color = 0;
}

void setDrawColor_contrast(){
  if (red_bg + green_bg + blue_bg > 383){
    //red   = 0;
    //green = 0;
    //blue  = 0;
    current_color = 15; // Black
  }else{
    //red   = 255;
    //green = 255;
    //blue  = 255;
    current_color = 9;  // White
  }
  
  
  //M5.Lcd.setColor(red, green, blue);
}

// ##################################################
////////////////////////////////////////////////////////


void setup_displayDriver(){
    M5.begin();
  // M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(0, 0);

  init_frameBuffer();
}

void setPixel(int x, int y){
  if ( 
    x>=0 &&
    y>=0 &&
    x<SCREEN_WIDTH &&
    y<SCREEN_HEIGHT
    ){

      if (get_frameBuffer_val(x,y)!=1){
        M5.Lcd.drawPixel(x, y, get_m5ColorFromPallette(current_color));
        set_frameBuffer_val(x,y,get_m5ColorFromPallette(current_color)); // Contrast line color  
      }
      
      set_needToClear_val(x,y,0);

    }
}

