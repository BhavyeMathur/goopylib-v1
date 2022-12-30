#pragma once

#include <memory>
#include <string>

#define _GP_BUILD_DLL

#if defined(_WIN32) && defined(_GP_BUILD_DLL)
/* We are building goopylib as a Win32 DLL */
#define GPAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(GP_DLL)
/* We are calling a goopylib Win32 DLL */
#define GPAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(_GP_BUILD_DLL)
/* We are building GP as a Unix shared library */
#define GPAPI __attribute__((visibility("default")))
#else
#define GPAPI
#endif

#define GL_SILENCE_DEPRECATION
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

// Smart Pointers
namespace gp {
    template<typename T>
        using Scope = std::unique_ptr<T>;

    template<typename T>
        using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
        constexpr Ref<T> CreateRef(Args &&... args) {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
}

namespace gp {
    template<typename ... Args>
        std::string strformat(const std::string &format, Args ... args) {
            int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
            if (size_s <= 0) {
                throw std::runtime_error("Error during string formatting");
            }
            auto size = static_cast<size_t>( size_s );
            std::unique_ptr<char[]> buf(new char[size]);
            std::snprintf(buf.get(), size, format.c_str(), args ...);
            return {buf.get(), buf.get() + size - 1}; // We don't want the '\0' inside
        }
}

#include "config.h"
#include "goopylib/debug/Log.h"
