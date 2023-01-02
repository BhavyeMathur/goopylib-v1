cmake_minimum_required(VERSION 3.22)
project(goopylib)

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES arm64;x86_64)
    set(MACOSX_DEPLOYMENT_TARGET 10.9)

    set(CMAKE_CXX_FLAGS_DEBUG -g)
    set(CMAKE_CXX_FLAGS_RELEASE -O3)
    set(CMAKE_CXX_FLAGS -Wno-deprecated-volatile)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG /Od)
    set(CMAKE_CXX_FLAGS_RELEASE /O2)
endif ()

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

# needed to silence errors in IDE
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/vendor)

link_directories(${CMAKE_SOURCE_DIR})

if (WIN32)
    set(WINDOWS_SOURCES src/vendor/glad/glad.c main.cpp)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        if (MSVC_TOOLSET_VERSION EQUAL 110)
            link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW/glfw-3.3.8.bin.WIN64/lib-vc2012)

            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2012)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2012)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2012)

        elseif(MSVC_TOOLSET_VERSION EQUAL 120)
            link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW/glfw-3.3.8.bin.WIN64/lib-vc2013)

            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2013)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2013)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2013)

        elseif(MSVC_TOOLSET_VERSION EQUAL 140)
            link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW/glfw-3.3.8.bin.WIN64/lib-vc2015)

            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2015)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2015)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2015)

        elseif(MSVC_TOOLSET_VERSION EQUAL 141)
            link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW/glfw-3.3.8.bin.WIN64/lib-vc2017)

            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2017)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2017)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2017)

        elseif(MSVC_TOOLSET_VERSION EQUAL 142)
            link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW/glfw-3.3.8.bin.WIN64/lib-vc2019)

            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2019)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2019)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2019)

        elseif(MSVC_TOOLSET_VERSION EQUAL 143)
            link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW/glfw-3.3.8.bin.WIN64/lib-vc2022)

            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2022)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2022)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-vc2022)

        endif()
    else ()
        link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW/glfw-3.3.8.bin.WIN64/lib-mingw-w64)

        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-mingw-64)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-mingw-64)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-mingw-64)

    endif ()

elseif (APPLE)
    link_directories(${CMAKE_SOURCE_DIR}/src/vendor/GLFW)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-macos)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-macos)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-macos)
endif()

add_library(goopylib SHARED ${WINDOWS_SOURCES}
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

if (APPLE)
    target_link_libraries(goopylib glfw.3)
else ()
    target_link_libraries(goopylib glfw3)
endif ()

if (APPLE)
    target_link_libraries(goopylib "-framework OpenGL")
endif ()

add_executable(main main.cpp)
target_link_libraries(main goopylib)
