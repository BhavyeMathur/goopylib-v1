#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "src/goopylib/core/Core.h"
#include "core.h"


namespace core {
    PyObject *init(PyObject * ) {
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

    static PyObject *terminate(PyObject * ) {
        GP_PY_TRACE("core.terminate()");

        gp::terminate();

        Py_RETURN_NONE;
    }

    static PyObject *is_initialised(PyObject * ) {
        GP_PY_TRACE("core.is_initialised()");

        if (gp::isInitialized()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *update(PyObject * ) {
        GP_PY_TRACE("core.update()");

        gp::update();

        Py_RETURN_NONE;
    }

    #if GP_USING_GLFW

    static PyObject *has_active_context(PyObject * ) {
        GP_PY_TRACE("core.has_active_context()");

        if (gp::hasActiveContext()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *update_on_event(PyObject * , PyObject * ) {
        GP_PY_TRACE("core.update_on_event()");

        gp::updateOnEvent();

        Py_RETURN_NONE;
    }

    static PyObject *update_timeout(PyObject * , PyObject * arg) {
        GP_PY_TRACE("core.update_on_timeout()");

        double timeout = PyFloat_AsDouble(arg);
        gp::updateTimeout(timeout);

        Py_RETURN_NONE;
    }

    static PyObject *glfw_compiled_version(PyObject * ) {
        GP_PY_TRACE("core.glfw_compiled_version()");

        return PyUnicode_FromString(gp::glfwCompiledVersion().c_str());
    }

    static PyObject *glfw_current_version(PyObject * ) {
        GP_PY_TRACE("core.glfw_current_version()");

        return PyUnicode_FromString(gp::glfwCurrentVersion().c_str());
    }

    static PyObject *get_refresh_rate(PyObject * ) {
        GP_PY_TRACE("core.get_refresh_rate()");

        return PyLong_FromLong(gp::getRefreshRate());
    }

    static PyObject *get_screen_width(PyObject * ) {
        GP_PY_TRACE("core.get_screen_width()");

        return PyLong_FromLong(gp::getScreenWidth());
    }

    static PyObject *get_screen_height(PyObject * ) {
        GP_PY_TRACE("core.get_screen_height()");

        return PyLong_FromLong(gp::getScreenHeight());
    }

    static PyObject *number_of_monitors(PyObject * ) {
        GP_PY_TRACE("core.number_of_monitors()");

        return PyLong_FromLong(gp::getNumberOfMonitors());
    }

    static PyObject *set_buffer_swap_interval(PyObject * , PyObject * arg) {
        GP_PY_TRACE("core.set_buffer_swap_interval()");

        auto interval = (int32_t) PyLong_AsLong(arg);
        gp::setBufferSwapInterval(interval);

        Py_RETURN_NONE;
    }

    #endif

    #if GP_USING_OPENGL

    static PyObject *opengl_version(PyObject * ) {
        GP_PY_TRACE("core.opengl_version()");

        return PyUnicode_FromString(gp::openglVersion().c_str());
    }

    #endif
}

static PyMethodDef CoreMethods[] = {
        {"init", (PyCFunction) core::init, METH_NOARGS, ""},
        {"terminate", (PyCFunction) core::terminate, METH_NOARGS, ""},
        {"is_initialised", (PyCFunction) core::is_initialised, METH_NOARGS, ""},

        {"update", (PyCFunction) core::update, METH_NOARGS, ""},

        #if GP_USING_GLFW

        {"has_active_context", (PyCFunction) core::has_active_context, METH_NOARGS, ""},

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


static struct PyModuleDef CoreModule = {
        PyModuleDef_HEAD_INIT,
        "core",
        "",
        -1,
        CoreMethods,
        nullptr
};

PyMODINIT_FUNC PyInit_core(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_core()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&CoreModule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
