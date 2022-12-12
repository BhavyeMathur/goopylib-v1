#include "pch.h"
#include "Base.h"

namespace {
    void OnUpdate() {
        gp::BaseWindow::updateAll();

        #if (GP_DEBUGGING)
        GLenum error;
        while ((error = glGetError()) != GL_NO_ERROR) {
            printf("Unknown Error: 0x%x\n", error);
        }
        #endif
    }
}

namespace gp {
    bool glfw_initialized = false;

    GPAPI int initialize() {
        #if GP_LOGGING
        gp::Log::Init();
        #endif

        gp::InitializeW3CX11();

        GP_CORE_INFO("Initializing goopylib");

        #if GP_USING_GLFW
        GP_CORE_TRACE("Initializing GLFW");

        glfwSetErrorCallback([](int error, const char *description) {
            std::cout << "ERROR: " << description << std::endl;
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

        return 0;
    }

    GPAPI void terminate() {
        GP_CORE_INFO("Terminating goopylib");

        BaseWindow::destroyAll();

        DeallocateW3CX11();

        #if GP_USING_GLFW
        GP_CORE_TRACE("Terminating GLFW");
        glfwTerminate();
        glfw_initialized = false;
        #endif
    }

    GPAPI void update() {
        OnUpdate();
        #if GP_USING_GLFW
        glfwPollEvents();
        #endif
    }

    #if GP_USING_GLFW

    GPAPI void updateOnEvent() {
        glfwWaitEvents();
        OnUpdate();
    }

    GPAPI void updateTimeout(double timeout) {
        glfwWaitEventsTimeout(timeout);
        OnUpdate();
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
        glfwSwapInterval(interval);
    }

    #endif

    #if GP_USING_OPENGL

    GPAPI std::string openglVersion() {
        return {(char *) glGetString(GL_VERSION)};
    }

    #endif
}
