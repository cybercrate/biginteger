cmake_minimum_required(VERSION 3.20)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{HOMEPATH}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
else()
    set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project(biginteger VERSION 1.0.0 LANGUAGES CXX)

list(APPEND CMAKE_CXX_FLAGS "-std=c++20 -Wall -Werror -Wpessimizing-move")

set(PROJECT_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")

find_package(GTest CONFIGS REQUIRED)

add_subdirectory(test)
