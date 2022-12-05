cmake_minimum_required(VERSION 3.22)
project(goopylib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(GOOPYLIB_PATH goopylib/src/goopylib/)
set(PLATFORM_PATH goopylib/src/Platform/)
set(SOURCE_FILES
        ${GOOPYLIB_PATH}/Core/Base.cpp
        ${GOOPYLIB_PATH}/Core/Log.cpp
        ${PLATFORM_PATH}/GLFW/Window.cpp
        ${GOOPYLIB_PATH}/Math/Easing.cpp
        ${PLATFORM_PATH}/Independent/BaseWindow.cpp)

set(HEADER_FILES
        ${GOOPYLIB_PATH}/Core/Base.h
        ${GOOPYLIB_PATH}/Core/Log.h
        ${GOOPYLIB_PATH}/Core/Window.h
        ${GOOPYLIB_PATH}/Math/Easing.h
        ${GOOPYLIB_PATH}/Math/gpmath.h
        ${PLATFORM_PATH}/Independent/BaseWindow.h)

add_library(goopylib ${SOURCE_FILES})

option(INCLUDE_PYTHON "Includes the Python header files" OFF)
if (INCLUDE_PYTHON)
    find_package(PythonLibs REQUIRED)
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(goopylib ${PYTHON_LIBRARIES})

    include_directories(goopylib/src)
    include_directories(goopylib/vendor)
endif()
unset(INCLUDE_PYTHON)

include_directories(goopylib)
add_executable(main main.cpp)

find_package(OpenGL REQUIRED)
target_include_directories(main SYSTEM PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(main ${OPENGL_gl_LIBRARY})

target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/goopylib.a)
target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/vendor/GLFW/libglfw.3.3.dylib)

add_executable(empty empty.cpp)
