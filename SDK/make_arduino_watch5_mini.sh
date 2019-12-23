clear

rm -R build/arduino/watch5_mini/cubos/*

cat src/settings/watch5_mini.ino                  > build/arduino/watch5_mini/cubos/cubos.ino
cat src/cubos.ino                                  >> build/arduino/watch5_mini/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/os_applications_watch5_mini.ino       build/arduino/watch5_mini/cubos/

#   APPS
cp src/apps/app_clock.ino                                       build/arduino/watch5_mini/cubos/
cp src/apps/app_menu.ino                                        build/arduino/watch5_mini/cubos/
cp src/apps/app_settings.ino                                    build/arduino/watch5_mini/cubos/
cp src/apps/app_test.ino                                        build/arduino/watch5_mini/cubos/
cp src/apps/app_game.ino                                        build/arduino/watch5_mini/cubos/
cp src/apps/app_battery.ino                                     build/arduino/watch5_mini/cubos/
cp src/apps/app_bluetooth.ino                                   build/arduino/watch5_mini/cubos/

############################################################################
#                                                                          #
#                                   OS *                                   #
#                                                                          #
############################################################################

cp src/os_basic.ino                                             build/arduino/watch5_mini/cubos/
cp src/os_clock.ino                                             build/arduino/watch5_mini/cubos/
cp src/os_display.ino                                           build/arduino/watch5_mini/cubos/
cp src/os_icons.ino                                             build/arduino/watch5_mini/cubos/


############################################################################
#                                                                          #
#                                 DRIVERS                                  #
#                                                                          #
############################################################################

cp src/libs/driver_display_u8g2.ino                             build/arduino/watch5_mini/cubos/
cp src/libs/driver_battery.ino                                  build/arduino/watch5_mini/cubos/
cp src/libs/driver_powermanager.ino                             build/arduino/watch5_mini/cubos/
cp src/libs/driver_vibro.ino                                    build/arduino/watch5_mini/cubos/
cp src/libs/driver_bluetooth.ino                                build/arduino/watch5_mini/cubos/
cp src/libs/driver_controls.ino                                 build/arduino/watch5_mini/cubos/
#cp src/libs/platform_stm32.ino                                    build/arduino/watch5_mini/cubos/

cp -R src/libs_h                                                build/arduino/watch5_mini/cubos/

echo "Watch5 MINI arduino project generate DONE"