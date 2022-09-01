file(GLOB PROJECT_SOURCES "*.cpp")

add_executable("${PROJECT_NAME}_test" ${PROJECT_SOURCES})

enable_testing()
add_test(NAME "${PROJECT_NAME}_test" COMMAND "${PROJECT_NAME}_test")
