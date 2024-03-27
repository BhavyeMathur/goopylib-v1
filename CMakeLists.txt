cmake_minimum_required(VERSION 3.22)
project(goopylib)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG__)
endif ()

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES arm64;x86_64)
    set(MACOSX_DEPLOYMENT_TARGET 10.9)

    set(CMAKE_CXX_FLAGS_DEBUG -g)
    set(CMAKE_CXX_FLAGS_RELEASE -O3)
    set(CMAKE_CXX_FLAGS "-Wall -Wno-unknown-pragmas")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG /Od)
    set(CMAKE_CXX_FLAGS_RELEASE /O2)
endif ()

if (POLICY CMP0148)
    cmake_policy(SET CMP0148 OLD)
endif ()

find_package(OpenGL REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/vendor)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glm)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glad)
include_directories(${CMAKE_SOURCE_DIR}/vendor/GLFW/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/pybind11/include)

if (WIN32)
    set(WINDOWS_SOURCES vendor/glad/glad.c)

    if (MSVC)
        set(CMAKE_CXX_FLAGS "-wd4068 /EHsc")

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
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-${GOOPYLIB_PLATFORM_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-${GOOPYLIB_PLATFORM_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries/lib-${GOOPYLIB_PLATFORM_NAME})

add_library(goopylib SHARED ${WINDOWS_SOURCES}
            src/core/Core.cpp
            src/core/Buffer.cpp
            src/core/VertexBuffer.cpp
            src/core/IndexBuffer.cpp
            src/core/UniformBuffer.cpp
            src/core/BufferLayout.cpp
            src/core/VertexArray.cpp

            src/debug/Log.cpp
            src/debug/Error.cpp

            src/maths/gpmath.cpp
            src/maths/Easing.cpp
            src/maths/packing/Packing.cpp
            src/maths/packing/Shelf.cpp

            src/color/Color.cpp
            src/color/ColorRGB.cpp
            src/color/ColorHex.cpp
            src/color/ColorCMYK.cpp
            src/color/ColorHSL.cpp
            src/color/ColorHSV.cpp
            src/color/Util.cpp
            src/color/W3CX11.cpp

            src/objects/Renderable.cpp
            src/objects/Triangle.cpp
            src/objects/Ellipse.cpp
            src/objects/Circle.cpp
            src/objects/Quad.cpp
            src/objects/Rectangle.cpp
            src/objects/Line.cpp
            src/objects/TexturedQuad.cpp
            src/objects/TexturedRectangle.cpp
            src/objects/Image.cpp

            src/scene/RenderingManager.cpp
            src/scene/Renderer.cpp
            src/scene/Camera.cpp
            src/scene/CameraController.cpp

            src/texture/Bitmap.cpp
            src/texture/Texture2D.cpp

            src/window/Window.cpp

            src/shader/Shader.cpp

            vendor/stb/stb_image.cpp
            vendor/stb/stb_image_write.cpp)

target_compile_definitions(goopylib PRIVATE GP_BUILD_DLL)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
endif ()

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(vendor/GLFW)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(main main.cpp)
    target_link_libraries(main goopylib)
endif ()

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples/BrickBreaker/CMakeLists.txt")
    add_subdirectory(examples/BrickBreaker)
endif()

add_subdirectory(examples/Minecraft)
add_subdirectory(examples/algorithms/packing)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/CMakeLists.txt")
    add_subdirectory(vendor/googletest)
endif()
add_subdirectory(tests/color)
add_subdirectory(tests/core)
