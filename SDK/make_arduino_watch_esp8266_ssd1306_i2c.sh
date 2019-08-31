clear

rm -R build/arduino/watch_esp8266_ssd1306_i2c/cubos/*

cat src/settings/watch_esp8266_ssd1306_i2c.ino                  > build/arduino/watch_esp8266_ssd1306_i2c/cubos/cubos.ino
cat src/cubos.ino                                               >> build/arduino/watch_esp8266_ssd1306_i2c/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/os_applications_watch_esp8266_ssd1306_i2c.ino       build/arduino/watch_esp8266_ssd1306_i2c/cubos/

cp src/apps/app_clock.ino                                       build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/apps/app_menu.ino                                        build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/apps/app_settings.ino                                    build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/apps/app_test.ino                                        build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/apps/app_game.ino                                        build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/apps/app_battery.ino                                     build/arduino/watch_esp8266_ssd1306_i2c/cubos/


############################################################################
#                                                                          #
#                                   OS *                                   #
#                                                                          #
############################################################################

cp src/os_basic.ino                                             build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/os_clock.ino                                             build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/os_display.ino                                           build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/os_icons.ino                                             build/arduino/watch_esp8266_ssd1306_i2c/cubos/


############################################################################
#                                                                          #
#                                 DRIVERS                                  #
#                                                                          #
############################################################################

cp src/libs/driver_display_ssd1306_i2c.ino                      build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/libs/driver_battery.ino                                  build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/libs/driver_powermanager.ino                             build/arduino/watch_esp8266_ssd1306_i2c/cubos/
cp src/libs/driver_vibro.ino                                    build/arduino/watch_esp8266_ssd1306_i2c/cubos/

cp src/libs/driver_controls_esp8266_watch_3btns.ino             build/arduino/watch_esp8266_ssd1306_i2c/cubos/

cp src/libs/platform_esp8266.ino                                build/arduino/watch_esp8266_ssd1306_i2c/cubos/

cp -R src/libs_h                                                build/arduino/watch_esp8266_ssd1306_i2c/cubos/

echo "Esp8266 watch arduino project generate DONE"