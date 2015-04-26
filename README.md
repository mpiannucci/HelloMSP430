HelloMSP430
===========

Simple example for the MSP 430 using the msp430-gcc toolchain. Just playing with device and testing out its limits.

Installing the compiler
------------------------
**Ubuntu 14.04**

    sudo apt-get update
    sudo apt-get install binutils-msp430 gcc-msp430 msp430-libc mspdebug
    
**Mac OSX**

* Get Energia [here](http://energia.nu/download/)
* Then install the Launchpad Drivers from [here](https://github.com/energia/Energia/wiki/Getting-Started)

**Windows**

Install MSPGCC from the [TI Project Page](http://sourceforge.net/projects/mspgcc/)

Building and Running Code
------------------------
**To Build for the msp430**
    
    cd build/
    cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/msp430.cmake ../
    make

**To Flash to Connected msp430**

    make flash
    
or....

    mspdebug rf2500 "prog hello_msp"

You can see the serial output and interact with the board using `screen`

    screen /dev/tty[YOUR DEVICE INTERFACE] 9600
