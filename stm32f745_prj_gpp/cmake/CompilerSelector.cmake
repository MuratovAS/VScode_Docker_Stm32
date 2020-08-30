option(CROSS_COMPILE "Path to cross compiler" /usr/bin/arm-none-eabi-)

set(triple arm-none-eabi)
set(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER "${CROSS_COMPILE}gcc")
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER "${CROSS_COMPILE}g++")
set(CMAKE_CXX_COMPILER_TARGET ${triple})
set(CMAKE_ASM_COMPILER "${CROSS_COMPILE}gcc")
set(CMAKE_ASM_COMPILER_TARGET ${triple})