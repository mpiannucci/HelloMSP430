include(CMakeForceCompiler)

# The name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)
set(MSP_BOARD msp430g2553)

# The location of the mspgcc toolchain. This may vary and need to be modified.
if(CMAKE_HOST_APPLE)
    set(MSP430_PATH /Applications/Energia.app/Contents/Resources/Java/hardware/tools/msp430)
elseif(CMAKE_HOST_WIN32)
    set(MSP430_PATH C:/Users/miannucci/msp430)
else()
    set(MSP430_PATH /usr/msp430)
endif()

# Specify the cross compiler
if(CMAKE_HOST_WIN32)
    CMAKE_FORCE_C_COMPILER(${MSP430_PATH}/bin/msp430-gcc.exe GNU)
    CMAKE_FORCE_CXX_COMPILER(${MSP430_PATH}/bin/msp430-g++.exe GNU)
elseif(CMAKE_HOST_APPLE)
    CMAKE_FORCE_C_COMPILER(${MSP430_PATH}/bin/msp430-gcc GNU)
    CMAKE_FORCE_CXX_COMPILER(${MSP430_PATH}/bin/msp430-g++ GNU)
else()
    CMAKE_FORCE_C_COMPILER(msp430-gcc GNU)
    CMAKE_FORCE_CXX_COMPILER(msp430-g++ GNU)
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
if (CMAKE_HOST_APPLE OR CMAKE_HOST_WIN32)
    include_directories(SYSTEM ${MSP430_PATH}/msp430/include)
else()
    include_directories(SYSTEM ${MSP430_PATH}/include)
endif()

# Set the compiler flags (REQUIRED). This is defined here and not the toolchain file 
# so the toolchain file can be re used for multiple boards
set(CPU_FLAG "-mmcu=${MSP_BOARD}")
set(CMAKE_C_FLAGS ${CPU_FLAG})
set(CMAKE_EXE_LINKER_FLAGS ${CPU_FLAG})

# Create a function that will instantiate a flash target command using mspdebug.
# you may have to set the path to mspdebug if it is different
if (CMAKE_HOST_APPLE)
    set(MSPDEBUG_PATH ${MSP430_PATH}/mspdebug/mspdebug)
else()
    set(MSPDEBUG_PATH mspdebug)
endif()
function(setup_flash_target TARGET_NAME DRIVER)
    add_custom_target(flash
        COMMAND ${MSPDEBUG_PATH} ${DRIVER} 'prog ${TARGET_NAME}'
        DEPENDS ${TARGET_NAME}
    )
endfunction()