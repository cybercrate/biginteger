file(GLOB PROJECT_SOURCES "*.cpp")

add_executable("${PROJECT_NAME}_test" ${PROJECT_SOURCES})

target_link_libraries("${PROJECT_NAME}_test" PRIVATE GTest::gtest_main ${PROJECT_NAME})

enable_testing()
add_test(NAME "${PROJECT_NAME}_test" COMMAND "${PROJECT_NAME}_test")
