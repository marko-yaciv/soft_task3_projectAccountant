#set(Boost_USE_STATIC_LIBS OFF)

set(SOURCES main.cpp FilesKeeper.cpp FileAnalyser.cpp CodeParser.cpp InfoKeeper.cpp utils.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

find_package(Boost COMPONENTS json filesystem system REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} Boost::json
                                            Boost::filesystem
                                            Boost::system)
if(MINGW)
    target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)
endif()