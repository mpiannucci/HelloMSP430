cmake_minimum_required(VERSION 2.8)

project(HelloMSP430)

# Set the compiler flags
set(CPU_FLAG "-mmcu=msp430g2553")
set(CMAKE_C_FLAGS ${CPU_FLAG})
set(CMAKE_EXE_LINKER_FLAGS ${CPU_FLAG})

# Set the source files
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES ${SOURCE_DIRECTORY}/main.c)

# Set the header files
#set(HEADERS)

# Create the executable
add_executable(hello_msp.elf ${SOURCES})