#define OS_MENU_COUNT_OF_APPLICATIONS 16

void setup()
{ 
	os_control_setup();
	//setup_os_menu();
	setup_displayDriver();
	//setup_os_menu(); // Start first app
}

byte current_app = 0x00; // Splashscreen
unsigned int dtime = 0;

/*
**************************************
*                                    *
*            APPLICATIONS +          *
*                                    *
**************************************
*/

/////////////////////////////////////
// INTERFACE ELEMNTS

// LABEL
class Label{
	public:
		void draw(){
			drawString(text,0,0);
		};
		Label(char* textLabel){
			text = textLabel; 
		};
		char* text;
};

//
/////////////////////////////////////

/////////////////////////////////////
// APPLICATION CLASS
class Application{
	public:
		char name[16];
		char * getName(){
			return name;
		};
		virtual void loop()=0;
};
//
/////////////////////////////////////

/*
**************************************
*                                    *
*            APPLICATIONS -          *
*                                    *
**************************************
*/

class MainMenu: public Application{
    private:
        //Label *title = new Label("Tex");
        //Label title;
        int x = 0;
    public:
        void loop() override{
            //title.draw();
            drawString("s1s",x,0);
            x++;
        };
        void setup(){
            //interfaceElements = interface;
            //title = new Label("h");
            //title = Label("h");    
        };

        MainMenu(){ // Constructor
            strcpy(name, "Main menu"); // Setting name of app
            //app_loop = &loop;
            setup();
        };

};

class App1: public Application{
    private:
        //Label *title = new Label("Tex");
        //Label title;
    public:
        void loop() override{
            //title.draw();
            drawString("s2s2",0,10);
        };
        void setup(){
            //interfaceElements = interface;
            //title = new Label("h");
            //title = Label("h");    
        };

        App1(){ // Constructor
            strcpy(name, "App1"); // Setting name of app
            //app_loop = &loop;
            setup();
        };

};

/////////////////////////////////////
// LIST OF APPLICATIONS
Application *os_applications_list[OS_MENU_COUNT_OF_APPLICATIONS];
/////////////////////////////////////

void loop(){
	clearscreen_displayDriver();
	dtime = os_clock_update();

	//t();

	////////////////////////////////////////////////////////////////////
	// Debug string show time need for 1 loop
	//drawDebugString(dtime, 0);
	// Debug string show time need for 1 loop
	////////////////////////////////////////////////////////////////////
	
	os_control_loop(); // Check buttons

    Application *app1 = new MainMenu();
    Application *app2 = new App1();

    //Application *os_applications_list[OS_MENU_COUNT_OF_APPLICATIONS];
    
	os_applications_list[0] = app1;
    os_applications_list[1] = app2;

	os_applications_list[0]->loop();
    os_applications_list[1]->loop();
    
    delete app1;
    delete app2;

	/*
	if (current_app==0x00){ // SplashScreen
		loop_os_splashscreen();
	}else if(current_app==0x02){ // Clock
		app_clock_loop();
	}else if(current_app==0x03){ // Settings
		app_settings_loop();
	}else if(current_app==0x04){ // Game
		app_game_loop();
	}else if(current_app==0x01){ // Menu
		loop_os_menu();
	}else{ // In case of not found app go to the splashscreen
		loop_os_splashscreen();
	}
	*/
	
	updatescreen_displayDriver();
}
