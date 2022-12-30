#include "goopylib/core/Core.h"
#include "core.h"

#include <GLFW/glfw3.h>

#include "config.h"

#if (GP_LOG_CORE != true) and (GP_LOG_CORE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_CORE
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"


namespace core {
    static PyObject *init(PyObject *Py_UNUSED(self)) {
        #if GP_LOGGING_LEVEL >= 6
        std::cout << "[--:--:--] PYTHON: core.init()" << std::endl;
        #endif

        try {
            gp::init();
        }
        catch (const std::runtime_error &e) {
            PyErr_SetString(PyExc_RuntimeError, e.what());
            return nullptr;
        }

        Py_RETURN_NONE;
    }

    static PyObject *terminate(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.terminate()");

        gp::terminate();

        Py_RETURN_NONE;
    }

    static PyObject *update(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.update()");

        gp::update();

        Py_RETURN_NONE;
    }

    #if GP_USING_GLFW

    static PyObject *update_on_event(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("core.update_on_event()");

        gp::updateOnEvent();

        Py_RETURN_NONE;
    }

    static PyObject *update_timeout(PyObject *Py_UNUSED(self), PyObject *arg) {
        GP_PY_TRACE("core.update_on_timeout()");

        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "number", arg);
        }
        #endif

        double timeout = PyFloat_AsDouble(arg);

        GP_CHECK_GE(timeout, 0, nullptr, "timeout must be greater than or equal to 0")

        gp::updateTimeout(timeout);

        Py_RETURN_NONE;
    }

    static PyObject *glfw_compiled_version(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.glfw_compiled_version()");

        return PyUnicode_FromString(gp::glfwCompiledVersion().c_str());
    }

    static PyObject *glfw_current_version(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.glfw_current_version()");

        return PyUnicode_FromString(gp::glfwCurrentVersion().c_str());
    }

    static PyObject *get_refresh_rate(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.get_refresh_rate()");

        CHECK_GLFW_INITIALIZED(nullptr);
        return PyLong_FromLong(gp::getRefreshRate());
    }

    static PyObject *get_screen_width(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.get_screen_width()");

        CHECK_GLFW_INITIALIZED(nullptr);
        return PyLong_FromLong(gp::getScreenWidth());
    }

    static PyObject *get_screen_height(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.get_screen_height()");

        CHECK_GLFW_INITIALIZED(nullptr);
        return PyLong_FromLong(gp::getScreenHeight());
    }

    static PyObject *number_of_monitors(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.number_of_monitors()");

        CHECK_GLFW_INITIALIZED(nullptr);
        return PyLong_FromLong(gp::getNumberOfMonitors());
    }

    static PyObject *set_buffer_swap_interval(PyObject *Py_UNUSED(self), PyObject *arg) {
        GP_PY_TRACE("core.set_buffer_swap_interval()");

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "integer", arg);
        }
        #endif

        int32_t interval = (int32_t) PyLong_AsLong(arg);

        GP_CHECK_GE(interval, 0, nullptr, "interval must be greater than or equal to 0")

        gp::setBufferSwapInterval(interval);
        Py_RETURN_NONE;
    }

    #endif

    #if GP_USING_OPENGL

    static PyObject *opengl_version(PyObject *Py_UNUSED(self)) {
        GP_PY_TRACE("core.opengl_version()");

        CHECK_GLFW_CONTEXT(nullptr);
        return PyUnicode_FromString(gp::openglVersion().c_str());
    }

    #endif
}

static PyMethodDef CoreMethods[] = {
        {"init", (PyCFunction) core::init, METH_NOARGS, ""},
        {"terminate", (PyCFunction) core::terminate, METH_NOARGS, ""},

        {"update", (PyCFunction) core::update, METH_NOARGS, ""},

        #if GP_USING_GLFW

        {"update_on_event", (PyCFunction) core::update_on_event, METH_NOARGS, ""},
        {"update_timeout", (PyCFunction) core::update_timeout, METH_O, ""},

        {"glfw_compiled_version", (PyCFunction) core::glfw_compiled_version, METH_NOARGS, ""},
        {"glfw_current_version", (PyCFunction) core::glfw_current_version, METH_NOARGS, ""},

        {"get_refresh_rate", (PyCFunction) core::get_refresh_rate, METH_NOARGS, ""},
        {"get_screen_width", (PyCFunction) core::get_screen_width, METH_NOARGS, ""},
        {"get_screen_height", (PyCFunction) core::get_screen_height, METH_NOARGS, ""},
        {"number_of_monitors", (PyCFunction) core::number_of_monitors, METH_NOARGS, ""},

        {"set_buffer_swap_interval", (PyCFunction) core::set_buffer_swap_interval, METH_O, ""},

        #endif

        #if GP_USING_OPENGL

        {"opengl_version", (PyCFunction) core::opengl_version, METH_NOARGS, ""},

        #endif

        {nullptr, nullptr, 0, nullptr}
};


static struct PyModuleDef coremodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "core",
        .m_size = -1,
        .m_methods = CoreMethods,
};

PyMODINIT_FUNC PyInit_core(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_core()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&coremodule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
