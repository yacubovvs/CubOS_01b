clear

rm -R build/arduino/mega_shield_320x480_touchscreen/cubos/*

cat src/settings/mega_shield_480x320_touchscreen.ino            > build/arduino/mega_shield_320x480_touchscreen/cubos/cubos.ino
cat src/cubos.ino                                               >> build/arduino/mega_shield_320x480_touchscreen/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/os_applications_mega2560_touch.ino                  build/arduino/mega_shield_320x480_touchscreen/cubos/

cp src/apps/app_clock.ino                                       build/arduino/mega_shield_320x480_touchscreen/cubos/
cp src/apps/app_sdcard_manager.ino                              build/arduino/mega_shield_320x480_touchscreen/cubos/
cp src/apps/app_menu.ino                                        build/arduino/mega_shield_320x480_touchscreen/cubos/
cp src/apps/app_settings.ino                                    build/arduino/mega_shield_320x480_touchscreen/cubos/
cp src/apps/app_test.ino                                        build/arduino/mega_shield_320x480_touchscreen/cubos/
cp src/apps/app_calibration_touch.ino                           build/arduino/mega_shield_320x480_touchscreen/cubos/


############################################################################
#                                                                          #
#                                 OS  LIBS                                 #
#                                                                          #
############################################################################

cp src/os_*.ino                                                 build/arduino/mega_shield_320x480_touchscreen/cubos/
cp src/apps/os_exec_b.ino                                       build/arduino/mega_shield_320x480_touchscreen/cubos/
cp src/libs/driver_display_tft_shield_touchscreen.ino           build/arduino/mega_shield_320x480_touchscreen/cubos/

cp src/libs/driver_controls_tft_shield_touchscreen.ino          build/arduino/mega_shield_320x480_touchscreen/cubos/

cp src/libs/driver_sdcard_mega_shield.ino                       build/arduino/mega_shield_320x480_touchscreen/cubos/

cp src/libs/platform_avr.ino                                    build/arduino/mega_shield_320x480_touchscreen/cubos/

cp -R src/libs_h                                                build/arduino/mega_shield_320x480_touchscreen/cubos/

echo "Mega 2560 touch screen 320x480 arduino project generate DONE"