clear

rm -R build/arduino/cnc_controller/cubos/*

cat src/settings/cnc_controller.ino                  > build/arduino/cnc_controller/cubos/cubos.ino
cat src/cubos.ino                                  >> build/arduino/cnc_controller/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/os_applications_cnc_controller.ino       build/arduino/cnc_controller/cubos/

#   APPS
cp src/apps/app_menu.ino                                        build/arduino/cnc_controller/cubos/
cp src/apps/app_settings.ino                                    build/arduino/cnc_controller/cubos/
cp src/apps/app_cnc_code_fromSD.ino                             build/arduino/cnc_controller/cubos/

############################################################################
#                                                                          #
#                                   OS *                                   #
#                                                                          #
############################################################################

cp src/os_basic.ino                                             build/arduino/cnc_controller/cubos/
cp src/os_clock.ino                                             build/arduino/cnc_controller/cubos/
cp src/os_display.ino                                           build/arduino/cnc_controller/cubos/
cp src/os_icons.ino                                             build/arduino/cnc_controller/cubos/


############################################################################
#                                                                          #
#                                 DRIVERS                                  #
#                                                                          #
############################################################################

cp src/libs/driver_display_u8g2.ino                             build/arduino/cnc_controller/cubos/
cp src/libs/driver_controls.ino                                 build/arduino/cnc_controller/cubos/
cp src/libs/driver_sdcard.ino                                   build/arduino/cnc_controller/cubos/
#cp src/libs/platform_esp.ino                                   build/arduino/cnc_controller/cubos/

cp -R src/libs_h                                                build/arduino/cnc_controller/cubos/

echo "cnc_controller arduino project generate DONE"