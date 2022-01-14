cmake_minimum_required(VERSION 3.6)

set(TARGET stm32blink)

################################################################################
##                            APP SOURCES                                     ##
################################################################################

set(LINKERSCRIPT linkerscript.ld)
set(ISAPP YES)

list(APPEND CFLAGS
	-mthumb -mcpu=cortex-m4
)

list(APPEND DEFINES
)

list(APPEND SOURCES
	head.s
	main.c
)

list(APPEND INCLUDES
	${PROJECT_SOURCE_DIR}/kernel/include
)

################################################################################
##                              FLAGS                                         ##
################################################################################

set(NOSTD -nostdlib -nostdinc)

list(APPEND CFLAGS
	${NOSTD}
)

list(APPEND LFLAGS
	${NOSTD} -T ${CMAKE_CURRENT_SOURCE_DIR}/${LINKERSCRIPT}
)

include(${PROJECT_SOURCE_DIR}/cmake/toolchain_arm_none_eabi.cmake)

