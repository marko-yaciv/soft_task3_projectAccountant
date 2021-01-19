set(BINARY ${CMAKE_PROJECT_NAME}_test)
set(SOURCES main.cpp tests.cpp)

add_executable(${BINARY} ${SOURCES})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

add_test(NAME ${BINARY} COMMAND ${BINARY})