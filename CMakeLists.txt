cmake_minimum_required(VERSION 3.22)
project(goopylib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -Wno-deprecated-volatile)
set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_CXX_FLAGS_RELEASE -O3)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

find_package(OpenGL REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(goopylib/)
include_directories(goopylib/src)
include_directories(goopylib/src/vendor)
include_directories(${PYTHON_INCLUDE_DIRS})

set(SOURCE_FILES
    goopylib/src/goopylib/core/Core.cpp
    goopylib/src/goopylib/core/BufferLayout.cpp

    goopylib/src/goopylib/debug/Log.cpp

    goopylib/src/goopylib/maths/Easing.cpp
    goopylib/src/goopylib/maths/gpmath.cpp

    goopylib/src/goopylib/color/Color.cpp
    goopylib/src/goopylib/color/ColorConversions.cpp
    goopylib/src/goopylib/color/Util.cpp
    goopylib/src/goopylib/color/W3CX11.cpp

    goopylib/src/goopylib/objects/Renderable.cpp
    goopylib/src/goopylib/objects/Line.cpp
    goopylib/src/goopylib/objects/Triangle.cpp
    goopylib/src/goopylib/objects/Quad.cpp
    goopylib/src/goopylib/objects/Ellipse.cpp
    goopylib/src/goopylib/objects/Circle.cpp
    goopylib/src/goopylib/objects/Image.cpp

    goopylib/src/goopylib/scene/Renderer.cpp
    goopylib/src/goopylib/scene/Camera.cpp
    goopylib/src/goopylib/scene/CameraController.cpp

    goopylib/src/platform/GLFW/Window.cpp
    goopylib/src/platform/OpenGL/Buffer.cpp
    goopylib/src/platform/OpenGL/VertexArray.cpp
    goopylib/src/platform/OpenGL/Shader.cpp
    goopylib/src/platform/OpenGL/Texture2D.cpp

    goopylib/src/goopylib/core/Window.cpp
    goopylib/src/goopylib/core/Buffer.cpp
    goopylib/src/goopylib/core/VertexArray.cpp
    goopylib/src/goopylib/shader/Shader.cpp

    goopylib/src/vendor/stb/stb_image.cpp)

add_library(goopylib SHARED ${SOURCE_FILES})
target_link_libraries(goopylib ${CMAKE_SOURCE_DIR}/goopylib/src/vendor/GLFW/libglfw.3.3.dylib)

if (APPLE)
    target_link_libraries(goopylib "-framework OpenGL")
endif ()


# Client Programs
add_executable(main main.cpp)
add_executable(empty empty.cpp)
add_executable(core examples/mini/cpp/core.cpp)
add_executable(window_states examples/mini/cpp/window/window_states.cpp)
add_executable(window_callbacks examples/mini/cpp/window/window_callbacks.cpp)
add_executable(gridlines examples/mini/cpp/objects/gridlines.cpp)
add_executable(minecraft examples/minecraft/minecraft.cpp)
add_executable(brick_breaker "examples/brick breaker/brick_breaker.cpp")

target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(core ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(window_states ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(window_callbacks ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(gridlines ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(minecraft ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(brick_breaker ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)

set_target_properties(minecraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../examples/minecraft)
set_target_properties(brick_breaker PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/../examples/brick breaker")
