########## Settings

SET(LD_HEADER "_app_addr = ORIGIN(FLASH);")

# Stack address - end of RAM => 0x20000000 + RAM size
SET(STM32_STACK_ADDRESS "0x20050000")
# RAM and Flash size
SET(STM32_RAM_SIZE "320K")
SET(STM32_FLASH_SIZE "900K")
# RAM and Flash addresses
SET(STM32_FLASH_ORIGIN "0x0801F000")
SET(STM32_RAM_ORIGIN "0x20000000")

########## Sources
# Code
file(GLOB_RECURSE APP_CORE_SOURCES	"App/Core/Src/*.c")
file(GLOB_RECURSE APP_USER_SOURCES	"App/User/Src/*.c"  "App/User/Src/*.cpp")
file(GLOB_RECURSE GENERAL_SOURCES	"General/Src/*.c"  "General/Src/*.cpp")

include_directories(App/Core/Inc)
include_directories(App/User/Inc)
include_directories(General/Inc)

# lib
#file(GLOB_RECURSE APP_USER_LIB		"App/Lib/*/Src/*.c" "App/Lib/*/Src/*.cpp") #Automatic library initialization (I recommend not to use)
#include_directories(App/Lib/*/Inc) #Automatic library initialization (I recommend not to use)

file(GLOB_RECURSE LIB_SecToMSec		"App/Lib/SecToMSec/Src/*.c" "App/Lib/SecToMSec/Src/*.cpp") #example
include_directories(App/Lib/SecToMSec/Inc) #example
add_library(APP_SecToMSec         ${LIB_SecToMSec})#example


# Driver
file(GLOB_RECURSE APP_HAL_SOURCES	"App/Drivers/STM32F7xx_HAL_Driver/Src/*.c")

include_directories(App/Drivers/STM32F7xx_HAL_Driver/Inc)
include_directories(App/Drivers/CMSIS/Include)
include_directories(App/Drivers/CMSIS/Device/ST/STM32F7xx/Include)

add_library(APP_HAL 	${APP_HAL_SOURCES})
add_library(APP_CMSIS	App/Core/Src/system_stm32f7xx.c
						App/startup_stm32f745xx.s)

########## Build
# Configuring the file - compiler script: replace the variables in the file with sizes and addresses
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/STM32F745ZGTx_FLASH.ld.in ${CMAKE_CURRENT_BINARY_DIR}/APP_STM32F745ZGTx_FLASH.ld)
SET(APP_LINKER_SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/APP_STM32F745ZGTx_FLASH.ld)

# Configure the file - compiler script: replace the variables in the file with sizes and addresses
#set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/APP_${PROJECT_NAME}.map,-gc-sections,-gc-sections -specs=nosys.specs -specs=nano.specs -T ${APP_LINKER_SCRIPT}")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/APP_${PROJECT_NAME}.map,--gc-sections,--undefined=uxTopUsedPriority,--print-memory-usage${LINKER_RELEASE} -T ${APP_LINKER_SCRIPT} ${LINKER_FLAGS}")
#

# Collecting project sources, modules, etc. in elf
add_executable(APP_${PROJECT_NAME}.elf ${GENERAL_SOURCES} ${APP_CORE_SOURCES} ${APP_USER_SOURCES} ${APP_USER_LIB})
target_link_libraries(APP_${PROJECT_NAME}.elf APP_HAL APP_CMSIS APP_SecToMSec)  #Не забыть добавить Lib

# Convert elf to hex and bin
set(APP_HEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/APP_${PROJECT_NAME}.hex)
set(APP_BIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/APP_${PROJECT_NAME}.bin)
add_custom_command(TARGET APP_${PROJECT_NAME}.elf POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:APP_${PROJECT_NAME}.elf> ${APP_HEX_FILE}
		COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:APP_${PROJECT_NAME}.elf> ${APP_BIN_FILE}
		COMMENT "Building ${APP_HEX_FILE} \nBuilding ${APP_BIN_FILE}")

