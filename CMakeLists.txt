cmake_minimum_required(VERSION 2.8)

project(HelloMSP430)

# Set the compiler flags
set(CPU_FLAG "-mmcu=msp430g2553")
set(CMAKE_C_FLAGS ${CPU_FLAG})
set(CMAKE_EXE_LINKER_FLAGS ${CPU_FLAG})

# Set the source files
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(SOURCES ${SOURCE_DIRECTORY}/main.c)

# Set the header files
#set(HEADERS)

# Create the executable
add_executable(hello_msp.elf ${SOURCES})

# Set the mspdebug path
# OSX using Energia.. For some reason the if statement wont work cross compiling
set(MSPDEBUG_PATH /Applications/Energia.app/Contents/Resources/Java/hardware/tools/msp430/mspdebug/mspdebug)

# Anything else 
#set(MSPDEBUG_PATH mspdebug)

add_custom_target(flash
    COMMAND ${MSPDEBUG_PATH} rf2500 'prog hello_msp.elf'
    DEPENDS hello_msp.elf
)