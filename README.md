HelloMSP430
===========

Simple example for the MSP 430 using the msp430-gcc toolchain. Just playing with device and testing out its limits.

Installing the compiler
------------------------
**Ubuntu 14.04**

    sudo apt-get update
    sudo apt-get install binutils-msp430 gcc-msp430 msp430-libc mspdebug

Building and Running Code
------------------------
**To Build and flash to connected msp-430**

    make install

Quick note
------------------------

Because I write code on OSX, I have copied the header for the msp430g2553 to the project directory for autocompletion and quick reference.

Take a look at [this](http://blog.mpiannucci.com/view/msp430osx) to see the stupid (but convienent) way I set this up.