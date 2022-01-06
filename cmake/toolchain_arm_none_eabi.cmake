################################################################################
##                              TOOLCHAIN                                     ##
################################################################################

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set_property(SOURCE ${SOURCES} PROPERTY LANGUAGE C)

################################################################################
##                              COMPILER                                      ##
################################################################################

include(${PROJECT_SOURCE_DIR}/cmake/toolchain_gcc.cmake)

set_target_properties(${TARGET} PROPERTIES SUFFIX ".elf")

add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND arm-none-eabi-size --format=berkeley --totals "$<TARGET_FILE:${TARGET}>"
        COMMAND arm-none-eabi-objcopy -O binary "$<TARGET_FILE:${TARGET}>" "$<TARGET_FILE:${TARGET}>.bin"
        COMMAND xxd "$<TARGET_FILE:${TARGET}>.bin" > "$<TARGET_FILE:${TARGET}>.bin.list"
        COMMAND arm-none-eabi-objdump -d "$<TARGET_FILE:${TARGET}>" > "$<TARGET_FILE:${TARGET}>.list"
)
