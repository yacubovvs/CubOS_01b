rm -R build/arduino/nano_SSD1206_128x64/cubos/*

cp src/cubos.ino                                            build/arduino/nano_SSD1206_128x64/cubos/
cp src/app_*.ino                                            build/arduino/nano_SSD1206_128x64/cubos/
cp src/os_*.ino                                             build/arduino/nano_SSD1206_128x64/cubos/
cp src/libs/driver_display_spi_ssd1306_128x64_nano.ino      build/arduino/nano_SSD1206_128x64/cubos/
rm build/arduino/nano_SSD1206_128x64/cubos/os_controls_sdk.ino
cp src/libs/os_controls_nano.ino                            build/arduino/nano_SSD1206_128x64/cubos/
cp src/libs/platform_avr.ino                                build/arduino/nano_SSD1206_128x64/cubos/

echo "Nano arduino project generate DONE"