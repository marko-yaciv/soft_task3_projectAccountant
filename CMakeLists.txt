cmake_minimum_required(VERSION 3.15)
project(projectAccountant)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(sources)
add_subdirectory(tests)
add_subdirectory(gtest_lib/googletest)
