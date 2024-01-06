#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

#define GP_BUILD_DLL

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#define __WINDOWS__ true
#define GP_USING_GLAD true
#define or ||
#define and &&

#else

#define __WINDOWS__ false
#define GP_USING_GLAD false

#endif

#if defined(_WIN32) && defined(GP_BUILD_DLL)
/* We are building goopylib as a Win32 DLL */
#define GPAPI __declspec(dllexport)
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

#define Ref std::shared_ptr
#define CreateRef std::make_shared
#define Scope std::unique_ptr
#define CreateScope std::make_unique

#include "src/config.h"
#include "src/goopylib/debug/LogMacros.h"
