cmake_minimum_required(VERSION 3.0)
project(demo-sequences)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(BUILD_DIR ${CMAKE_BINARY_DIR})
set(GCC_ARM_PATH /usr/local/gcc-arm/bin/)
set(FIRMWARE_DIR /usr/local/src/particle/firmware)

if (NOT PLATFORM)
    set(PLATFORM photon)
endif ()
message(STATUS "Building firmware for the ${PLATFORM} platform.")
include(${PLATFORM})

configure_file(common/flash.in ${CMAKE_BINARY_DIR}/flash)

include(particle)
add_particle_remote_app(firmware)
