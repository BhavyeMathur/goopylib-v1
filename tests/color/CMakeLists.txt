project(color_tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/vendor/googletest/googletest/include)

add_executable(color_tests
               color.cpp rgb.cpp hex.cpp cmyk.cpp)

target_link_libraries(color_tests goopylib)
target_link_libraries(color_tests gtest gtest_main)
