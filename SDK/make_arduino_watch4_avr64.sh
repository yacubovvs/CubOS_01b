clear

rm -R build/arduino/watch4_avr64/cubos/*

cat src/settings/watch4_avr64.ino                  > build/arduino/watch4_avr64/cubos/cubos.ino
cat src/cubos.ino                                  >> build/arduino/watch4_avr64/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/os_applications_watch4_avr64.ino       build/arduino/watch4_avr64/cubos/

#   APPS
cp src/apps/app_clock.ino                                       build/arduino/watch4_avr64/cubos/
cp src/apps/app_menu.ino                                        build/arduino/watch4_avr64/cubos/
cp src/apps/app_settings.ino                                    build/arduino/watch4_avr64/cubos/
cp src/apps/app_test.ino                                        build/arduino/watch4_avr64/cubos/
cp src/apps/app_game.ino                                        build/arduino/watch4_avr64/cubos/
cp src/apps/app_battery.ino                                     build/arduino/watch4_avr64/cubos/
cp src/apps/app_bluetooth.ino                                   build/arduino/watch4_avr64/cubos/
cp src/apps/app_barometer.ino                                   build/arduino/watch4_avr64/cubos/
cp src/apps/app_compass.ino                                     build/arduino/watch4_avr64/cubos/
cp src/apps/app_accelerometer.ino                               build/arduino/watch4_avr64/cubos/

############################################################################
#                                                                          #
#                                   OS *                                   #
#                                                                          #
############################################################################

cp src/os_basic.ino                                             build/arduino/watch4_avr64/cubos/
cp src/os_clock.ino                                             build/arduino/watch4_avr64/cubos/
cp src/os_display.ino                                           build/arduino/watch4_avr64/cubos/
cp src/os_icons.ino                                             build/arduino/watch4_avr64/cubos/


############################################################################
#                                                                          #
#                                 DRIVERS                                  #
#                                                                          #
############################################################################

cp src/libs/driver_display_u8g2.ino                             build/arduino/watch4_avr64/cubos/
cp src/libs/driver_battery.ino                                  build/arduino/watch4_avr64/cubos/
cp src/libs/driver_powermanager.ino                             build/arduino/watch4_avr64/cubos/
cp src/libs/driver_vibro.ino                                    build/arduino/watch4_avr64/cubos/
cp src/libs/driver_barometer_bmp180.ino                         build/arduino/watch4_avr64/cubos/
cp src/libs/driver_accelerometer_gy_521.ino                     build/arduino/watch4_avr64/cubos/
cp src/libs/driver_bluetooth.ino                                build/arduino/watch4_avr64/cubos/
cp src/libs/driver_magnitometer.ino                             build/arduino/watch4_avr64/cubos/

cp src/libs/driver_controls.ino                                 build/arduino/watch4_avr64/cubos/
cp src/libs/platform_avr.ino                                    build/arduino/watch4_avr64/cubos/

cp -R src/libs_h                                                build/arduino/watch4_avr64/cubos/

echo "Watch4_avr64 arduino project generate DONE"