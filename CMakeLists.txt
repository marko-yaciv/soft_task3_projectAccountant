cmake_minimum_required(VERSION 3.15)
project(projectAccountant)
set(CMAKE_CXX_STANDARD 17)

option(MINGW_STDTHREADS_GENERATE_STDHEADERS "" ON)
add_subdirectory(sources)
add_subdirectory(tests)
add_subdirectory(gtest_lib/googletest)
add_subdirectory(mingw-std-threads)

target_link_libraries(${CMAKE_PROJECT_NAME} mingw_stdthreads)
target_link_libraries(${CMAKE_PROJECT_NAME} stdc++fs)