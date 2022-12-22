cmake_minimum_required(VERSION 3.22)
project(goopylib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../goopylib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/..)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_compile_definitions(GP_DIRECTORY="${PROJECT_BINARY_DIR}/../goopylib/src/")

# Precompiled Header File
#add_library(pch STATIC goopylib/src/pch.cpp goopylib/src/pch.h)
#add_custom_command(TARGET pch
#                   PRE_BUILD COMMAND ${CMAKE_CXX_COMMAND} -x c++-header goopylib/src/pch.h -o goopylib/src/pch.h.pch)
#set_source_files_properties(goopylib/src/pch.cpp PROPERTIES COMPILE_FLAGS "-include pch.h")

set(GOOPYLIB_PATH goopylib/src/goopylib/)
set(PLATFORM_PATH goopylib/src/Platform/)
set(SOURCE_FILES
    ${GOOPYLIB_PATH}/Core/Core.cpp
    ${GOOPYLIB_PATH}/Core/BufferLayout.cpp
    ${GOOPYLIB_PATH}/Debug/Log.cpp

    ${GOOPYLIB_PATH}/Math/Easing.cpp

    ${GOOPYLIB_PATH}/Color/Color.cpp
    ${GOOPYLIB_PATH}/Color/ColorConversions.cpp
    ${GOOPYLIB_PATH}/Color/Util.cpp

    ${GOOPYLIB_PATH}/Renderer/Triangle.cpp
    ${GOOPYLIB_PATH}/Renderer/Quad.cpp
    ${GOOPYLIB_PATH}/Renderer/Circle.cpp
    ${GOOPYLIB_PATH}/Renderer/Renderer.cpp
    ${GOOPYLIB_PATH}/Renderer/RenderableObject.cpp

    ${PLATFORM_PATH}/GLFW/Window.cpp
    ${PLATFORM_PATH}/OpenGL/Buffer.cpp
    ${PLATFORM_PATH}/OpenGL/VertexArray.cpp
    ${PLATFORM_PATH}/OpenGL/Shader.cpp

    ${PLATFORM_PATH}/Independent/BaseWindow.cpp
    ${PLATFORM_PATH}/Independent/Buffer.cpp
    ${PLATFORM_PATH}/Independent/VertexArray.cpp
    ${PLATFORM_PATH}/Independent/Shader.cpp)

include_directories(goopylib)
include_directories(goopylib/src)
include_directories(goopylib/vendor)

find_package(OpenGL REQUIRED)

option(INCLUDE_PYTHON "Includes the Python header files" true)
option(DYNAMIC_LIBRARY "Dynamic vs Static Library" true)

add_executable(main main.cpp)
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

#target_link_libraries(goopylib pch)

target_link_libraries(goopylib ${PROJECT_BINARY_DIR}/../goopylib/vendor/GLFW/libglfw.3.3.dylib)
target_link_libraries(main ${CMAKE_SOURCE_DIR}/goopylib/vendor/GLFW/libglfw.3.3.dylib)
target_link_libraries(main ${OPENGL_gl_LIBRARY})

target_include_directories(main SYSTEM PRIVATE ${OPENGL_INCLUDE_DIR})

if (INCLUDE_PYTHON)
    find_package(PythonLibs REQUIRED)
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(goopylib ${PYTHON_LIBRARIES})
endif ()
