project(core_tests)
project(buffer_tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/vendor/googletest/googletest/include)

add_executable(core_tests core.cpp index_buffer.cpp)
add_executable(buffer_tests index_buffer.cpp)

target_link_libraries(${PROJECT_NAME} goopylib)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
