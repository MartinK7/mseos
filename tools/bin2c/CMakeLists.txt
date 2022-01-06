cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET bin2c)

################################################################################
##                            TOOL SOURCES                                    ##
################################################################################

list(APPEND CFLAGS
)

list(APPEND DEFINES
)

list(APPEND SOURCES
	bin2c.c
)

list(APPEND INCLUDES
)

################################################################################
##                              COMPILER                                      ##
################################################################################

include(${PROJECT_SOURCE_DIR}/cmake/toolchain_gcc.cmake)
