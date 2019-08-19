
clear

rm -R build/arduino/nodemcu_ssd1306_128x64/cubos/*

cat src/settings/nodemcu_ssd1206_128x64.ino                     > build/arduino/nodemcu_ssd1306_128x64/cubos/cubos.ino
cat src/cubos.ino                                               >> build/arduino/nodemcu_ssd1306_128x64/cubos/cubos.ino

############################################################################
#                                                                          #
#                               APPLICATIONS                               #
#                                                                          #
############################################################################

#   APPS CONFIG
cp src/apps/os_applications_nodemcu_ssd1306_128x64.ino          build/arduino/nodemcu_ssd1306_128x64/cubos/

cp src/apps/app_clock.ino                                       build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/apps/app_menu.ino                                        build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/apps/app_settings.ino                                    build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/apps/app_test.ino                                        build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/apps/app_game.ino                                        build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/apps/app_wificonnect.ino                                 build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/apps/app_battery.ino                                     build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/apps/app_www.ino                                         build/arduino/nodemcu_ssd1306_128x64/cubos/


############################################################################
#                                                                          #
#                                   OS *                                   #
#                                                                          #
############################################################################

cp src/os_basic.ino                                             build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/os_clock.ino                                             build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/os_display.ino                                           build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/os_icons.ino                                             build/arduino/nodemcu_ssd1306_128x64/cubos/


############################################################################
#                                                                          #
#                                 DRIVERS                                  #
#                                                                          #
############################################################################

cp src/libs/driver_display_spi_led_128x64_esp32.ino             build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/libs/driver_powermanager.ino                             build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/libs/driver_wifi_esp8266.ino                             build/arduino/nodemcu_ssd1306_128x64/cubos/

cp src/libs/os_controls_nodemcu.ino                             build/arduino/nodemcu_ssd1306_128x64/cubos/

cp src/libs/platform_esp32.ino                                  build/arduino/nodemcu_ssd1306_128x64/cubos/

cp -R src/libs_h                                                build/arduino/nodemcu_ssd1306_128x64/cubos/

echo "NodeMCU ssd1306 128x64 arduino project generate DONE"