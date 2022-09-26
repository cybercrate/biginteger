project(biginteger_test)

file(GLOB PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIRS})

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
