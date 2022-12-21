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

#include <iostream>
#include <cmath>
#include <utility>
#include <type_traits>
#include <random>
#include <string>
#include <vector>
#include <utility>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#if GP_USING_OPENGL

#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl.h>

#ifdef __APPLE__
#define __gl_h_
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#endif
#endif

#if GP_USING_GLFW

#include <GLFW/glfw3.h>

#endif

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

template<typename ... Args>
    std::string strformat(const std::string &format, Args ... args) {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size_s <= 0) {
            throw std::runtime_error("Error during formatting.");
        }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return {buf.get(), buf.get() + size - 1}; // We don't want the '\0' inside
    }

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
#include "src/goopylib/Math/gpmath.h"
