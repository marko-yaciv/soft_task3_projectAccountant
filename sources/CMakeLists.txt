#set(Boost_USE_STATIC_LIBS OFF)

set(SOURCES main.cpp FilesKeeper.cpp FileAnalyser.cpp CodeParser.cpp InfoKeeper.cpp utils.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})


