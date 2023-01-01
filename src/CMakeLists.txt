cmake_minimum_required(VERSION 3.22)
project(goopylib)

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES arm64;x86_64)
    set(MACOSX_DEPLOYMENT_TARGET 10.9)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_CXX_FLAGS_RELEASE -O3)
set(CMAKE_CXX_FLAGS -Wno-deprecated-volatile)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(OpenGL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/vendor)

link_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW)

add_library(goopylib SHARED
            src/goopylib/core/Core.cpp
            src/goopylib/core/BufferLayout.cpp

            src/goopylib/debug/Log.cpp

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

            src/goopylib/core/Window.cpp
            src/goopylib/core/Buffer.cpp
            src/goopylib/core/VertexArray.cpp
            src/goopylib/shader/Shader.cpp

            src/vendor/stb/stb_image.cpp)

target_link_libraries(goopylib -lglfw.3)

if (APPLE)
    target_link_libraries(goopylib "-framework OpenGL")
endif ()

add_executable(empty empty.cpp)

add_executable(main main.cpp)
target_link_libraries(main -lgoopylib)
