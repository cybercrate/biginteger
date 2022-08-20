cmake_minimum_required(VERSION 3.20)
set(TARGET biginteger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES "*.cpp")

add_library(${TARGET} ${PROJECT_SOURCES})
target_include_directories(${TARGET} PUBLIC "../include")
