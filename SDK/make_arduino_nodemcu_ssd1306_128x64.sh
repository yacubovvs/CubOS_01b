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

cp src/os_*.ino                                                 build/arduino/nodemcu_ssd1306_128x64/cubos/
cp src/libs/driver_display_spi_led_128x64_esp32.ino             build/arduino/nodemcu_ssd1306_128x64/cubos/
rm build/arduino/nodemcu_ssd1306_128x64/cubos/os_controls_sdk.ino
cp src/libs/os_controls_nodemcu.ino                             build/arduino/nodemcu_ssd1306_128x64/cubos/

cp src/libs/platform_esp32.ino                                  build/arduino/nodemcu_ssd1306_128x64/cubos/


echo "NodeMCU ssd1306 128x64 arduino project generate DONE"