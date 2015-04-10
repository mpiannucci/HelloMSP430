cmake_minimum_required(VERSION 2.8)
project(HelloMSP430)

# Set the toolchain file
set(CMAKE_TOOLCHAIN_FILE cmake/msp430.cmake)

# Set the source directory
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Source Files
set(SOURCES ${SOURCE_DIRECTORY}/main.c
            ${SOURCE_DIRECTORY}/uart.c)

# Header files
set(HEADERS ${SOURCE_DIRECTORY}/uart.h)

# Create the executable
add_executable(hello_msp ${SOURCES})

# Create a flash target.
setup_flash_target(hello_msp rf2500)