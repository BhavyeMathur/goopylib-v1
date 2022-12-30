#include "camera_controller.h"
#include "goopylib/scene/CameraController.h"

#include "core/window_module.h"
#include "core/window_object.h"

#include "config.h"

#if (GP_LOG_CAMERA_CONTROLLER != true) and (GP_LOG_CAMERA_CONTROLLER <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_CAMERA_CONTROLLER
#endif

#if !GP_VALUE_CHECK_CAMERA_CONTROLLER
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"


struct CameraControllerObject {
    PyObject_HEAD
    Ref<gp::CameraController> controller;
};

// Camera Controller Core
namespace controller {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        GP_PY_DEBUG("gp.camera_controller.CameraController.__new__()");

        CameraControllerObject *self;
        self = (CameraControllerObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(CameraControllerObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.camera_controller.CameraController()");

        PyObject* window;
        if (!PyArg_ParseTuple(args, "O!", WindowType, &window)) {
            return -1;
        }

        auto win = ((WindowObject *) window)->window.get();
        self->controller = std::shared_ptr<gp::CameraController>(new gp::CameraController(win));

        return 0;
    }

    static PyObject *repr(CameraControllerObject *self) {
        GP_PY_TRACE("gp.camera_controller.CameraController.__repr__()");
        return PyUnicode_FromString("CameraController()");
    }

    static int traverse(CameraControllerObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(CameraControllerObject *self) {
        GP_PY_TRACE("gp.camera_controller.CameraController.clear()");
        return 0;
    }

    static void dealloc(CameraControllerObject *self) {
        GP_PY_DEBUG("gp.camera_controller.CameraController.__dealloc__()");

        self->controller.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Camera Controller methods
namespace controller {
    static PyObject *update(CameraControllerObject *self, PyObject *Py_UNUSED(args)) {
        self->controller->update();
        Py_RETURN_NONE;
    }

    static PyObject *enable_movement(CameraControllerObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyBool_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "bool", arg);
        }
        #endif

        self->controller->enableMovement(arg == Py_True);
        Py_RETURN_NONE;
    }

    static PyObject *enable_rotation(CameraControllerObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyBool_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "bool", arg);
        }
        #endif

        self->controller->enableRotation(arg == Py_True);
        Py_RETURN_NONE;
    }

    static PyObject *enable_zoom(CameraControllerObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyBool_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "bool", arg);
        }
        #endif

        self->controller->enableZoom(arg == Py_True);
        Py_RETURN_NONE;
    }

    static PyObject *invert_movement(CameraControllerObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyBool_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "bool", arg);
        }
        #endif

        self->controller->invertMovement(arg == Py_True);
        Py_RETURN_NONE;
    }

    static PyObject *invert_rotation(CameraControllerObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyBool_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "bool", arg);
        }
        #endif

        self->controller->invertRotation(arg == Py_True);
        Py_RETURN_NONE;
    }

    static PyObject *use_wasd(CameraControllerObject *self, PyObject *Py_UNUSED(args)) {
        self->controller->useWASD();
        Py_RETURN_NONE;
    }

    static PyObject *use_arrows(CameraControllerObject *self, PyObject *Py_UNUSED(args)) {
        self->controller->useArrows();
        Py_RETURN_NONE;
    }

    static PyObject *set_movement_keys(CameraControllerObject *self, PyObject *args) {
        int up, left, down, right;
        if (!PyArg_ParseTuple(args, "iiii", &up, &left, &down, &right)) {
            return nullptr;
        }

        self->controller->setMovementKeys(up, left, down, right);
        Py_RETURN_NONE;
    }

    static PyObject *set_rotation_keys(CameraControllerObject *self, PyObject *args) {
        int clockwise, anticlockwise;
        if (!PyArg_ParseTuple(args, "ii", &clockwise, &anticlockwise)) {
            return nullptr;
        }

        self->controller->setRotationKeys(clockwise, anticlockwise);
        Py_RETURN_NONE;
    }

    static PyObject *set_zoom_keys(CameraControllerObject *self, PyObject *args) {
        int in, out;
        if (!PyArg_ParseTuple(args, "ii", &in, &out)) {
            return nullptr;
        }

        self->controller->setZoomKeys(in, out);
        Py_RETURN_NONE;
    }
}

// Camera Controller getters & setters
namespace controller {
    // Horizontal Speed
    static PyObject *get_horizontal_speed(CameraControllerObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->controller->getHorizontalSpeed());
    }

    static int set_horizontal_speed(CameraControllerObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->controller->setHorizontalSpeed(PyFloat_AsDouble(value));
        return 0;
    }

    // Vertical Speed
    static PyObject *get_vertical_speed(CameraControllerObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->controller->getVerticalSpeed());
    }

    static int set_vertical_speed(CameraControllerObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->controller->setVerticalSpeed(PyFloat_AsDouble(value));
        return 0;
    }

    // Rotation Speed
    static PyObject *get_rotate_speed(CameraControllerObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->controller->getRotateSpeed());
    }

    static int set_rotate_speed(CameraControllerObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->controller->setRotateSpeed(PyFloat_AsDouble(value));
        return 0;
    }

    // Zoom Speed
    static PyObject *get_zoom_speed(CameraControllerObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->controller->getZoomSpeed());
    }

    static int set_zoom_speed(CameraControllerObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->controller->setZoomSpeed(PyFloat_AsDouble(value));
        return 0;
    }
}

// Camera Controller Type
namespace controller {
    static PyMethodDef methods[] = {
            {"update",            (PyCFunction) update,            METH_NOARGS,
                    "Updates the camera controller"},

            {"enable_movement",   (PyCFunction) enable_movement,   METH_O,
                    "Enables camera movement"},
            {"enable_rotation",   (PyCFunction) enable_rotation,   METH_O,
                    "Enables camera rotation"},
            {"enable_zoom",       (PyCFunction) enable_zoom,       METH_O,
                    "Enables camera zoom"},

            {"invert_movement",   (PyCFunction) invert_movement,   METH_O,
                    "Inverts the camera movement"},
            {"invert_rotation",   (PyCFunction) invert_rotation,   METH_O,
                    "Inverts the camera rotation"},

            {"use_wasd",          (PyCFunction) use_wasd,          METH_NOARGS,
                    "Uses the WASD keys for camera movement"},
            {"use_arrows",        (PyCFunction) use_arrows,        METH_NOARGS,
                    "Uses the arrow keys for camera movement"},

            {"set_movement_keys", (PyCFunction) set_movement_keys, METH_NOARGS,
                    "Sets the keys used for camera movement"},
            {"set_rotation_keys", (PyCFunction) set_rotation_keys, METH_NOARGS,
                    "Sets the keys used for camera rotation"},
            {"set_zoom_keys",     (PyCFunction) set_zoom_keys,     METH_NOARGS,
                    "Sets the keys used for camera zooming"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            GETTER_SETTER(horizontal_speed),
            GETTER_SETTER(vertical_speed),
            GETTER_SETTER(rotate_speed),
            GETTER_SETTER(zoom_speed),

            {nullptr}
    };
}

PyTypeObject ControllerType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.CameraController",
        .tp_basicsize = sizeof(CameraControllerObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

        .tp_new = controller::new_,
        .tp_init = (initproc) controller::init,

        .tp_methods = controller::methods,
        .tp_getset = controller::getsetters,

        .tp_traverse = (traverseproc) controller::traverse,
        .tp_clear = (inquiry) controller::clear,
        .tp_dealloc = (destructor) controller::dealloc,

        .tp_repr = (reprfunc) controller::repr,
};

static struct PyModuleDef CameraControllerModule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "camera_controller",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_camera_controller(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_camera_controller()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&CameraControllerModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Window

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_renderable() - import_window()" << std::endl;
    #endif
    PyWindow_API = (void **) PyCapsule_Import("goopylib.ext.window._C_API", 0);
    if (PyWindow_API == nullptr) {
        return nullptr;
    }

    WindowType = Window_pytype();

    // Exposing class

    EXPOSE_PYOBJECT_CLASS(ControllerType, "CameraController");

    return m;
}
