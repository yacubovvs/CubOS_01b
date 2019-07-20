

void app_clock_loop(){

	if (isPressStart(1)){
		current_app = 0x01;
	}else if (isPressStart(0)){
		switch(get_app_settings_watchface()){
			case 9:  {set_app_settings_watchface(11);  break; }
			case 10: { set_app_settings_watchface(9);  break; }
			case 11: { set_app_settings_watchface(10); break; }
		}
	}else if (isPressStart(2)){
		switch(get_app_settings_watchface()){
			case 9:  { set_app_settings_watchface(10);  break; }
			case 10: { set_app_settings_watchface(11);  break; }
			case 11: { set_app_settings_watchface(9);   break; }
		}
	}

	int center_x = SCREEN_WIDTH/2;
	int center_y = SCREEN_HEIGHT/2;

	int radius_small = min(center_x, center_y);
	int radius_big = max(center_x, center_y);

	if (get_app_settings_watchface()==9){
		int scale = min(SCREEN_WIDTH/19, SCREEN_HEIGHT/5); // /29 - for clock with seconds and /19 without seconds
		int x = (SCREEN_WIDTH - scale*19)/2;
		int y = (SCREEN_HEIGHT - scale*5)/2;
		
		draw_digit(os_clock_currentTime_hour()/10,  0, scale, x, y);
		draw_digit(os_clock_currentTime_hour()%10,  1, scale, x, y);
		draw_digit(10, 2, scale, x, y);
		draw_digit(os_clock_currentTime_minutes()/10, 3, scale, x, y);
		draw_digit(os_clock_currentTime_minutes()%10, 4, scale, x, y);
	}else if(get_app_settings_watchface()==10){
		int scale = min(SCREEN_WIDTH/31, SCREEN_HEIGHT/5); // /29 - for clock with seconds and /19 without seconds
		int x = (SCREEN_WIDTH - scale*31)/2;
		int y = (SCREEN_HEIGHT - scale*5)/2;
		
		draw_digit(os_clock_currentTime_hour()/10,  0, scale, x, y);
		draw_digit(os_clock_currentTime_hour()%10,  1, scale, x, y);
		draw_digit(10, 2, scale, x, y);
		draw_digit(os_clock_currentTime_minutes()/10, 3, scale, x, y);
		draw_digit(os_clock_currentTime_minutes()%10, 4, scale, x, y);
		draw_digit(10, 5, scale, x, y);
		draw_digit(os_clock_currentTime_seconds()/10, 6, scale, x, y);
		draw_digit(os_clock_currentTime_seconds()%10, 7, scale, x, y);
	}else if(get_app_settings_watchface()==11){

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
		
		// 3. Draw arrows
		#define analog_arrow_hour_length 			radius_small*0.70 // As a percentage
		#define analog_arrow_hour_back_length   	radius_small*0.20 // As a percentage
		#define analog_arrow_hour_width 			radius_small*0.06 // As a percentage

		#define analog_arrow_minutes_length 		radius_small*0.87 // As a percentage 
		#define analog_arrow_minutes_back_length 	radius_small*0.30 // As a percentage 
		#define analog_arrow_minutes_width 			radius_small*0.04 // As a percentage 

		#define analog_arrow_seconds_length 		radius_small*0.95 // As a percentage
		#define analog_arrow_seconds_back_length 	radius_small*0.35 // As a percentage 
		#define analog_arrow_seconds_width			0 // As a percentage

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


bool digitMap[11][15] = {
	{ 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 }, // Digit map - 0
	{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 }, // Digit map - 1
	{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 }, // Digit map - 2
	{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 }, // Digit map - 3
	{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1 }, // Digit map - 4
	{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 }, // Digit map - 5
	{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 }, // Digit map - 6
	{ 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 }, // Digit map - 7
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 }, // Digit map - 8
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 }, // Digit map - 9
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, // Digit map - :
};

void draw_digit(byte digit, byte pos, int scale, int label_x, int label_y){
	for (int i=0; i<15; i++){
		if (digitMap[digit][i]){
			
			int x = label_x + pos*4*scale + (i%3)*scale;
			int y = label_y + (i/3)*scale;
			
			drawRect( x, y, x + scale, y + scale-1, true);  
			
		}
	}
}
