include(CMakeForceCompiler)

#---------------------------------------------------------------------------------------------------------
# CMake Toolchain File for the MSP430 using msp430-elf-gcc
#
# Author: Matthew Iannucci
#
#
# - To make a 'flash' command, call the setup_flash_target function with the TARGET NAME and DRIVER of the launchpad
#   board.
#
#---------------------------------------------------------------------------------------------------------

# The name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)
set(MSP_TOOLCHAIN 1)

# Skip compiler checks because it depends on the MCU flag being passed
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# The location of the msp430-elf-gcc toolchain. This may vary and need to be modified.


if(DEFINED ENV{MSP430_FIND_ROOT_PATH})
    set(MSP430_PATH $ENV{MSP430_FIND_ROOT_PATH})
else()
    if(CMAKE_HOST_WIN32)
        set(MSP430_PATH "C:/Program Files/msp430")
    else()
        set(MSP430_PATH /usr/local/msp430)
    endif()
endif()

# Specify the cross compiler
if(CMAKE_HOST_WIN32)
    set(CMAKE_C_COMPILER ${MSP430_PATH}/bin/msp430-elf-gcc.exe)
    set(CMAKE_CXX_COMPILER ${MSP430_PATH}/bin/msp430-elf-g++.exe)
else()
    set(CMAKE_C_COMPILER ${MSP430_PATH}/bin/msp430-elf-gcc)
    set(CMAKE_CXX_COMPILER ${MSP430_PATH}/bin/msp430-elf-g++)
endif()
set(CMAKE_C_COMPILER_ENV_VAR CC)
set(CMAKE_CXX_COMPILER_ENV_VAR CXX)

# Where is the target environment located
set(CMAKE_FIND_ROOT_PATH ${MSP430_PATH}) 

# Adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Include The header directory
include_directories(SYSTEM ${MSP430_PATH}/include ${MSP430_PATH}/msp430-elf/include)
set(CMAKE_EXE_LINKER_FLAGS "-L${MSP430_PATH}/include")

# Create a function that will instantiate a flash target command using mspdebug.
# you may have to set the path to mspdebug if it is different. In this case we are
# assuming mspdebug is in the system PATH
set(MSPDEBUG_PATH mspdebug)

function(setup_flash_target TARGET_NAME DRIVER)
    add_custom_target(flash
        COMMAND ${MSPDEBUG_PATH} ${DRIVER} --allow-fw-update 'prog ${TARGET_NAME}'
        DEPENDS ${TARGET_NAME}
    )
endfunction()
