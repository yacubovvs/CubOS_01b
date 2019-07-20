rm -R build/arduino/nano-nokia5110/cubos/*

cp src/cubos.ino                                            build/arduino/nano-nokia5110/cubos/
cp src/app_*.ino                                            build/arduino/nano-nokia5110/cubos/
cp src/os_*.ino                                             build/arduino/nano-nokia5110/cubos/
cp src/libs/driver_display_nokia5100.ino                    build/arduino/nano-nokia5110/cubos/
rm build/arduino/nano-nokia5110/cubos/os_controls_sdk.ino
cp src/libs/os_controls_nano.ino                            build/arduino/nano-nokia5110/cubos/
cp src/libs/platform_avr.ino                                build/arduino/nano-nokia5110/cubos/

echo "Nano nokia 5110 arduino project generate DONE"