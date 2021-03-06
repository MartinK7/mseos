set(TARGET kernel)

################################################################################
##                            PLATFORM SOURCES                                ##
################################################################################

set(LINKERSCRIPT platform/stm32f429_discovery/linkerscript.ld)

list(APPEND CFLAGS
	-mthumb -mcpu=cortex-m4
)

list(APPEND DEFINES
	STM32F429xx
)

list(APPEND SOURCES
	platform/stm32f429_discovery/head.s
	platform/stm32f429_discovery/platform.c
)

list(APPEND INCLUDES
	platform/stm32f429_discovery
	include/cpu/arm/device/st/stm32f4xx
)

################################################################################
##                              ARCH SOURCES                                  ##
################################################################################

# PLATFORM
list(APPEND INCLUDES
	include/cpu/arm/cmsis
)

################################################################################
##                   KERNEL COMMON SOURCES AND INCLUDES                       ##
################################################################################

list(APPEND SOURCES
	mseos/kernel.c
	mseos/boot.c
	mseos/sys/tick.c
	mseos/sys/kheap.c
	mseos/sys/scheduler.c
	mseos/sys/memops.c
)

list(APPEND INCLUDES
	include
	mseos
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
