rm -R build/arduino/uno_shield_240x320_touchscreen/cubos/*

cat src/settings/uno_shield_320x240_touchscreen.ino             > build/arduino/uno_shield_240x320_touchscreen/cubos/cubos.ino
cat src/cubos.ino                                               >> build/arduino/uno_shield_240x320_touchscreen/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/app_sdcard_manager.ino                              build/arduino/uno_shield_240x320_touchscreen/cubos/
#cp src/app_*.ino                                               build/arduino/uno_shield_240x320_touchscreen/cubos/

#cp src/os_*.ino                                                build/arduino/uno_shield_240x320_touchscreen/cubos/

cp src/os_basic.ino                                             build/arduino/uno_shield_240x320_touchscreen/cubos/
cp src/os_clock.ino                                             build/arduino/uno_shield_240x320_touchscreen/cubos/
cp src/os_display.ino                                           build/arduino/uno_shield_240x320_touchscreen/cubos/

cp src/apps/os_exec_b.ino                                       build/arduino/uno_shield_240x320_touchscreen/cubos/

cp src/libs/driver_display_tft_shield_touchscreen.ino           build/arduino/uno_shield_240x320_touchscreen/cubos/

cp src/libs/driver_controls_tft_shield_touchscreen.ino          build/arduino/uno_shield_240x320_touchscreen/cubos/
cp src/libs/driver_sdcard_tft_shield.ino                        build/arduino/uno_shield_240x320_touchscreen/cubos/

cp src/libs/platform_avr.ino                                    build/arduino/uno_shield_240x320_touchscreen/cubos/

cp -R src/libs_h                                                build/arduino/uno_shield_240x320_touchscreen/cubos/

echo "Uno touch screen 240x320 arduino project generate DONE"