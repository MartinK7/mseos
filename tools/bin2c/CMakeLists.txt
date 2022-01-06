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

add_executable(${TARGET} ${SOURCES})
target_compile_definitions(${TARGET} PUBLIC ${DEFINES})
target_include_directories(${TARGET} PUBLIC ${INCLUDES})
target_compile_options(${TARGET} PUBLIC ${CFLAGS})
target_link_options(${TARGET} PUBLIC ${LFLAGS})
target_link_libraries(${TARGET} ${LIBRARIES})

