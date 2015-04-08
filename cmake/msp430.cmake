INCLUDE(CMakeForceCompiler)

# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Generic)

# specify the cross compiler
CMAKE_FORCE_C_COMPILER(/Applications/Energia.app/Contents/Resources/Java/hardware/tools/msp430/bin/msp430-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(/Applications/Energia.app/Contents/Resources/Java/hardware/tools/msp430/bin/msp430-g++ GNU)

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH  /Applications/Energia.app/Contents/Resources/Java/hardware/tools/msp430) 

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)