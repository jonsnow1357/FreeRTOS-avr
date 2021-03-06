##################################################################################
# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann
##################################################################################

##################################################################################
# Sample CMakeLists.txt for a simple AVR project based on the toolchain
##################################################################################

cmake_minimum_required(VERSION 2.8)

### TOOLCHAIN SETUP AREA #################################################
# Set any variables used in the toolchain prior project() call. In that
# case they are already set and used.
##########################################################################

##################################################################################
# tools to be used for programming the AVR
##################################################################################
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/avr.cmake)
set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER avrispmkII)
set(AVR_UPLOADTOOL_PORT usb)
# AVR and fuses needs to be set
#set(AVR_MCU atmega8)
#set(AVR_H_FUSE 0xd9)
#set(AVR_L_FUSE 0xc3)
set(CMAKE_VERBOSE_MAKEFILE ON)

### END TOOLCHAIN SETUP AREA #############################################

##########################################################################
# name your project
##########################################################################
project(freertos-test)

##################################################################################
# status messages
##################################################################################
message(STATUS "Current uploadtool is: ${AVR_UPLOADTOOL}")
message(STATUS "Current programmer is: ${AVR_PROGRAMMER}")
message(STATUS "Current upload port is: ${AVR_UPLOADTOOL_PORT}")
message(STATUS "Current uploadtool options are: ${AVR_UPLOADTOOL_OPTIONS}")
message(STATUS "Current MCU is set to: ${AVR_MCU}")
message(STATUS "Current H_FUSE is set to: ${AVR_H_FUSE}")
message(STATUS "Current L_FUSE is set to: ${AVR_L_FUSE}")

##################################################################################
# set build type, if not already set at cmake command line
##################################################################################
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

##################################################################################
# needs to be defined for AVR toolchain
##################################################################################
set(MCU_SPEED "4000000UL")

##################################################################################
# some cmake cross-compile necessities
##################################################################################
if(DEFINED ENV{AVR_FIND_ROOT_PATH})
    set(CMAKE_FIND_ROOT_PATH $ENV{AVR_FIND_ROOT_PATH})
else(DEFINED ENV{AVR_FIND_ROOT_PATH})
    if(EXISTS "/opt/local/avr")
      set(CMAKE_FIND_ROOT_PATH "/opt/local/avr")
    elseif(EXISTS "/usr/avr")
      set(CMAKE_FIND_ROOT_PATH "/usr/avr")
    elseif(EXISTS "/usr/lib/avr")
      set(CMAKE_FIND_ROOT_PATH "/usr/lib/avr")
    elseif(EXISTS "/usr/local/CrossPack-AVR")
      set(CMAKE_FIND_ROOT_PATH "/usr/local/CrossPack-AVR")
    else(EXISTS "/opt/local/avr")
      message(FATAL_ERROR "Please set AVR_FIND_ROOT_PATH in your environment.")
    endif(EXISTS "/opt/local/avr")
endif(DEFINED ENV{AVR_FIND_ROOT_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# not added automatically, since CMAKE_SYSTEM_NAME is "generic"
set(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
set(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")

##################################################################################
# status messages for generating
##################################################################################
message(STATUS "Set CMAKE_FIND_ROOT_PATH to ${CMAKE_FIND_ROOT_PATH}")
message(STATUS "Set CMAKE_SYSTEM_INCLUDE_PATH to ${CMAKE_SYSTEM_INCLUDE_PATH}")
message(STATUS "Set CMAKE_SYSTEM_LIBRARY_PATH to ${CMAKE_SYSTEM_LIBRARY_PATH}")

##################################################################################
# set compiler options for build types
##################################################################################
if(CMAKE_BUILD_TYPE MATCHES Release)
   set(CMAKE_C_FLAGS_RELEASE "-Os")
   set(CMAKE_CXX_FLAGS_RELEASE "-Os")
endif(CMAKE_BUILD_TYPE MATCHES Release)

if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
   set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
   set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
endif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

if(CMAKE_BUILD_TYPE MATCHES Debug)
   set(CMAKE_C_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
   set(CMAKE_CXX_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

##################################################################################
# compiler options for all build types
##################################################################################
add_definitions("-DF_CPU=${MCU_SPEED}")
add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
#add_definitions("-Werror")
# http://gcc.gnu.org/onlinedocs/gcc-4.8.2/gcc/Alternate-Keywords.html#Alternate-Keywords
# [...]-pedantic and other options cause warnings for many GNU C extensions. You can prevent such warnings within
# one expression by writing __extension__ before the expression. __extension__ has no effect aside from this.[...] 
add_definitions("-pedantic")
#add_definitions("-pedantic-errors")
add_definitions("-funsigned-char")
add_definitions("-funsigned-bitfields")
add_definitions("-ffunction-sections")
add_definitions("-c")
add_definitions("-std=gnu99")

set(FR_ROOT "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel")
message(STATUS "FreeRTOS root     : " ${FR_ROOT})
set(FR_SRC ${FR_ROOT})
message(STATUS "FreeRTOS sources  : " ${FR_ROOT})
set(FR_SRC_INC "${FR_ROOT}/include")
message(STATUS "FreeRTOS include  : " ${FR_SRC_INC})
set(FR_SRC_PORT "${FR_ROOT}/portable")
message(STATUS "FreeRTOS portable : " ${FR_SRC_PORT})

if(AVR_FR_OPT STREQUAL "old")
    set(FR_SRC_ATMega "${FR_SRC_PORT}/GCC/ATMega323")
    message(STATUS "FreeRTOS ATMega   : " ${FR_SRC_ATMega323})
elseif(AVR_FR_OPT STREQUAL "new")
    set(FR_SRC_ATMega "${FR_SRC_PORT}/ThirdParty/GCC/ATmega")
    message(STATUS "FreeRTOS ATMega   : " ${FR_SRC_ATMega})
else()
    message(FATAL_ERROR "AVR_FR_OPT not set (values: [old|new])")
endif()
#set(FR_SRC_AVR32_UC3 "${FR_ROOT}/portable/GCC/AVR32_UC3")
#message(STATUS "FreeRTOS AVR32_UC3: " ${FR_SRC_AVR32_UC3})
#set(FR_SRC_AVR_AVRDx "${FR_ROOT}/portable/GCC/AVR_AVRDx")
#message(STATUS "FreeRTOS AVR_AVRDx: " ${FR_SRC_AVR_AVRDx})
#set(FR_SRC_AVR_Mega0 "${FR_ROOT}/portable/GCC/AVR_Mega0")
#message(STATUS "FreeRTOS AVR_Mega0: " ${FR_SRC_AVR_Mega0})

set(LST_C ${FR_SRC}/list.c ${FR_SRC}/queue.c ${FR_SRC}/tasks.c ${FR_SRC}/timers.c)
list(APPEND LST_C ${FR_SRC_PORT}/MemMang/heap_1.c)
list( APPEND LST_C ${FR_SRC_ATMega}/port.c )
list( APPEND LST_C main.c)
#message("LST_C: ${LST_C}")
##################################################################################
# add AVR executable
##################################################################################
#add_avr_executable(
#   <executable-name>
#   <sources> <headers>
#)
include_directories(. ${FR_SRC_INC})
include_directories(${FR_SRC_ATMega})

add_avr_executable(${PROJECT_NAME} ${LST_C})
##################################################################################
# add AVR library
##################################################################################
#add_avr_library(
#   <library-name>
#   <sources> <headers>
#)

##################################################################################
# link library to executable
# NOTE: It needs to be the elf target.
##################################################################################
# target_link_libraries(<executable-name>-${AVR_MCU}.elf <library-name>-${AVR_MCU})
# OR easier
#target_link_libraries(<executable-name> <library-name> <some-external-libary>)

