include(CMakeForceCompiler)

#---------------------------------------------------------------------------------------------------------
# CMake Toolchain File for the MSP430 using Energia
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

# The location of the mspgcc toolchain. This may vary and need to be modified.
if(CMAKE_HOST_APPLE)
    set(MSP430_PATH /Applications/Energia.app/Contents/Java/hardware/tools/msp430)
elseif(CMAKE_HOST_WIN32)
    set(MSP430_PATH "C:/Program Files/Energia/Contents/hardware/tools/msp430")
else()
    set(MSP430_PATH /opt/energia/hardware/tools/msp430)
endif()

# Specify the cross compiler
if(CMAKE_HOST_WIN32)
    set(CMAKE_C_COMPILER ${MSP430_PATH}/bin/msp430-gcc.exe)
    set(CMAKE_CXX_COMPILER ${MSP430_PATH}/bin/msp430-g++.exe)
else()
    set(CMAKE_C_COMPILER ${MSP430_PATH}/bin/msp430-gcc)
    set(CMAKE_CXX_COMPILER ${MSP430_PATH}/bin/msp430-g++)
endif()

# Where is the target environment located
set(CMAKE_FIND_ROOT_PATH ${MSP430_PATH}) 

# Adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Include The header directory
include_directories(SYSTEM ${MSP430_PATH}/msp430/include)

# Create a function that will instantiate a flash target command using mspdebug.
# you may have to set the path to mspdebug if it is different
set(MSPDEBUG_PATH ${MSP430_PATH}/bin/mspdebug)

function(setup_flash_target TARGET_NAME DRIVER)
    add_custom_target(flash
        COMMAND ${MSPDEBUG_PATH} ${DRIVER} 'prog ${TARGET_NAME}'
        DEPENDS ${TARGET_NAME}
    )
endfunction()
