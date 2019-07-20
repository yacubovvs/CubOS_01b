char current_watchface = 0;

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                                                                                         *
 *                                  >>>   IMPORTANT!   <<<                                 *
 *                  DO NOT FORGET TO ADD YOUR APP IN os_applications.ino                   *
 *                                                                                         *
 *                                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#define appNameClass    ClockApp           // App name without spaces
#define appName         "Clock"            // App name with spaces (max 16)

class appNameClass: public Application{
    public:
        virtual void loop() override{
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                                >>>   MAIN APP LOOP   <<<                                *
            *                                                                                         *
            */

            //EVERY FRAME CODE
            app_clock_loop();

      			if (isPressStart_Select()){
      				os_switch_to_app(-1);
      			}

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };
        void setup(){
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                              >>>   APP SETUP ON START   <<<                             *
            *                                                                                         *
            */

            // ON START APP ODE

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */
        };

		static unsigned const char* getParams(unsigned char type){
            switch(type){ 
              case PARAM_TYPE_NAME: return (unsigned char*)appName; 
              case PARAM_TYPE_ICON: return icon;
              default: return (unsigned char*)""; }
        };

		const static byte icon[] PROGMEM;

        appNameClass(){ // Constructor
            setup();
        };

    byte digitMap[11][2] = {
      { 0b11110110, 0b11011110 }, // Digit map - 0
      { 0b01001001, 0b00100100 }, // Digit map - 1
      { 0b11100111, 0b11001110 }, // Digit map - 2
      { 0b11100111, 0b10011110 }, // Digit map - 3
      { 0b10110111, 0b10010010 }, // Digit map - 4
      { 0b11110011, 0b10011110 }, // Digit map - 5
      { 0b11110011, 0b11011110 }, // Digit map - 6
      { 0b11100100, 0b10010010 }, // Digit map - 7
      { 0b11110111, 0b11011110 }, // Digit map - 8
      { 0b11110111, 0b10011110 }, // Digit map - 9
      { 0b00001000, 0b00100000 }, // Digit map - :
    };

    void draw_digit(byte digit, byte pos, int scale, int label_x, int label_y){
      for (int i=0; i<15; i++){
        if (digitMap[digit][i/8]&1<<(7-i%8)){
          
          int x = label_x + pos*4*scale + (i%3)*scale;
          int y = label_y + (i/3)*scale;     
          drawRect( x, y, x + scale, y + scale-1, true);  
          
        }
      }
    }
    
		#define WATCHFACES_COUNT 3

    ////////////////////////////
    //  WATCHFACES:
    //  1. Digital - HH:MM
    //  2. Digital - HH:MM:SS
    //  3. Analog

		void app_clock_loop(){

			if (isPressStart_Left()){
				current_watchface++;
				if (current_watchface>=WATCHFACES_COUNT) current_watchface=0;
			}else if (isPressStart_Right()){
				current_watchface--;
				if (current_watchface<0) current_watchface = WATCHFACES_COUNT-1;
			}

			const int center_x = SCREEN_WIDTH/2;
			const int center_y = SCREEN_HEIGHT/2;

			const int radius_small = min(center_x, center_y);
			const int radius_big = max(center_x, center_y);

			if (current_watchface==0 || current_watchface==1){
				int scale = min(SCREEN_WIDTH/(current_watchface==0?19:31), SCREEN_HEIGHT/5);
				int x = (SCREEN_WIDTH - scale*(current_watchface==0?19:31))/2;
				int y = (SCREEN_HEIGHT - scale*5)/2;
				
				draw_digit(os_clock_currentTime_hour()/10,  0, scale, x, y);
				draw_digit(os_clock_currentTime_hour()%10,  1, scale, x, y);
				draw_digit(10, 2, scale, x, y);
				draw_digit(os_clock_currentTime_minutes()/10, 3, scale, x, y);
				draw_digit(os_clock_currentTime_minutes()%10, 4, scale, x, y);
				
				if(current_watchface==1){
					draw_digit(10, 5, scale, x, y);
					draw_digit(os_clock_currentTime_seconds()/10, 6, scale, x, y);
					draw_digit(os_clock_currentTime_seconds()%10, 7, scale, x, y);
				}
			}else if(current_watchface==2){

				// Drawing lines
				// 1. Bold lines 

				#define analog_boldlines_height 	2
				#define analog_boldlines_width 		2
				#define analog_smalllines_height 	0

				drawRect(center_x + analog_boldlines_width - 1, center_y - radius_small, center_x - analog_boldlines_width, center_y - radius_small + analog_boldlines_height, true); // top
				drawRect(center_x + analog_boldlines_width - 1, center_y + radius_small - analog_boldlines_height-1, center_x - analog_boldlines_width, center_y + radius_small-1, true); // bottom

				drawRect(center_x + radius_small, center_y + analog_boldlines_width - 1, center_x + radius_small - analog_boldlines_height - 1, center_y - analog_boldlines_width + 1, true); // right
				drawRect(center_x - radius_small, center_y + analog_boldlines_width - 1, center_x - radius_small + analog_boldlines_height + 1, center_y - analog_boldlines_width + 1, true); // left

				// 2. Small lines
				#define i_max 24
				for (byte i=0; i<i_max; i++){
					float i_cos = cos(360/i_max*i*get_pi()/180);
					float i_sin = sin(360/i_max*i*get_pi()/180);
					drawLine(center_x + round((radius_small - analog_smalllines_height) * i_cos), center_y + round((radius_small - analog_smalllines_height) * i_sin), center_x + round(radius_small * i_cos), center_y + round(radius_small * i_sin));
				}
				
				// 3. Drawing arrows
				#define analog_arrow_hour_length 			    radius_small*0.70
				#define analog_arrow_hour_back_length     radius_small*0.20
				#define analog_arrow_hour_width 			    radius_small*0.06

				#define analog_arrow_minutes_length 		  radius_small*0.87
				#define analog_arrow_minutes_back_length 	radius_small*0.30
				#define analog_arrow_minutes_width 			  radius_small*0.04

				#define analog_arrow_seconds_length 		  radius_small*0.95
				#define analog_arrow_seconds_back_length 	radius_small*0.35
				#define analog_arrow_seconds_width			  0

				// Hours
				byte hours = os_clock_currentTime_hour();
				float radian_angle_arrow_cos 	= cos(-360/12*((hours+3)%12)*get_pi()/180);
				float radian_angle_arrow_sin    = sin(-360/12*((hours+3)%12)*get_pi()/180);

				drawRect_custom(
					center_x - analog_arrow_hour_length*radian_angle_arrow_cos - analog_arrow_hour_width*radian_angle_arrow_sin, 			center_y + analog_arrow_hour_length*radian_angle_arrow_sin - analog_arrow_hour_width*radian_angle_arrow_cos,
					center_x + analog_arrow_hour_back_length*radian_angle_arrow_cos - analog_arrow_hour_width*radian_angle_arrow_sin, 	center_y - analog_arrow_hour_back_length*radian_angle_arrow_sin - analog_arrow_hour_width*radian_angle_arrow_cos,
					center_x + analog_arrow_hour_back_length*radian_angle_arrow_cos + analog_arrow_hour_width*radian_angle_arrow_sin, 	center_y - analog_arrow_hour_back_length*radian_angle_arrow_sin + analog_arrow_hour_width*radian_angle_arrow_cos,
					center_x - analog_arrow_hour_length*radian_angle_arrow_cos + analog_arrow_hour_width*radian_angle_arrow_sin, 			center_y + analog_arrow_hour_length*radian_angle_arrow_sin + analog_arrow_hour_width*radian_angle_arrow_cos,
					true
				);

				// Minutes
				byte minutes = os_clock_currentTime_minutes();
				radian_angle_arrow_cos 	= cos(-360/60*((minutes+15)%60)*get_pi()/180);
				radian_angle_arrow_sin  = sin(-360/60*((minutes+15)%60)*get_pi()/180);


				drawRect_custom(
					center_x - analog_arrow_minutes_length*radian_angle_arrow_cos - analog_arrow_minutes_width*radian_angle_arrow_sin, 		center_y + analog_arrow_minutes_length*radian_angle_arrow_sin - analog_arrow_minutes_width*radian_angle_arrow_cos,
					center_x + analog_arrow_minutes_back_length*radian_angle_arrow_cos - analog_arrow_minutes_width*radian_angle_arrow_sin, 	center_y - analog_arrow_minutes_back_length*radian_angle_arrow_sin - analog_arrow_minutes_width*radian_angle_arrow_cos,
					center_x + analog_arrow_minutes_back_length*radian_angle_arrow_cos + analog_arrow_minutes_width*radian_angle_arrow_sin, 	center_y - analog_arrow_minutes_back_length*radian_angle_arrow_sin + analog_arrow_minutes_width*radian_angle_arrow_cos,
					center_x - analog_arrow_minutes_length*radian_angle_arrow_cos + analog_arrow_minutes_width*radian_angle_arrow_sin, 		center_y + analog_arrow_minutes_length*radian_angle_arrow_sin + analog_arrow_minutes_width*radian_angle_arrow_cos,
					true
				);

				// Seconds
				byte seconds = os_clock_currentTime_seconds();
				radian_angle_arrow_cos = cos(-360/60*((seconds+15)%60)*get_pi()/180);
				radian_angle_arrow_sin = sin(-360/60*((seconds+15)%60)*get_pi()/180);

				drawLine(
					center_x - analog_arrow_seconds_length*radian_angle_arrow_cos - analog_arrow_seconds_width*radian_angle_arrow_sin, 			center_y + analog_arrow_seconds_length*radian_angle_arrow_sin - analog_arrow_seconds_width*radian_angle_arrow_cos,
					center_x + analog_arrow_seconds_back_length*radian_angle_arrow_cos - analog_arrow_seconds_width*radian_angle_arrow_sin, 	center_y - analog_arrow_seconds_back_length*radian_angle_arrow_sin - analog_arrow_seconds_width*radian_angle_arrow_cos
				);
			}

		}

};

const byte appNameClass::icon[] PROGMEM =  {  //128
	//////////////////////////////////////////////////////////////
	//		PUT YOUR ICON HERE
	
	0x00, 0xF0, 0x0F, 0x00, 0x00, 0xFE, 0x7F, 0x00, 
	0x80, 0x9F, 0xF9, 0x00, 0xC0, 0x83, 0xC1, 0x03, 
	0xE0, 0x01, 0x80, 0x07, 0x70, 0x00, 0x00, 0x0E, 
	0x38, 0x80, 0x01, 0x1C, 0x18, 0x80, 0x01, 0x38, 
	0x1C, 0x80, 0x01, 0x38, 0x0E, 0x80, 0x01, 0x70, 
	0x06, 0x80, 0x01, 0x60, 0x06, 0x80, 0x01, 0x60, 
	0x07, 0x80, 0x01, 0xE0, 0x03, 0x80, 0x01, 0xC0, 
	0x03, 0x80, 0x01, 0xC0, 0x0F, 0xE0, 0x7F, 0xF0, 
	0x0F, 0xE0, 0x7F, 0xF0, 0x03, 0x80, 0x01, 0xC0, 
	0x03, 0x80, 0x01, 0xC0, 0x07, 0x00, 0x00, 0xE0, 
	0x06, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x60, 
	0x0E, 0x00, 0x00, 0x70, 0x1C, 0x00, 0x00, 0x38, 
	0x1C, 0x00, 0x00, 0x18, 0x38, 0x00, 0x00, 0x1C, 
	0x70, 0x00, 0x00, 0x0E, 0xE0, 0x01, 0x80, 0x07, 
	0xC0, 0x83, 0xC1, 0x03, 0x00, 0x9F, 0xF9, 0x01, 
	0x00, 0xFE, 0x7F, 0x00, 0x00, 0xF0, 0x0F, 0x00, 

	//
	//////////////////////////////////////////////////////////////
};


/*




*/
