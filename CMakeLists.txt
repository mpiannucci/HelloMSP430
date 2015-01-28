cmake_minimum_required(VERSION 2.8)

project(HelloMSP430)

# Set the source files
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES ${SOURCE_DIRECTORY}/main.cpp 
           ${SOURCE_DIRECTORY}/uart.cpp
           ${SOURCE_DIRECTORY}/led.cpp )

# Set the header files
set(HEADERS ${SOURCE_DIRECTORY}/uart.h
            ${SOURCE_DIRECTORY}/led.h )

# Create the executable
add_executable(hello_msp.elf ${SOURCES} ${HEADERS})