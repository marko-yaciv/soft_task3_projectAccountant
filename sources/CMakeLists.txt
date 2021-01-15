#set(Boost_USE_STATIC_LIBS OFF)

set(SOURCES main.cpp FilesKeeper.cpp FileAnalyser.cpp CodeParser.cpp CodeParser.h)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

#find_package(Boost REQUIRED COMPONENTS json)
#include_directories(${Boost_INCLUDE_DIR})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
