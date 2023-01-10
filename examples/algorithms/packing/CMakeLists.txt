project(PackingAlgorithms)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PackingAlgorithms main.cpp)
target_link_libraries(PackingAlgorithms goopylib)
