cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE cmake/msp430.cmake)

project(HelloMSP430)

# Set the source files
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(SOURCES ${SOURCE_DIRECTORY}/main.c)

# Set the header files
#set(HEADERS)

# Create the executable
add_executable(hello_msp ${SOURCES})

# Create a flash target.
setup_flash_target(hello_msp rf2500)