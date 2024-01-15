#define GP_LOGGING_LEVEL 3

#include "Core.h"
#include "src/goopylib/core/Window.h"

#if GP_USING_GLAD
#include <glad/glad.h>
#endif

#if GP_USING_GLFW

#include <GLFW/glfw3.h>
#ifdef APIENTRY
#undef APIENTRY
#endif

#endif


namespace gp {
    static bool is_initialized = false;
}

namespace {
    void onUpdate() {
        GP_CORE_TRACE_ALL("gp::onUpdate()");
        gp::Window::updateAll();

        #if (GP_ERROR_CHECKING and GP_USING_OPENGL)
        if (glfwGetCurrentContext()) {
            GLenum error;
            while ((error = glGetError()) != GL_NO_ERROR) {
                switch (error) {
                    case GL_INVALID_ENUM:
                        GP_CORE_ERROR("OpenGL Invalid Enum Error");
                        GP_RUNTIME_ERROR("OpenGL Invalid Enum Error");
                        break;

                    case GL_INVALID_OPERATION:
                        GP_CORE_ERROR("OpenGL Invalid Operation Error");
                        GP_RUNTIME_ERROR("OpenGL Invalid Operation Error");
                        break;

                    case GL_INVALID_VALUE:
                        GP_CORE_ERROR("OpenGL Invalid Value Error");
                        GP_RUNTIME_ERROR("OpenGL Invalid Value Error");
                        break;

                    case GL_STACK_OVERFLOW:
                        GP_CORE_ERROR("OpenGL Stack Overflow Error");
                        GP_RUNTIME_ERROR("OpenGL Stack Overflow Error");
                        break;

                    case GL_STACK_UNDERFLOW:
                        GP_CORE_ERROR("OpenGL Stack Underflow Error");
                        GP_RUNTIME_ERROR("OpenGL Stack Underflow Error");
                        break;

                    case GL_OUT_OF_MEMORY:
                        GP_CORE_ERROR("OpenGL Out of Memory Error");
                        GP_RUNTIME_ERROR("OpenGL Out of Memory Error");
                        break;

                    default:
                        GP_CORE_ERROR("OpenGL Error: {0}", error);
                        GP_RUNTIME_ERROR("Unknown OpenGL Error");
                }
            }
        }
        #endif
    }

    void initGLFW() {
        GP_CORE_DEBUG("gp::init() initialising GLFW");

        #if GP_USING_GLFW
        glfwSetErrorCallback([](int error, const char *description) {
            GP_CORE_WARN("GLFW Error Code {0}: {1}", error, description);
        });
        if (!glfwInit()) {
            GP_RUNTIME_ERROR("gp::init() failed to initialize GLFW");
        }
        gp::is_initialized = true;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        #endif
    }
}

namespace gp {
    void init() {
        Log::init();

        GP_CORE_INFO("gp::init()");

        #if GP_USING_GLFW
        initGLFW();
        #endif
    }

    void terminate() {
        GP_CORE_INFO("gp::terminate()");

        Window::destroyAll();

        #if GP_USING_GLFW
        GP_CORE_DEBUG("gp::terminate() terminating GLFW");

        glfwTerminate();
        is_initialized = false;
        #endif
    }

    bool isInitialized() {
        return is_initialized;
    }

    void update() {
        GP_CORE_TRACE_ALL("gp::update()");

        onUpdate();
        #if GP_USING_GLFW
        glfwPollEvents();
        #endif
    }

    #if GP_USING_GLFW

    void updateOnEvent() {
        GP_CORE_TRACE_ALL("gp::updateOnEvent()");

        glfwWaitEvents();
        onUpdate();
    }

    void updateTimeout(double timeout) {
        GP_CORE_TRACE_ALL("gp::updateTimeout(timeout={0})", timeout);

        GP_CHECK_GE(timeout, 0, "gp::updateTimeout() timeout must be greater than or equal to 0");

        glfwWaitEventsTimeout(timeout);
        onUpdate();
    }

    void setBufferSwapInterval(int32_t interval) {
        GP_CORE_TRACE("gp::setBufferSwapInterval(interval={0})", interval);

        GP_CHECK_GE(interval, 0, "gp::setBufferSwapInterval() interval must be greater than or equal to 0");

        glfwSwapInterval(interval);
    }

    int getRefreshRate() {
        GP_CORE_TRACE("gp::getRefreshRate()");

        return glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
    }

    int getScreenWidth() {
        GP_CORE_TRACE("gp::getScreenWidth()");

        return glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    }

    int getScreenHeight() {
        GP_CORE_TRACE("gp::getScreenHeight()");

        return glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
    }

    int getNumberOfMonitors() {
        GP_CORE_TRACE("gp::getNumberOfMonitors()");

        int count;
        glfwGetMonitors(&count);
        return count;
    }

    float getTime() {
        return (float) glfwGetTime();
    }

    bool hasActiveContext() {
        return (bool) glfwGetCurrentContext();
    }

    std::string glfwCompiledVersion() {
        GP_CORE_TRACE("gp::glfwCompiledVersion()");

        return {glfwGetVersionString()};
    }

    std::string glfwCurrentVersion() {
        GP_CORE_TRACE("gp::glfwCurrentVersion()");

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);

        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision);
    }

    #endif

    #if GP_USING_OPENGL

    std::string openglVersion() {
        GP_CORE_TRACE("gp::openglVersion()");

        return {(char *)(glGetString(GL_VERSION))};
    }

    #endif
}
