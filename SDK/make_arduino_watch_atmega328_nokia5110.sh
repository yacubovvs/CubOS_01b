clear

rm -R build/arduino/watch_atmega328_nokia5110/cubos/*

cat src/settings/watch_atmega328_nokia_5110.ino                 > build/arduino/watch_atmega328_nokia5110/cubos/cubos.ino
cat src/cubos.ino                                               >> build/arduino/watch_atmega328_nokia5110/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/os_applications_nano_watch_nokia.ino                build/arduino/watch_atmega328_nokia5110/cubos/

cp src/apps/app_clock.ino                                       build/arduino/watch_atmega328_nokia5110/cubos/
cp src/apps/app_menu.ino                                        build/arduino/watch_atmega328_nokia5110/cubos/
cp src/apps/app_settings.ino                                    build/arduino/watch_atmega328_nokia5110/cubos/
cp src/apps/app_test.ino                                        build/arduino/watch_atmega328_nokia5110/cubos/
cp src/apps/app_game.ino                                        build/arduino/watch_atmega328_nokia5110/cubos/
cp src/apps/app_barometer.ino                                   build/arduino/watch_atmega328_nokia5110/cubos/
cp src/apps/app_accelerometer.ino                               build/arduino/watch_atmega328_nokia5110/cubos/
cp src/apps/app_battery.ino                                     build/arduino/watch_atmega328_nokia5110/cubos/


############################################################################
#                                                                          #
#                                   OS *                                   #
#                                                                          #
############################################################################

cp src/os_basic.ino                                             build/arduino/watch_atmega328_nokia5110/cubos/
cp src/os_clock.ino                                             build/arduino/watch_atmega328_nokia5110/cubos/
cp src/os_display.ino                                           build/arduino/watch_atmega328_nokia5110/cubos/
cp src/os_icons.ino                                             build/arduino/watch_atmega328_nokia5110/cubos/


############################################################################
#                                                                          #
#                                 DRIVERS                                  #
#                                                                          #
############################################################################

cp src/libs/driver_display_nokia5110.ino                        build/arduino/watch_atmega328_nokia5110/cubos/
cp src/libs/driver_battery.ino                                  build/arduino/watch_atmega328_nokia5110/cubos/
cp src/libs/driver_barometer_bmp180.ino                         build/arduino/watch_atmega328_nokia5110/cubos/
cp src/libs/driver_accelerometer_gy_521.ino                     build/arduino/watch_atmega328_nokia5110/cubos/
cp src/libs/driver_powermanager.ino                             build/arduino/watch_atmega328_nokia5110/cubos/

cp src/libs/driver_controls_nano_watch_3btns.ino                build/arduino/watch_atmega328_nokia5110/cubos/

cp src/libs/platform_avr.ino                                    build/arduino/watch_atmega328_nokia5110/cubos/

cp -R src/libs_h                                                build/arduino/watch_atmega328_nokia5110/cubos/

echo "Atmega smartwatch arduino project generate DONE"