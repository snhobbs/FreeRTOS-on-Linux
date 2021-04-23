# FreeRTOS on linux

**NOTE** Make sure to check out the official demos at https://github.com/FreeRTOS/FreeRTOS/tree/master/FreeRTOS/Demo.

Demo project useful as a starting point for building an emulated application using the FreeRTOS operating
system on a posix system. Includes the [FreeRTOS](https://github.com/FreeRTOS/FreeRTOS) and [freertos-addons](https://github.com/michaelbecker/freertos-addons/) repositories as submodules. The example
main is the most bare bones example of two dynamically created tasks printing to screen when they're scheduled.
More advanced examples can be found in the [freertos-addons Linux demos](https://github.com/michaelbecker/freertos-addons/tree/master/Linux/Demo).

## Installing, Building, & Running
### Install
Each of these has submodules so those have to be checkout out.
To speed up time and reduce footprint, only the FreeRTOS/Source dir has to be initialized.
```
git clone https://github.com/snhobbs/FreeRTOS-on-Linux ./
cd FreeRTOS-on-Linux
git submodule update --init --recursive --depth=2
```

### build & run basic example
```
cd examples/basic && mkdir build && cmake ../ && make
./freertos
```
