#pragma once

#include <memory>
#include <string>

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

namespace gp {
    template<typename ... Args>
        std::string strformat(const std::string &format, Args ... args) {
            int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
            if (size_s <= 0) {
                throw std::runtime_error("Error during string formatting");
            }
            auto size = static_cast<size_t>( size_s );
            const Scope<char[]> buf(new char[size]);
            if (std::snprintf(buf.get(), size, format.c_str(), args ...) < 0) {
                throw std::runtime_error("Error during string formatting");
            }
            return {buf.get(), buf.get() + size - 1}; // We don't want the '\0' inside
        }
}

#include "src/config.h"
