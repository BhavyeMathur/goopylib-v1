#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "window/Window.h"

namespace py = pybind11;

PYBIND11_MODULE(window, m) {
    py::class_<gp::Window>(m, "Window")
            .def(py::init<int, int, const char *>())
            .def("__repr__", &gp::Window::toString)

            .def("is_closed", &gp::Window::isClosed)
            .def("is_open", &gp::Window::isOpen)
            .def("is_destroyed", &gp::Window::isDestroyed)

            .def("update", &gp::Window::update)
            .def("destroy", &gp::Window::destroy)

            .def("set_size", &gp::Window::setSize)
            .def("set_size_limits", &gp::Window::setSizeLimits)
            .def("set_min_size", &gp::Window::setMinSize)
            .def("set_max_size", &gp::Window::setMaxSize)

            .def("set_aspect_ratio", &gp::Window::setAspectRatio)
            .def("get_aspect_ratio", &gp::Window::getAspectRatio)
            .def("get_frame_size", &gp::Window::getFrameSize)
            .def("get_content_scale", &gp::Window::getContentScale)
            .def("get_framebuffer_size", &gp::Window::getFramebufferSize)

            .def("restore", &gp::Window::restore)
            .def("fullscreen", &gp::Window::fullscreen)
            .def("is_fullscreen", &gp::Window::isFullscreen)
            .def("minimize", &gp::Window::minimize)
            .def("is_minimized", &gp::Window::isMinimized)
            .def("maximize", &gp::Window::maximize)
            .def("is_maximized", &gp::Window::isMaximized)
            .def("show", &gp::Window::show)
            .def("hide", &gp::Window::hide)
            .def("is_visible", &gp::Window::isVisible)
            .def("focus", &gp::Window::focus)
            .def("has_focus", &gp::Window::hasFocus)
            .def("request_attention", &gp::Window::requestAttention)

            .def("is_mouse_hovering", &gp::Window::isMouseHovering)
            .def("get_mouse_position", &gp::Window::getMousePosition)
            .def("set_cursor_mode", &gp::Window::setCursorMode)
            .def("check_mouse_button", &gp::Window::checkMouseButton)
            .def("check_left_click", &gp::Window::checkLeftClick)
            .def("check_middle_click", &gp::Window::checkMiddleClick)
            .def("check_right_click", &gp::Window::checkRightClick)

            .def("check_shift_key", &gp::Window::checkShiftKey)
            .def("check_control_key", &gp::Window::checkControlKey)
            .def("check_alt_key", &gp::Window::checkAltKey)
            .def("check_super_key", &gp::Window::checkSuperKey)
            .def("check_key", &gp::Window::checkKey)

            .def_property("resize_callback", py::cpp_function(), &gp::Window::setResizeCallback)
            .def_property("close_callback", py::cpp_function(), &gp::Window::setCloseCallback)
            .def_property("destroy_callback", py::cpp_function(), &gp::Window::setDestroyCallback)
            .def_property("position_callback", py::cpp_function(), &gp::Window::setPositionCallback)
            .def_property("minimize_callback", py::cpp_function(), &gp::Window::setMinimizeCallback)
            .def_property("maximize_callback", py::cpp_function(), &gp::Window::setMaximizeCallback)
            .def_property("focus_callback", py::cpp_function(), &gp::Window::setFocusCallback)
            .def_property("refresh_callback", py::cpp_function(), &gp::Window::setRefreshCallback)
            .def_property("content_scale_callback", py::cpp_function(), &gp::Window::setContentScaleCallback)
            .def_property("framebuffer_size_callback", py::cpp_function(), &gp::Window::setFramebufferSizeCallback)
            .def_property("mouse_motion_callback", py::cpp_function(), &gp::Window::setMouseMotionCallback)
            .def_property("mouse_enter_callback", py::cpp_function(), &gp::Window::setMouseEnterCallback)
            .def_property("scroll_callback", py::cpp_function(), &gp::Window::setScrollCallback)

            .def("set_key_callback", &gp::Window::setKeyCallback)
            .def("set_mouse_button_callback", &gp::Window::setMouseButtonCallback)
            .def_property("left_click_callback", py::cpp_function(), &gp::Window::setLeftClickCallback)
            .def_property("middle_click_callback", py::cpp_function(), &gp::Window::setMiddleClickCallback)
            .def_property("right_click_callback", py::cpp_function(), &gp::Window::setRightClickCallback)

            .def("get_camera", &gp::Window::getCamera)
            .def("to_world", &gp::Window::toWorld)
            .def("to_screen", &gp::Window::toScreen)

            .def_property("title", &gp::Window::getTitle, &gp::Window::setTitle)
            .def_property("background", &gp::Window::getBackground, &gp::Window::setBackground)
            .def_property("xpos", &gp::Window::getXPos, &gp::Window::setXPos)
            .def_property("ypos", &gp::Window::getYPos, &gp::Window::setYPos)
            .def_property("position", &gp::Window::getPosition, &gp::Window::setPosition)

            .def_property("width", &gp::Window::getMinWidth, &gp::Window::setMinWidth)
            .def_property("height", &gp::Window::getMinHeight, &gp::Window::setMinHeight)
            .def_property("min_width", &gp::Window::getMinWidth, &gp::Window::setMinWidth)
            .def_property("min_height", &gp::Window::getMinHeight, &gp::Window::setMinHeight)
            .def_property("max_width", &gp::Window::getMaxWidth, &gp::Window::setMaxWidth)
            .def_property("max_height", &gp::Window::getMaxHeight, &gp::Window::setMaxHeight)

            .def_property("resizable", &gp::Window::isResizable, &gp::Window::setResizable)
            .def_property("decorated", &gp::Window::isDecorated, &gp::Window::setDecorated)
            .def_property("floating", &gp::Window::isFloating, &gp::Window::setFloating)
            .def_property("auto_minimized", &gp::Window::isAutoMinimized, &gp::Window::setAutoMinimized)
            .def_property("focused_on_show", &gp::Window::isFocusedOnShow, &gp::Window::setFocusedOnShow)

            .def_static("update_all", &gp::Window::updateAll)
            .def_static("destroy_all", &gp::Window::destroyAll)
            ;
}
