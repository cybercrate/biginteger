cmake_minimum_required(VERSION 3.20)
set(TARGET biginteger_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES "*.cpp")

add_executable(${TARGET} ${PROJECT_SOURCES})

target_link_libraries(${TARGET} PUBLIC
    gtest_main
    biginteger)

enable_testing()
add_test(NAME ${TARGET} COMMAND ${TARGET})
