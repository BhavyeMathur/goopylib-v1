#pragma once

#include <memory>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#define GP_USING_GLAD true
#define GP_BUILDING_WINDOWS true
#define or ||
#define and &&

#elif defined(__linux__) || defined(__gnu_linux__)

#define GP_USING_GLAD true
#define GP_BUILDING_WINDOWS false

#else

#define GP_USING_GLAD false
#define GP_BUILDING_WINDOWS false

#endif

#if defined(_WIN32)
/* We are building goopylib as a Win32 DLL */
#if defined(GP_BUILD_DLL)
#define GPAPI __declspec(dllexport)
#else
#define GPAPI __declspec(dllimport)
#endif

#elif defined(_WIN32) && defined(GP_DLL)
/* We are calling a goopylib Win32 DLL */
#define GPAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(GP_BUILD_DLL)
/* We are building GP as a Unix shared library */
#define GPAPI __attribute__((visibility("default")))
#else
#define GPAPI
#endif

#define GL_SILENCE_DEPRECATION
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

namespace gp {
    using std::make_unique, std::make_shared, std::shared_ptr, std::unique_ptr;
}

#include "src/config.h"
#include "debug/Log.h"

#define GP_DRAW_MODE_TRIANGLES 0x0004
#define GP_DRAW_MODE_LINES 0x0001
