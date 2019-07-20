/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                         *
 *                                                                                         *
 *                                  >>>   IMPORTANT!   <<<                                 *
 *                       DO NOT FORGET TO ADD YOU APP IN os_menu.ino                       *
 *                                                                                         *
 *                                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#define appNameClass    TestApplication1        // App name without spaces
#define appName         "Test application 1"    // App name with spaces

//ObjClass ObjClass();
class appNameClass: public  Application{
    private:
    /* список свойств и методов для использования внутри класса */
    public:
        /* список методов доступных другим функциям и объектам программы */
        char* getName(){
            return appName;
        };
    protected:
    /*список средств, доступных при наследовании*/
};


