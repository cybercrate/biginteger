file(GLOB PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_library("${PROJECT_NAME}_debug" STATIC ${PROJECT_SOURCES})
    target_include_directories("${PROJECT_NAME}_debug" PUBLIC ${PROJECT_INCLUDE_DIRS})

    add_custom_command(TARGET "${PROJECT_NAME}_debug"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin"

        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_debug.lib"
        "${CMAKE_SOURCE_DIR}/bin"
    )
else()
    add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})

    add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin"

        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.lib"
        "${CMAKE_SOURCE_DIR}/bin"
    )
endif()
