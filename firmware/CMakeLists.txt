cmake_minimum_required(VERSION 3.5.0)
project(Project 
    LANGUAGES CXX C ASM)

file(GLOB SEARCH_PRJ_MCU "${CMAKE_CURRENT_SOURCE_DIR}/*/CMakeLists.txt" )
foreach( STRING_PARSER ${SEARCH_PRJ_MCU} )
	string( REPLACE "/CMakeLists.txt" "" NAME_SEARCH_PRJ_MCU ${STRING_PARSER} )
	string( REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" NAME_SEARCH_PRJ_MCU ${NAME_SEARCH_PRJ_MCU} )
    message("Sub Projects: ${NAME_SEARCH_PRJ_MCU}")
    add_subdirectory(${NAME_SEARCH_PRJ_MCU})
endforeach( STRING_PARSER ${SEARCH_PRJ_MCU} )
message("Status: ")