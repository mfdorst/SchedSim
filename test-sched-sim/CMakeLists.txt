cmake_minimum_required(VERSION 3.15)
project(test-sched-sim)

set(CMAKE_CXX_STANDARD 11)

add_executable(test-sched-sim test.cpp)
add_dependencies(test-sched-sim sched-sim)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_cases/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_cases/)
