if(ASTYLE STREQUAL "ON")
    message(STATUS "-- AStyle: ON")
    add_custom_command(
        TARGET ${BINARY_NAME}.elf
        PRE_BUILD
        COMMAND bash "-c" "astyle --options=${CMAKE_SOURCE_DIR}/.astylerc \
            ${CMAKE_CURRENT_SOURCE_DIR}/User/Src/*.c ${CMAKE_CURRENT_SOURCE_DIR}/User/Inc/*.h"
    )
elseif(ASTYLE STREQUAL "CHANGES")
    message(STATUS "-- AStyle: CHANGES")
    add_custom_command(
        TARGET ${BINARY_NAME}.elf
        PRE_BUILD
        COMMAND bash "-c" "${CMAKE_SOURCE_DIR}/cmake/astyle_changes.sh ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}"
    )
else()
    message(STATUS "-- AStyle: OFF")
endif()
