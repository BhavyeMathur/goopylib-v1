cmake_minimum_required(VERSION 3.22)
project(goopylib)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG__)
endif ()

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES arm64;x86_64)
    set(MACOSX_DEPLOYMENT_TARGET 10.9)

    set(CMAKE_CXX_FLAGS_DEBUG -g)
    set(CMAKE_CXX_FLAGS_RELEASE -O3)
    set(CMAKE_CXX_FLAGS -Wno-c++17-extensions)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
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

include_directories(${CMAKE_SOURCE_DIR}/vendor)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glm)
include_directories(${CMAKE_SOURCE_DIR}/vendor/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/GLFW/include)

add_library(goopylib SHARED ${WINDOWS_SOURCES}
            src/goopylib/core/Core.cpp
            src/goopylib/core/BufferLayout.cpp

            src/goopylib/debug/Log.cpp

            src/goopylib/maths/gpmath.cpp
            src/goopylib/maths/Easing.cpp
            src/goopylib/maths/packing/Packing.cpp
            src/goopylib/maths/packing/Shelf.cpp

            src/goopylib/color/Color.cpp
            src/goopylib/color/ColorConversions.cpp
            src/goopylib/color/Util.cpp
            src/goopylib/color/W3CX11.cpp

            src/goopylib/objects/Renderable.cpp
            src/goopylib/objects/Line.cpp
            src/platform/OpenGL/Line.cpp
            src/goopylib/objects/Triangle.cpp
            src/goopylib/objects/Quad.cpp
            src/goopylib/objects/TexturedQuad.cpp
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
            src/platform/OpenGL/TextureAtlas.cpp
            src/goopylib/texture/TextureAtlas.cpp
            src/goopylib/texture/Bitmap.cpp
            src/goopylib/texture/Texture2D.cpp

            src/goopylib/core/Window.cpp
            src/goopylib/core/Buffer.cpp
            src/goopylib/core/VertexArray.cpp
            src/goopylib/shader/Shader.cpp

            vendor/stb/stb_image.cpp
            vendor/stb/stb_image_write.cpp)

if (WIN32)
    set(WINDOWS_SOURCES vendor/glad/glad.c)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        if (MSVC_TOOLSET_VERSION EQUAL 110)
            set(GOOPYLIB_PLATFORM_NAME vc2012)
        elseif (MSVC_TOOLSET_VERSION EQUAL 120)
            set(GOOPYLIB_PLATFORM_NAME vc2013)
        elseif (MSVC_TOOLSET_VERSION EQUAL 140)
            set(GOOPYLIB_PLATFORM_NAME vc2015)
        elseif (MSVC_TOOLSET_VERSION EQUAL 141)
            set(GOOPYLIB_PLATFORM_NAME vc2017)
        elseif (MSVC_TOOLSET_VERSION EQUAL 142)
            set(GOOPYLIB_PLATFORM_NAME vc2019)
        elseif (MSVC_TOOLSET_VERSION EQUAL 143)
            set(GOOPYLIB_PLATFORM_NAME vc2022)
        endif ()
    else ()
        set(GOOPYLIB_PLATFORM_NAME mingw-64)
    endif ()
elseif (APPLE)
    set(GOOPYLIB_PLATFORM_NAME macos)

    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-${GOOPYLIB_PLATFORM_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-${GOOPYLIB_PLATFORM_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-${GOOPYLIB_PLATFORM_NAME})

set(GLFW_DIR vendor/GLFW)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

add_executable(main main.cpp)
target_link_libraries(main goopylib)

add_subdirectory(examples/BrickBreaker)
add_subdirectory(examples/Minecraft)
add_subdirectory(examples/algorithms/packing)
