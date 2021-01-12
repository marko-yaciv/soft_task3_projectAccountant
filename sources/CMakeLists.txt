set(SOURCES main.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})