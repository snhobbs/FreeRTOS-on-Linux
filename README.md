# FreeRTOS on linux
Demo project useful as a starting point for building an emulated application using the FreeRTOS operating
system on a posix system. Includes the FreeRTOS [https://github.com/FreeRTOS/FreeRTOS] and freertos-addons [https://github.com/michaelbecker/freertos-addons/] repositories as submodules. The example
main is the most bare bones example of two dynamically created tasks printing to screen when they're scheduled.
More advanced examples can be found in the freertos-addons Linux demos [https://github.com/michaelbecker/freertos-addons/tree/master/Linux/Demo].

## Building & Running
build:
mkdir build && cd build
cmake ../
make
cd ..

run: 
bin/freertos

