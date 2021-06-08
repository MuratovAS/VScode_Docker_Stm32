if(IDE STREQUAL "VSCODE")
    message(STATUS "IDE: VScode")
    set(SKOBKA "\$\{")
    configure_file(${PROJECT_SOURCE_DIR}/../cmake/vscode/launch.json.in ${PROJECT_SOURCE_DIR}/../.vscode/launch_${PRJ_NAME}_${MCU_BOARD}.json)
    configure_file(${PROJECT_SOURCE_DIR}/../cmake/vscode/tasks.json.in ${PROJECT_SOURCE_DIR}/../.vscode/tasks_${PRJ_NAME}_${MCU_BOARD}.json)
    
    add_custom_command(
        TARGET ${BINARY_NAME}.elf
        PRE_BUILD
        COMMAND bash "-c" "echo ' -- Update launch.json and tasks.json for ${PRJ_NAME}_${MCU_BOARD}'"
        COMMAND bash "-c" "cp ${CMAKE_SOURCE_DIR}/.vscode/launch_${PRJ_NAME}_${MCU_BOARD}.json  ${CMAKE_SOURCE_DIR}/.vscode/launch.json"
        COMMAND bash "-c" "cp ${CMAKE_SOURCE_DIR}/.vscode/tasks_${PRJ_NAME}_${MCU_BOARD}.json  ${CMAKE_SOURCE_DIR}/.vscode/tasks.json"
    )
endif()

