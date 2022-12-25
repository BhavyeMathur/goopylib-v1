#pragma once

#define GP_USING_GLFW true
#define GP_USING_OPENGL true
#define GP_ERROR_CHECKING true

/*
 0 - No Logging
 1 - Fatals Enabled
 2 - Errors Enabled
 3 - Warnings Enabled
 4 - Info Enabled
 5 - Debug Enabled
 6 - Trace Enabled
 7 - All Enabled
 */
#define GP_LOGGING 4

#include <type_traits>
#include <memory>

#define MAX_WIDTH 65535
#define MAX_HEIGHT 65535

#define _GP_BUILD_DLL

#define UNUSED(parameter) __attribute__((unused)) parameter

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

namespace gp {
    template<class T>
        struct _Unique_if {
            typedef std::unique_ptr<T> _Single_object;
        };

    template<class T>
        struct _Unique_if<T[]> {
            typedef std::unique_ptr<T[]> _Unknown_bound;
        };

    template<class T, size_t N>
        struct _Unique_if<T[N]> {
            typedef void _Known_bound;
        };

    template<class T, class... Args>
        typename _Unique_if<T>::_Single_object
        make_unique(Args &&... args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }

    template<class T>
        typename _Unique_if<T>::_Unknown_bound
        make_unique(size_t n) {
            typedef typename std::remove_extent<T>::type U;
            return std::unique_ptr<T>(new U[n]());
        }

    template<class T, class... Args>
        typename _Unique_if<T>::_Known_bound
        make_unique(Args &&...) = delete;
}

// Smart Pointers
namespace gp {
    template<typename T>
        using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
        constexpr Scope<T> CreateScope(Args &&... args) {
            return make_unique<T>(std::forward<Args>(args)...);
        }

    template<typename T>
        using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
        constexpr Ref<T> CreateRef(Args &&... args) {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
}

#include "src/goopylib/Debug/Log.h"
