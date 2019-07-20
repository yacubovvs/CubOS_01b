killall build

echo "/* -- core.cpp -- */"                                 > build/build.cpp
cat core.cpp                                                >> build/build.cpp
echo "/* -- settings/sdk.ino -- */"                         >> build/build.cpp
cat src/settings/sdk.ino                                    >> build/build.cpp
echo "/* -- os_icons.ino -- */"                             >> build/build.cpp
cat src/os_icons.ino                                        >> build/build.cpp
echo "/* -- cubos.ino -- */"                                >> build/build.cpp
cat src/cubos.ino                                           >> build/build.cpp
echo "/* -- os_controls_sdk.ino -- */"                      >> build/build.cpp
cat src/os_controls_sdk.ino                                 >> build/build.cpp
echo "/* -- os_menu.ino -- */"                              >> build/build.cpp

cat src/os_clock.ino                                        >> build/build.cpp
echo "/* -- os_basic.ino -- */"                             >> build/build.cpp
cat src/os_basic.ino                                        >> build/build.cpp
echo "/* -- os_display.ino -- */"                           >> build/build.cpp
cat src/os_display.ino                                      >> build/build.cpp
echo "/* -- driver_display_sdk.ino -- */"                   >> build/build.cpp
cat src/driver_display_sdk.ino                              >> build/build.cpp

echo "/* -- app_*.ino -- */"                                >> build/build.cpp
cat src/apps/app_clock.ino                                  >> build/build.cpp
cat src/apps/app_game.ino                                   >> build/build.cpp
cat src/apps/app_menu.ino                                   >> build/build.cpp
cat src/apps/app_test.ino                                   >> build/build.cpp
cat src/apps/app_settings.ino                               >> build/build.cpp

echo "/* -- os_applications.ino -- */"                      >> build/build.cpp
cat src/apps/os_applications_sdk.ino                        >> build/build.cpp

cat src/libs/platform_x86.ino                               >> build/build.cpp
echo "/* -- platform_x86.ino -- */"                         >> build/build.cpp

g++ build/build.cpp -O4 -w -o build/build
./build/build &
#./build/build