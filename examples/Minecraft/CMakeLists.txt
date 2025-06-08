project(Minecraft)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Minecraft main.cpp)
target_link_libraries(Minecraft goopylib)
