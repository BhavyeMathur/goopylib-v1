project(RectanglePacking)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(RectanglePacking main.cpp)
target_link_libraries(RectanglePacking goopylib)
