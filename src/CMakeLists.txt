file(GLOB PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})

add_custom_target(copy_binaries
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.lib"
        "${CMAKE_SOURCE_DIR}/bin"

    # Output message
    COMMENT "Copying binaries from '${CMAKE_CURRENT_BINARY_DIR}' to '${CMAKE_SOURCE_DIR}/bin'" VERBATIM)

add_dependencies(${PROJECT_NAME} copy_binaries)
