/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                                                                                         *
 *                                  >>>   IMPORTANT!   <<<                                 *
 *                   DO NOT FORGET TO ADD YOU APP IN os_applications.ino                   *
 *                                                                                         *
 *                                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#define appNameClass    Battery         // App name without spaces
#define appName         "Battery"      // App name with spaces (max 8)

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
            int batter_val = 0;

            for (int i=0; i<100; i++){
              batter_val += readVcc();
            }

            batter_val /= 100;

            drawString("Battery vol.",6,10);
            drawDebugString(batter_val, 20); // show time needed for 1 loop
            
            if (isPressStart_Select()){
                os_switch_to_app(-1);
            }

            if(digitalRead(A2)){
              if(analogRead(A3)!=0){ // if 0v on tp4056a on leg №2 then no charging
                drawString("Charging",6,30);
              }else{
                drawString("Charged",6,30);
              }
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

            pinMode(A3, INPUT);
            pinMode(A2, INPUT);
            
            // ON START CODE
            #ifdef tabletView
                this->showStatusBar = true;
            #endif

           /*                                                                                         *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            */
        };

        appNameClass(){ // Constructor
            setup();
        };

        const static byte icon[];

            static unsigned const char* getParams(unsigned char type){
            switch(type){ 
              case PARAM_TYPE_NAME: return (unsigned char*)appName; 
              case PARAM_TYPE_ICON: return icon;
              default: return (unsigned char*)""; }
        };

        long readVcc() {
            // Read 1.1V reference against AVcc
            // set the reference to Vcc and the measurement to the internal 1.1V reference
            #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
                ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
            #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
                ADMUX = _BV(MUX5) | _BV(MUX0);
            #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
                ADMUX = _BV(MUX3) | _BV(MUX2);
            #else
                ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
            #endif  

            //delay(10); // Wait for Vref to settle
            ADCSRA |= _BV(ADSC); // Start conversion
            while (bit_is_set(ADCSRA,ADSC)); // measuring

            uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
            uint8_t high = ADCH; // unlocks both

            long result = (high<<8) | low;

            result = 1125300L / result / 100; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
            return (int)result; // Vcc in millivolts
        }

};

const byte appNameClass::icon[] PROGMEM = { //128
  //////////////////////////////////////////////////////////////
  //    PUT YOUR ICON HERE
  #ifdef colorScreen
    0x02,0x01,0x02,0x20,0x02,0x18,0x04,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0xB1,0x3B,0xBB,0x29,0xAA,0x91,0x22,0xA9,0xB2,0x91,0x33,0x29,0xAB,0x91,0x22,0x99,0xAA,0x91,0x22,0x89,0xB2,0x91,0x3A,0xB1,0x80,0x00,0x00,0x01,0xBB,0xB7,0x0C,0x71,0x92,0x22,0x02,0x11,0x93,0x32,0x0C,0x11,0x92,0x12,0x02,0x21,0x93,0xB2,0x0C,0xA1,0x80,0x00,0x00,0x01,0x9F,0xFF,0xFF,0xF1,0x9F,0xFF,0x80,0x09,0x9F,0xFF,0x80,0x05,0x9F,0xFF,0x80,0x05,0x9F,0xFF,0x80,0x09,0x9F,0xFF,0xFF,0xF1,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,
  #else
    0x02,0x01,0x02,0x20,0x02,0x18,0x04,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0xB1,0x3B,0xBB,0x29,0xAA,0x91,0x22,0xA9,0xB2,0x91,0x33,0x29,0xAB,0x91,0x22,0x99,0xAA,0x91,0x22,0x89,0xB2,0x91,0x3A,0xB1,0x80,0x00,0x00,0x01,0xBB,0xB7,0x0C,0x71,0x92,0x22,0x02,0x11,0x93,0x32,0x0C,0x11,0x92,0x12,0x02,0x21,0x93,0xB2,0x0C,0xA1,0x80,0x00,0x00,0x01,0x9F,0xFF,0xFF,0xF1,0x9F,0xFF,0x80,0x09,0x9F,0xFF,0x80,0x05,0x9F,0xFF,0x80,0x05,0x9F,0xFF,0x80,0x09,0x9F,0xFF,0xFF,0xF1,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,
  #endif
  //
  //////////////////////////////////////////////////////////////
};
