project(ColorTests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/vendor/googletest/googletest/include)

add_executable(ColorTests color.cpp)
target_link_libraries(ColorTests goopylib)
target_link_libraries(ColorTests gtest gtest_main)
