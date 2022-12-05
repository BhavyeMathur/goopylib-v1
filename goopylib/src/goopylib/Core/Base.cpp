#include "pch.h"
#include "Base.h"
#include "Platform/Independent/BaseWindow.h"

#if GP_USING_GLFW

#include <GLFW/glfw3.h>

#endif

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

    int Initialize() {
        #if GP_LOGGING
        gp::Log::init();
        #endif

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

    void Terminate() {
        GP_CORE_INFO("Terminating goopylib");

        gp::BaseWindow::destroyAll();

        #if GP_USING_GLFW
        GP_CORE_TRACE("Terminating GLFW");
        glfwTerminate();
        glfw_initialized = false;
        #endif
    }

    void Update() {
        #if GP_USING_GLFW
        glfwPollEvents();
        #endif
        OnUpdate();
    }

    #if GP_USING_GLFW

    void UpdateOnEvent() {
        glfwWaitEvents();
        OnUpdate();
    }

    void UpdateTimeout(double timeout) {
        glfwWaitEventsTimeout(timeout);
        OnUpdate();
    }

    std::string GLFWCompiledVersion() {
        return {glfwGetVersionString()};
    }

    std::string GLFWCurrentVersion() {
        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);

        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision);
    }

    int GetRefreshRate() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
    }

    int GetScreenWidth() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    }

    int GetScreenHeight() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
    }

    int GetNumberOfMonitors() {
        int count;
        glfwGetMonitors(&count);
        return count;
    }

    void SetBufferSwapInterval(int interval) {
        glfwSwapInterval(interval);
    }

    #endif

    #if GP_USING_OPENGL

    std::string OpenGLVersion() {
        return {(char *) glGetString(GL_VERSION)};
    }

    #endif
}
