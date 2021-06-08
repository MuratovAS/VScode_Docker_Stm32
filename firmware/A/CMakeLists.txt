cmake_minimum_required(VERSION 3.5.0)


########## Settings
#Конфигурация проекта, расчёт адресов, создание необходимых файлов и т.д.
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectConfiguration.cmake)

project(${PRJ_NAME}_${MCU_BOARD}
		LANGUAGES CXX C ASM)
		
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/arm_CompilerSettings.cmake)


########## Build
include(${CMAKE_SOURCE_DIR}/cmake/GlobalDefines.cmake)

file(GLOB SEARCH_PRJ_MCU "${CMAKE_CURRENT_SOURCE_DIR}/*/CMakeLists.txt" )
foreach( STRING_PARSER ${SEARCH_PRJ_MCU} )
	string( REPLACE "/CMakeLists.txt" "" NAME_SEARCH_PRJ_MCU ${STRING_PARSER} )
	string( REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" NAME_SEARCH_PRJ_MCU ${NAME_SEARCH_PRJ_MCU} )
    message(STATUS "Find Sector: ${NAME_SEARCH_PRJ_MCU}")
    add_subdirectory(${NAME_SEARCH_PRJ_MCU})
endforeach( STRING_PARSER ${SEARCH_PRJ_MCU} )

