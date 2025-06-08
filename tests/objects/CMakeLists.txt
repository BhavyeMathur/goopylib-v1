project(gridlines.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(gridlines gridlines.cpp)
target_link_libraries(gridlines goopylib)
