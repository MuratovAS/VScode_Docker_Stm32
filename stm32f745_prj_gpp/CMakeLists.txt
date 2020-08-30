cmake_minimum_required(VERSION 3.5.0)

########## Settings
project(01_01 CXX C ASM)

# The preprocessor directives needed for the library.
add_definitions(-DSTM32F745xx)
include(${PROJECT_SOURCE_DIR}/cmake/stm32f745.cmake)

########## pre-build
#remove cube extra files
execute_process(
   COMMAND rm "${PROJECT_SOURCE_DIR}/App/.mxproject"
   COMMAND rm "${PROJECT_SOURCE_DIR}/App/Makefile"
   COMMAND rm "${PROJECT_SOURCE_DIR}/App/STM32F745ZGTx_FLASH.ld"
   COMMAND rm "${PROJECT_SOURCE_DIR}/Boot/.mxproject"
   COMMAND rm "${PROJECT_SOURCE_DIR}/Boot/Makefile"
   COMMAND rm "${PROJECT_SOURCE_DIR}/Boot/STM32F745ZGTx_FLASH.ld"
   )

execute_process(COMMAND
        bash "-c" "printf \"%s\" `cd ${CMAKE_CURRENT_SOURCE_DIR} && git describe --always --tags --long --abbrev=8 --dirty`"
        OUTPUT_VARIABLE APP_GIT_COMMIT)
file(WRITE General/Inc/git-rev.h
"#define STR_EXPAND(x) #x
#define STR(x) STR_EXPAND(x)
#define GIT_STR STR(GIT_REV)
#define GIT_REV \
${APP_GIT_COMMIT}"
)

########## Sys
if(CMAKE_BUILD_TYPE STREQUAL "Release")

elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
   add_definitions(-DDEBUG)
endif()

########## Build
if(FLASH_SECTION STREQUAL "Boot")
   include(Boot/Boot.cmake)
elseif(FLASH_SECTION STREQUAL "App")
   include(App/App.cmake)
endif()