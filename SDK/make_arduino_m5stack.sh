rm -R build/arduino/m5stack/cubos/*

cat src/settings/m5stack.ino                        > build/arduino/m5stack/cubos/cubos.ino
cat src/cubos.ino                                   >> build/arduino/m5stack/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/os_applications_m5stack.ino             build/arduino/m5stack/cubos/

cp src/apps/app_clock.ino                           build/arduino/m5stack/cubos/
cp src/apps/app_sdcard_manager.ino                  build/arduino/m5stack/cubos/
cp src/apps/app_menu.ino                            build/arduino/m5stack/cubos/
cp src/apps/app_settings.ino                        build/arduino/m5stack/cubos/
cp src/apps/app_test.ino                            build/arduino/m5stack/cubos/
cp src/apps/app_game.ino                            build/arduino/m5stack/cubos/
cp src/apps/os_exec_b.ino                           build/arduino/m5stack/cubos/

###########################################################################
#                                                                         #
#                                 OS LIBS                                 #
#                                                                         #
###########################################################################

cp src/os_*.ino                                     build/arduino/m5stack/cubos/
cp src/libs/driver_display_m5stack.ino              build/arduino/m5stack/cubos/
cp src/libs/os_controls_m5stack.ino                 build/arduino/m5stack/cubos/
cp src/libs/platform_esp32.ino                      build/arduino/m5stack/cubos/
cp src/libs/driver_sdcard_m5stack.ino               build/arduino/m5stack/cubos/

cp -R src/libs_h                                    build/arduino/m5stack/cubos/

echo "M5Stack arduino project generate DONE"