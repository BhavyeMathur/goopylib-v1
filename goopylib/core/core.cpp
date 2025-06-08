#include "goopylib/header.h"
#include "core/Core.h"

namespace py = pybind11;


PYBIND11_MODULE(core, m) {
    m.def("init", &gp::init);
    m.def("terminate", &gp::terminate);
    m.def("is_initialized", &gp::isInitialized);
    m.def("has_active_context", &gp::hasActiveContext);

    m.def("update", &gp::update);
    m.def("update_timeout", &gp::updateTimeout);
    m.def("update_on_event", &gp::updateOnEvent);

    m.def("set_buffer_swap_interval", &gp::setBufferSwapInterval);

    m.def("get_refresh_rate", &gp::getRefreshRate);
    m.def("get_screen_width", &gp::getScreenWidth);
    m.def("get_screen_height", &gp::getScreenHeight);
    m.def("get_number_of_monitors", &gp::getNumberOfMonitors);
    m.def("get_time", &gp::getTime);

    m.def("glfw_compiled_version", &gp::glfwCompiledVersion);
    m.def("glfw_current_version", &gp::glfwCurrentVersion);
    m.def("opengl_version", &gp::openglVersion);
}
