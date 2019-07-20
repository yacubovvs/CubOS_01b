

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

#define appNameClass    SampleGame         // App name without spaces
#define appName         "Sample game"         // App name with spaces (max 16)

class appNameClass: public Application{
    public:
        float player_y = 0;
        float player_x = 0;
        float player_v_y = 0;

        long delay_timer = 0;
        bool isGameOver = false;

        int block_y = 0;

        virtual void loop() override{
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                                >>>   MAIN APP LOOP   <<<                                *
            *                                                                                         *
            */

            //EVERY FRAME CODE
            //drawString("Sample game loop",0,10);

            //if (isPressStart_Select()){
                //os_switch_to_app(-1);
            //}
            
            if (isPressStart_Left()){
                os_switch_to_app(-1);
            }

            if (isGameOver) game_over_looop();
            else game_loop();

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */

        };

        void new_game(){
            player_y = 0;
            player_v_y = 0;
            player_x = 0;

            delay_timer = 0;
            isGameOver = false;
        }

        void game_loop(){
            player_v_y += SCREEN_HEIGHT/30;
            
            if (isPressStart_Select()){
                player_v_y -= SCREEN_HEIGHT*2;
            }

            player_y += player_v_y * dtime/1000/2;
            player_x += 40*(float)dtime/1000;

            if (player_x>SCREEN_WIDTH*1.1 + 12){
                player_x = 0;  
                block_y = SCREEN_HEIGHT*2*(millis()%100)/3/100;
            }

            if (player_y<0){
                player_y = 0;
                player_v_y = 0;
            }

            if (player_y + 12>SCREEN_HEIGHT){
                gameOver();
            }

            // Check collision
            int playerx = SCREEN_WIDTH/6;
            int playerx1 = SCREEN_WIDTH/6 + 16;
            int playery = player_y;
            int playery1 = player_y + 12;

            int blockx = (int)(SCREEN_WIDTH - player_x);
            int blockx1 = ( (int)(SCREEN_WIDTH - player_x) ) + 12;
            int blocky = block_y;
            int blocky1 = block_y + SCREEN_HEIGHT/3;

            if (playerx < blockx1 && playerx1 > blockx && playery < blocky1 && playery1 > blocky){
                gameOver();
            }

            drawIcon(player,SCREEN_WIDTH/6,player_y, 16,12);

            drawLine(0, SCREEN_HEIGHT-1, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
            
            drawRect(  (int)(SCREEN_WIDTH - player_x) , block_y, ( (int)(SCREEN_WIDTH - player_x) ) + 12, block_y + SCREEN_HEIGHT/3, true); 
        }

        void gameOver(){
            player_y = 0; player_v_y = 0;

            delay_timer = millis();
            isGameOver = true;
        }

        void game_over_looop(){
          drawString_centered("GAME OVER",SCREEN_WIDTH/2,SCREEN_HEIGHT/2 - FONT_CHAR_HEIGHT - 2);

          if (abs( (int)(delay_timer-millis())) >3000){ isGameOver = false; new_game();}
          if (abs( (int)(delay_timer-millis()))>500 && isPressStart_Select()){ isGameOver = false; new_game();}
        }

        void setup(){
            /*
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *                                                                                         *
            *                              >>>   APP SETUP ON START   <<<                             *
            *                                                                                         *
            */
            new_game();
            // ON START APP CODE

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
        const static byte player[] PROGMEM; 

        appNameClass(){ // Constructor
            setup();
        };        

};

const byte appNameClass::icon[] PROGMEM = {
  //////////////////////////////////////////////////////////////
  //    PUT YOUR APP ICON HERE
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x80, 0x07, 
    0xE0, 0x01, 0x80, 0x07, 0xE0, 0x01, 0x80, 0x07, 
    0xE0, 0x01, 0x80, 0x07, 0xE0, 0x0F, 0xF0, 0x07, 
    0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 
    0x80, 0xFF, 0xFF, 0x01, 0xC0, 0xFF, 0xFF, 0x03, 
    0xE0, 0xFF, 0xFF, 0x07, 0xF0, 0xF7, 0xEF, 0x0F, 
    0xF8, 0xE3, 0xC7, 0x1F, 0xF8, 0xE3, 0xC7, 0x1F, 
    0xFF, 0xE3, 0xC7, 0xFF, 0xFF, 0xF7, 0xEF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xF3, 
    0xCF, 0xFF, 0xFF, 0xF3, 0xCF, 0xFF, 0xFF, 0xF3, 
    0xCF, 0x01, 0x80, 0xF3, 0xCF, 0x01, 0x80, 0xF3, 
    0xCF, 0x3F, 0xFC, 0xF3, 0x00, 0x3F, 0xFC, 0x00, 
    0x00, 0x3F, 0xFC, 0x00, 0x00, 0x3F, 0xFC, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  //
  //////////////////////////////////////////////////////////////
};

const byte appNameClass::player[] PROGMEM  = { //16x12
    0b11000000, 0b00000111,
    0b00110000, 0b00001010,
    0b00001000, 0b00010001,
    0b00011110, 0b00101001,
    0b00100001, 0b00101001,
    0b01000001, 0b00100001,
    0b01000001, 0b01111110,
    0b00100010, 0b10000001,
    0b10011100, 0b01111110,
    0b00001000, 0b01000001,
    0b00010000, 0b00111110,
    0b11100000, 0b00000001,
    
}; 
