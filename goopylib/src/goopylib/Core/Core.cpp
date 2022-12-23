#include "src/pch.h"

#include "src/goopylib/Core/Core.h"
#include "src/goopylib/Color/W3CX11.h"
#include "src/Platform/Independent/BaseWindow.h"

namespace {
    void onUpdate() {
        gp::BaseWindow::updateAll();

        #if (GP_DEBUGGING and GP_USING_OPENGL)
        GLenum error;
        while ((error = glGetError()) != GL_NO_ERROR) {
            GP_CORE_ERROR("OpenGL Error: {0}", error);
        }
        #endif
    }
}

namespace gp {
    bool glfw_initialized = false;

    GPAPI int initialize() {
        Log::init();

        GP_CORE_INFO("Initializing goopylib");

        stbi_set_flip_vertically_on_load(1);

        GP_CORE_DEBUG("Initializing W3CX11");
        InitializeW3CX11();

        #if GP_USING_GLFW
        GP_CORE_DEBUG("Initializing GLFW");

        glfwSetErrorCallback([](int error, const char *description) {
            GP_CORE_ERROR("GLFW Error Code {0}: {1}" , error, description);
        });
        if (!glfwInit()) {
            return -1;
        }
        glfw_initialized = true;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #endif

        #if GP_USING_OPENGL
        #endif

        return 0;
    }

    GPAPI void terminate() {
        GP_CORE_INFO("Terminating goopylib");

        BaseWindow::destroyAll();

        GP_CORE_DEBUG("Deallocating W3CX11");
        DeallocateW3CX11();

        #if GP_USING_GLFW
        GP_CORE_DEBUG("Terminating GLFW");
        glfwTerminate();
        glfw_initialized = false;
        #endif
    }

    GPAPI void update() {
        onUpdate();
        #if GP_USING_GLFW
        glfwPollEvents();
        #endif
    }

    #if GP_USING_GLFW

    GPAPI void updateOnEvent() {
        glfwWaitEvents();
        onUpdate();
    }

    GPAPI void updateTimeout(double timeout) {
        glfwWaitEventsTimeout(timeout);
        onUpdate();
    }

    GPAPI std::string glfwCompiledVersion() {
        return {glfwGetVersionString()};
    }

    GPAPI std::string glfwCurrentVersion() {
        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);

        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision);
    }

    GPAPI int getRefreshRate() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
    }

    GPAPI int getScreenWidth() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    }

    GPAPI int getScreenHeight() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
    }

    GPAPI int getNumberOfMonitors() {
        int count;
        glfwGetMonitors(&count);
        return count;
    }

    GPAPI void setBufferSwapInterval(int interval) {
        GP_CORE_INFO("Frame Rate limited to {0}", interval);
        glfwSwapInterval(interval);
    }

    #endif

    #if GP_USING_OPENGL

    GPAPI std::string openglVersion() {
        return {(char *) glGetString(GL_VERSION)};
    }

    #endif
}
