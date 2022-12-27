cmake_minimum_required(VERSION 3.22)
project(goopylib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/..)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_compile_definitions(GP_DIRECTORY="${PROJECT_BINARY_DIR}/../goopylib/src/")

set(SOURCE_FILES
    goopylib/src/goopylib/core/Core.cpp
    goopylib/src/goopylib/core/BufferLayout.cpp

    goopylib/src/goopylib/debug/Log.cpp
    goopylib/src/goopylib/debug/Error.cpp

    goopylib/src/goopylib/math/Easing.cpp
    goopylib/src/goopylib/math/gpmath.cpp

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

    goopylib/src/platform/Independent/Window.cpp
    goopylib/src/platform/Independent/Buffer.cpp
    goopylib/src/platform/Independent/VertexArray.cpp
    goopylib/src/platform/Independent/Shader.cpp

    goopylib/vendor/stb/stb_image.cpp)

include_directories(goopylib)
include_directories(goopylib/src)
include_directories(goopylib/vendor)

find_package(OpenGL REQUIRED)
add_library(goopylib SHARED ${SOURCE_FILES})
target_link_libraries(goopylib ${PROJECT_BINARY_DIR}/../goopylib/vendor/GLFW/libglfw.3.3.dylib)

if (APPLE)
    target_link_libraries(goopylib "-framework OpenGL")
endif ()

option(INCLUDE_PYTHON "Includes the Python header files" true)
if (INCLUDE_PYTHON)
    find_package(PythonLibs REQUIRED)
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(goopylib ${PYTHON_LIBRARIES})
endif ()

# Client Programs
add_executable(main main.cpp)
add_executable(empty empty.cpp)
add_executable(core examples/cpp/core.cpp)
add_executable(window_states examples/cpp/window/window_states.cpp)
add_executable(window_callbacks examples/cpp/window/window_callbacks.cpp)

target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(core ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(window_states ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(window_callbacks ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
