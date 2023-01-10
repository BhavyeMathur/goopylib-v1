cmake_minimum_required(VERSION 3.22)
project(BrickBreaker)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_executable(BrickBreaker brick_breaker.cpp)
target_link_libraries(BrickBreaker goopylib)
