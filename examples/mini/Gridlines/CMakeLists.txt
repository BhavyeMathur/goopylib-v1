project(Gridlines)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Gridlines main.cpp)
target_link_libraries(Gridlines goopylib)
