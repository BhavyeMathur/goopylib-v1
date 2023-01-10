project(BrickBreaker)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(BrickBreaker main.cpp)
target_link_libraries(BrickBreaker goopylib)
