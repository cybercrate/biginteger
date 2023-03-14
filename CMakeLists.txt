cmake_minimum_required(VERSION 3.20)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{HOMEPATH}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
else()
    set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project(biginteger VERSION 1.0.0 LANGUAGES CXX)

if (MSVC)
    set(CMAKE_CXX_FLAGS "/std:c++20")
else()
    set(CMAKE_CXX_FLAGS "-std=c++20 -Werror -Wall -Wextra -Wpedantic")
endif()

set(ALEF_INCLUDE_PATH
    "${CMAKE_SOURCE_DIR}/lib/alef/include"
    "${CMAKE_SOURCE_DIR}/lib/concepts/include"
    "${CMAKE_SOURCE_DIR}/lib/cast/include"
    "${CMAKE_SOURCE_DIR}/include")

set(PROJECT_INCLUDE_DIRS ${ALEF_INCLUDE_PATH})

find_package(GTest CONFIG REQUIRED)

add_subdirectory(test)
