########## Sys
if(CMAKE_BUILD_TYPE STREQUAL "Release")
   # TODO: add -Ofast or -Os and -lfto flags
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
   add_definitions(-DDEBUG)
   #add_definitions(-DUSE_DEBUG=1 -DUSE_ASSERTS=1 -DRTOS_USE_DEBUG=0)
endif()

# Git commit
execute_process(COMMAND
        bash "-c" "printf \"%s\" `cd ${CMAKE_CURRENT_SOURCE_DIR} && git describe --always --tags --long --abbrev=8 --dirty`"
        OUTPUT_VARIABLE APP_GIT_COMMIT
)
# short
execute_process(COMMAND
        bash "-c" "printf \"%s\" `cd ${CMAKE_CURRENT_SOURCE_DIR} && git describe --always --long --abbrev=8`"
        OUTPUT_VARIABLE APP_GIT_COMMIT_HEX)
# current branch
execute_process(COMMAND
        bash "-c" "printf \"%s\" `cd ${CMAKE_CURRENT_SOURCE_DIR} && git branch --show-current`"
        OUTPUT_VARIABLE APP_CURRENT_BRANCH
)
# determine what is it master branch
if (APP_CURRENT_BRANCH STREQUAL "master")
    set(APP_IS_MASTER_BRANCH 1)
else()
    set(APP_IS_MASTER_BRANCH 0)
endif()
# timestamp
execute_process(
        COMMAND bash "-c" "printf \"%s\" `date +%s`"
        OUTPUT_VARIABLE BUILD_TIMESTAMP
        ERROR_QUIET
)

configure_file(../cmake/build_info.h.in ${CMAKE_BINARY_DIR}/generated/${BINARY_NAME}/build_info.h)
configure_file(../cmake/build_info.c.in ${CMAKE_BINARY_DIR}/generated/${BINARY_NAME}/build_info.c)