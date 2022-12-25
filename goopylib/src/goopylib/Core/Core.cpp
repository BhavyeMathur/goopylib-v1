#include "Window.h"

#include "src/gp.h"
#include "src/goopylib/Core/Core.h"
#include "src/goopylib/Color/W3CX11.h"

#include <stb/stb_image.h>
#include <GLFW/glfw3.h>

namespace {
    void onUpdate() {
        gp::Window::updateAll();

        #if (GP_LOGGING >= 2 and GP_USING_OPENGL)
        GLenum error;
        while ((error = glGetError()) != GL_NO_ERROR) {
            switch (error) {
                case GL_INVALID_ENUM:
                    GP_CORE_ERROR("OpenGL Invalid Enum Error");
                    break;

                case GL_INVALID_OPERATION:
                    GP_CORE_ERROR("OpenGL Invalid Operation Error");
                    break;

                case GL_INVALID_VALUE:
                    GP_CORE_ERROR("OpenGL Invalid Value Error");
                    break;

                case GL_STACK_OVERFLOW:
                    GP_CORE_ERROR("OpenGL Stack Overflow Error");
                    break;

                case GL_STACK_UNDERFLOW:
                    GP_CORE_ERROR("OpenGL Stack Underflow Error");
                    break;

                case GL_OUT_OF_MEMORY:
                    GP_CORE_ERROR("OpenGL Out of Memory Error");
                    break;

                default:
                    GP_CORE_ERROR("OpenGL Error: {0}", error);
            }
        }
        #endif
    }
}

namespace gp {
    bool glfw_initialized = false;

    int initialize() {
        Log::init();

        GP_CORE_INFO("Initializing goopylib");

        stbi_set_flip_vertically_on_load(1);

        GP_CORE_DEBUG("Initializing W3CX11");
        InitializeW3CX11();

        #if GP_USING_GLFW
        GP_CORE_DEBUG("Initializing GLFW");

        glfwSetErrorCallback([](int error, const char *description) {
            GP_CORE_ERROR("GLFW Error Code {0}: {1}", error, description);
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

    void terminate() {
        GP_CORE_INFO("Terminating goopylib");

        Window::destroyAll();

        GP_CORE_DEBUG("Deallocating W3CX11");
        DeallocateW3CX11();

        #if GP_USING_GLFW
        GP_CORE_DEBUG("Terminating GLFW");
        glfwTerminate();
        glfw_initialized = false;
        #endif
    }

    void update() {
        onUpdate();
        #if GP_USING_GLFW
        glfwPollEvents();
        #endif
    }

    #if GP_USING_GLFW

    void updateOnEvent() {
        glfwWaitEvents();
        onUpdate();
    }

    void updateTimeout(double timeout) {
        glfwWaitEventsTimeout(timeout);
        onUpdate();
    }

    std::string glfwCompiledVersion() {
        return {glfwGetVersionString()};
    }

    std::string glfwCurrentVersion() {
        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);

        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision);
    }

    int getRefreshRate() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
    }

    int getScreenWidth() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    }

    int getScreenHeight() {
        return glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
    }

    int getNumberOfMonitors() {
        int count;
        glfwGetMonitors(&count);
        return count;
    }

    void setBufferSwapInterval(int interval) {
        GP_CORE_INFO("Frame Rate limited to {0}", interval);
        glfwSwapInterval(interval);
    }

    #endif

    #if GP_USING_OPENGL

    std::string openglVersion() {
        return {(char *) glGetString(GL_VERSION)};
    }

    #endif
}
