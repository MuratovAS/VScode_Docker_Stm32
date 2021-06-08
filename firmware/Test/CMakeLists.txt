cmake_minimum_required(VERSION 3.10)

project(UTest LANGUAGES C CXX VERSION 1.0.0)

include(cmake/CompilerSelector.cmake)
include(cmake/CompilerSettings.cmake)

#Main source code
file(GLOB_RECURSE MAIN_SRC 
	"${CMAKE_SOURCE_DIR}/*/App/User/Src/*_.c"
	"${CMAKE_SOURCE_DIR}/*/Boot/User/Src/*_.c"
	"${CMAKE_SOURCE_DIR}/*/General/Src/*_.c"
)

#ишим каталог проекта для каждого мк.
file(GLOB BOARD_MCU_TMP "${CMAKE_SOURCE_DIR}/*/App" )
foreach( BOARD_MCU ${BOARD_MCU_TMP} )
	string( REPLACE "${CMAKE_SOURCE_DIR}/" "" BOARD_MCU ${BOARD_MCU} )
	string( REPLACE "/App" "" BOARD_MCU ${BOARD_MCU} )

	include_directories (
		${CMAKE_SOURCE_DIR}/${BOARD_MCU}/App/User/Inc
		${CMAKE_SOURCE_DIR}/${BOARD_MCU}/Boot/User/Inc
		${CMAKE_SOURCE_DIR}/${BOARD_MCU}/General/Inc
	)
endforeach( BOARD_MCU ${BOARD_MCU_TMP} )

#UTest source code
file(GLOB_RECURSE TEST_SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.cpp"
	)

include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
)

#message(STATUS "${ALL_SRC}")
file(GLOB RUN_TEST_SRC "${CMAKE_CURRENT_SOURCE_DIR}/UT_*.cpp" )
foreach( RUN_TEST ${RUN_TEST_SRC} )
	string( REPLACE ".cpp" "" testname ${RUN_TEST} )
	string( REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" testname ${testname} )
	add_executable( ${testname} ${RUN_TEST} ${TEST_SRC} ${MAIN_SRC})
	message(STATUS "Test name: ${testname}")
endforeach( RUN_TEST ${RUN_TEST_SRC} )

