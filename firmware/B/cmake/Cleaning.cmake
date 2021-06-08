message(STATUS "-- Cleaning: ON")

#remove cube extra files
execute_process(
	COMMAND rm  "-f" "${CMAKE_CURRENT_SOURCE_DIR}/.mxproject"
	COMMAND rm  "-f" "${CMAKE_CURRENT_SOURCE_DIR}/Makefile"
	COMMAND rm  "-f" "${CMAKE_CURRENT_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld"
	COMMAND rm  "-f" "${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f103xb.s"
	)