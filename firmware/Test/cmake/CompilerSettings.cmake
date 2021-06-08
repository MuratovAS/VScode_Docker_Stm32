set(WARNINGS "-Wall") ## -Wextra -Wno-comment -Wno-unused-parameter !!!-Werror
set(COMMON_FLAGS " ${WARNINGS}")

SET(CMAKE_CXX_FLAGS "${COMMON_FLAGS}  -Wno-register -fno-exceptions -frtti")
SET(CMAKE_C_FLAGS "${COMMON_FLAGS}")
