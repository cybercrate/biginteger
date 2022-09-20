file(GLOB PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable("${PROJECT_NAME}_test" ${PROJECT_SOURCES})

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_link_libraries("${PROJECT_NAME}_test" PRIVATE
        GTest::gtest_main
        "${PROJECT_NAME}_debug"
    )
else()
    target_link_libraries("${PROJECT_NAME}_test" PRIVATE
        GTest::gtest_main
        ${PROJECT_NAME}
    )
endif()

enable_testing()
add_test(NAME "${PROJECT_NAME}_test" COMMAND "${PROJECT_NAME}_test")
