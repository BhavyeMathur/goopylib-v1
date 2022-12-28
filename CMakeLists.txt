cmake_minimum_required(VERSION 3.22)
project(goopylib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/..)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_compile_definitions(GP_DIRECTORY="${PROJECT_BINARY_DIR}/../src/")

set(SOURCE_FILES
    src/goopylib/core/Core.cpp
    src/goopylib/core/BufferLayout.cpp

    src/goopylib/debug/Log.cpp
    src/goopylib/debug/Error.cpp

    src/goopylib/maths/Easing.cpp
    src/goopylib/maths/gpmath.cpp

    src/goopylib/color/Color.cpp
    src/goopylib/color/ColorConversions.cpp
    src/goopylib/color/Util.cpp
    src/goopylib/color/W3CX11.cpp

    src/goopylib/objects/Renderable.cpp
    src/goopylib/objects/Line.cpp
    src/goopylib/objects/Triangle.cpp
    src/goopylib/objects/Quad.cpp
    src/goopylib/objects/Ellipse.cpp
    src/goopylib/objects/Circle.cpp
    src/goopylib/objects/Image.cpp

    src/goopylib/scene/Renderer.cpp
    src/goopylib/scene/Camera.cpp
    src/goopylib/scene/CameraController.cpp

    src/platform/GLFW/Window.cpp
    src/platform/OpenGL/Buffer.cpp
    src/platform/OpenGL/VertexArray.cpp
    src/platform/OpenGL/Shader.cpp
    src/platform/OpenGL/Texture2D.cpp

    src/platform/Independent/Window.cpp
    src/platform/Independent/Buffer.cpp
    src/platform/Independent/VertexArray.cpp
    src/platform/Independent/Shader.cpp

    src/vendor/stb/stb_image.cpp)

include_directories(src)
include_directories(src/vendor)

find_package(OpenGL REQUIRED)
add_library(goopylib SHARED ${SOURCE_FILES})
target_link_libraries(goopylib ${PROJECT_BINARY_DIR}/../src/vendor/GLFW/libglfw.3.3.dylib)

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
add_executable(gridlines examples/cpp/objects/gridlines.cpp)
add_executable(minecraft examples/important/minecraft/minecraft.cpp)

target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(core ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(window_states ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(window_callbacks ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(gridlines ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
target_link_libraries(minecraft ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)

set_target_properties(minecraft PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../examples/important/minecraft)
