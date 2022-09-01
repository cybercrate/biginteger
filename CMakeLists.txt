cmake_minimum_required(VERSION 3.20)
project(biginteger VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib")
list(APPEND PROJECT_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})

if(CMAKE_BUILD_TYPE MATCHES "Test")
    find_package(GTest COMPONENTS gtest_main REQUIRED)

    add_subdirectory(test)

    if(GTest_FOUND)
        target_include_directories("${PROJECT_NAME}_test" PRIVATE ${GTest_INCLUDE_DIRS})
        target_link_libraries("${PROJECT_NAME}_test" PRIVATE GTest::gtest_main ${PROJECT_NAME})
    endif()
endif()
