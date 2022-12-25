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

option(INCLUDE_PYTHON "Includes the Python header files" true)
option(DYNAMIC_LIBRARY "Dynamic vs Static Library" true)

# add_executable(main main.cpp)
add_executable(main examples/cpp/core.cpp)
add_executable(empty empty.cpp)

if (DYNAMIC_LIBRARY)
    add_library(goopylib SHARED ${SOURCE_FILES})
    target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/goopylib.dylib)
else ()
    add_library(goopylib STATIC ${SOURCE_FILES})
    target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/goopylib.a)
endif ()

if (APPLE)
    target_link_libraries(goopylib "-framework OpenGL")
endif ()

target_link_libraries(goopylib ${PROJECT_BINARY_DIR}/../goopylib/vendor/GLFW/libglfw.3.3.dylib)
target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/vendor/GLFW/libglfw.3.3.dylib)
target_link_libraries(main ${OPENGL_gl_LIBRARY})

target_include_directories(main SYSTEM PRIVATE ${OPENGL_INCLUDE_DIR})

if (INCLUDE_PYTHON)
    find_package(PythonLibs REQUIRED)
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(goopylib ${PYTHON_LIBRARIES})
endif ()
