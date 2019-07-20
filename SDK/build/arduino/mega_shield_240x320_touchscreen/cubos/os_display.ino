
/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

                                  DISPLAY FUNCTIONS

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*/

//////////////////////////////////////////////////
// Function needed for CubOS

byte os_display_param = 0b00000001;

void set_os_auto_redraw_screen(bool v){
  set_bit_to_byte(os_display_param, 0, v);
}

bool get_os_auto_redraw_screen(){
  return get_bit_from_byte(os_display_param, 0);
}

void drawString(char * dString, int x, int y){
  setStr(dString, x, y);
}

void drawString_centered(char * dString, int y){
  drawString(dString, (SCREEN_WIDTH - strlen(dString)*FONT_CHAR_WIDTH)/2, y);  
}

void drawString_centered(char * dString, int x, int y){
  drawString(dString, x - strlen(dString)*FONT_CHAR_WIDTH/2, y);  
}

void drawPixel(int x, int y){
  setPixel(x, y);
}

void drawLine(int x0, int y0, int x1, int y1){
  int dy = y1 - y0; // Difference between y0 and y1
  int dx = x1 - x0; // Difference between x0 and x1
  int stepx, stepy;

  if (dy < 0)
  {
    dy = -dy;
    stepy = -1;
  }
  else
    stepy = 1;

  if (dx < 0)
  {
    dx = -dx;
    stepx = -1;
  }
  else
    stepx = 1;

  dy <<= 1; // dy is now 2*dy
  dx <<= 1; // dx is now 2*dx
  drawPixel(x0, y0); // Draw the first pixel.

  if (dx > dy) 
  {
    int fraction = dy - (dx >> 1);
    while (x0 != x1)
    {
      if (fraction >= 0)
      {
        y0 += stepy;
        fraction -= dx;
      }
      x0 += stepx;
      fraction += dy;
      drawPixel(x0, y0);
    }
  }
  else
  {
    int fraction = dx - (dy >> 1);
    while (y0 != y1)
    {
      if (fraction >= 0)
      {
        x0 += stepx;
        fraction -= dy;
      }
      y0 += stepy;
      fraction += dx;
      drawPixel(x0, y0);
    }
  }
}

void drawRect(int x0, int y0, int x1, int y1){
  drawRect(x0, y0, x1, y1, false);
}

void drawRect(int x0, int y0, int x1, int y1, boolean fill){
  // check if the rectangle is to be filled
  if (fill == 1)
  {
    int xDiff;

    if(x0 > x1)
      xDiff = x0 - x1; //Find the difference between the x vars
    else
      xDiff = x1 - x0;

    while(xDiff > 0)
    {
      drawLine(x0, y0, x0, y1);

      if(x0 > x1)
        x0--;
      else
        x0++;

      xDiff--;
    }
  }
  else 
  {
    // best way to draw an unfilled rectangle is to draw four lines
    drawLine(x0, y0, x1, y0);
    drawLine(x0, y1, x1, y1);
    drawLine(x0, y0, x0, y1);
    drawLine(x1, y0, x1, y1);
  }
}

int treangle_area(int x0, int y0, int x1, int y1, int x2, int y2){
  //a-0
  //b-1
  //c-2
   return round(abs((x0 - x2)*(y1 - y2) + (x1-x2)*(y2-y0)));
}

void drawRect_custom( int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, boolean fill){
  if (fill){
    // all angles should be less thаn 180 degrees
    const int min_x = min(min(x0, x1), min(x2, x3));
    const int max_x = max(max(x0, x1), max(x2, x3));
    const int min_y = min(min(y0, y1), min(y2, y3));
    const int max_y = max(max(y0, y1), max(y2, y3));

    for (int i_x=min_x; i_x<max_x; i_x++){
      for (int i_y=min_y; i_y<max_y; i_y++){

        if (
          treangle_area(x0, y0, x1, y1, x2, y2) ==
          treangle_area(x0, y0, x1, y1, i_x, i_y) + 
          treangle_area(x0, y0, x2, y2, i_x, i_y) + 
          treangle_area(x2, y2, x1, y1, i_x, i_y)
          || 
          treangle_area(x0, y0, x3, y3, x2, y2) ==
          treangle_area(x0, y0, x3, y3, i_x, i_y) + 
          treangle_area(x0, y0, x2, y2, i_x, i_y) + 
          treangle_area(x2, y2, x3, y3, i_x, i_y)
        ){
          drawPixel(i_x, i_y);
        }
      }
    }    
  }else{
    drawLine(x0, y0, x1, y1);
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x0, y0);
  }
}

void drawIcon(const unsigned char* data, int x, int y){
  /* 
  byte icon_x = 0;
  byte icon_y = 0;

  //if (width<8) x = x - 8 + width; // Костыль
  for (uint8_t data_i=0; data_i<width*height; data_i++){
    //unsigned char data_char = data[data_i];
    unsigned char data_char = (char)pgm_read_word(&(data[data_i]));
    
    for (unsigned char d=0; d<8; d++){
      if (data_char&1<<d)  drawPixel(x + icon_x%8 + (icon_x/8)*8,y + icon_y);
      icon_x ++;

      if (icon_x==width){
        icon_x = 0;
        icon_y++;
      }
      if (icon_y==height) return;
    }

  }
  */

  /*
  ################################################
  #                                              #
  #               NEW IMAGE FORMAT               #
  #                                              #
  ################################################
  */

  long readPosition = 0;
  //int data_size = sizeof(data)/sizeof(data[0]);
  byte current_byte;

  //drawDebugString(data_size, 300);
  //if(data_size<3)return;

  int image_type = readRawParam(data, readPosition);    // type of image
  int image_wigth = readRawParam(data, readPosition);   // width
  int image_height = readRawParam(data, readPosition);  // height

  int icon_x=0;
  int icon_y=0;

  if(image_type==0x01){
    
    while(1){

      //if(data_size<=readPosition) break;
      byte color_var = redRawChar(data, readPosition);
      
      if (color_var==0x04){ // new color layout
        
        byte red    = redRawChar(data, readPosition); 
        byte green  = redRawChar(data, readPosition); 
        byte blue   = redRawChar(data, readPosition); 

        setDrawColor(red, green, blue);
        
        icon_x = 0;
        icon_y = 0;

        for (int reading_byte=0; reading_byte<(image_wigth*image_height%8==0?image_wigth*image_height/8:image_wigth*image_height/8+1); reading_byte++){
          //if(data_size<=readPosition) break;
          current_byte = redRawChar(data, readPosition);

          if(current_byte!=0x00 && current_byte!=0xFF){
            for (unsigned char d=0; d<8; d++){
              if (icon_x>=image_wigth){
                icon_y+=icon_x/image_wigth;
                icon_x %= image_wigth;
                //icon_y++;
              }

              if (current_byte&1<<(7-d)) drawPixel(x + icon_x, y + icon_y);
              icon_x ++;
            }
          }else if(current_byte==0xFF){ // Saving 1ms!!!!

            if (icon_x>=image_wigth){
              icon_y+=icon_x/image_wigth;
              icon_x %= image_wigth;
            }

            drawLine(x + icon_x, y + icon_y, x + icon_x+7, y + icon_y); 
            icon_x+=8;
          }else{
            icon_x+=8;
          }
        }
        
      }else{
        break;
      } 

    }
      
    setDrawColor_contrast();
  }else{
    // Unknow type of image

  }

}

//////////////////////////////////////////////////
// For debugging
void drawDebugString(int val, int y){  
  char str[11];
  int number = val;
  sprintf(str, "%d", number);
  drawString( str, 0, y);
}

void drawDebugString(char * val){
  
  // DEBUGGING
  // Problems in SDK
  /*
  int a=val;
  char b[10];
  String str;
  str=String(a);
  str.toCharArray(b,10);
  drawString( b, 0, y);
  */
}