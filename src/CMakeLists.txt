set(TARGET lib_biginteger)

file(GLOB PROJECT_SOURCES *.cpp)

add_library(${TARGET} ${PROJECT_SOURCES})
