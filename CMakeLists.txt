cmake_minimum_required(VERSION 2.8)
project(HelloMSP430)

# Set the C flags. Only the compiler is set by the platform file. The -mmcu flag is REQUIRED 
# by mspgcc to find the correct include files and enable preprocessor defs. this definition should
# be equal to the target board.
set(MSP_CPU_FLAG -mmcu=msp430g2553)
set(CMAKE_C_FLAGS "${MSP_CPU_FLAG}")
set(CMAKE_CXX_FLAGS "${MSP_CPU_FLAG}")
set(CMAKE_EXE_LINKER_FLAGS "${MSP_CPU_FLAG}")

# Set the source directory
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Source Files
set(SOURCES ${SOURCE_DIRECTORY}/main.cpp
            ${SOURCE_DIRECTORY}/led.cpp)

# Header files
set(HEADERS ${SOURCE_DIRECTORY}/led.h)

# Create the executable
add_executable(hello_msp ${HEADERS} ${SOURCES})

# Create a flash target if the toolchain file was selected correctly
if (MSP_TOOLCHAIN)
    setup_flash_target(hello_msp rf2500)
endif () 