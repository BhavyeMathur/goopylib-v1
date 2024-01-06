#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#define CAMERA_MODULE

#include "camera.h"
#include "camera_object.h"
#include "camera_module.h"
#include "camera_capsule.h"


// Camera Core
namespace camera {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        GP_PY_DEBUG("gp.camera.Camera.__new__()");

        CameraObject *self;
        self = (CameraObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(CameraObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.camera.Camera()");

        float left, right, bottom, top;
        if (!PyArg_ParseTuple(args, "ffff", &left, &right, &bottom, &top)) {
            return -1;
        }

        self->camera = std::shared_ptr<gp::Camera>(new gp::Camera(left, right, bottom, top));
        return 0;
    }

    static PyObject *repr(CameraObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.camera.Camera.__repr__()");
        return PyUnicode_FromString("Camera()");
    }

    static int traverse(CameraObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(CameraObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.camera.Camera.clear()");
        return 0;
    }

    static void dealloc(CameraObject *self) {
        GP_PY_DEBUG("gp.camera.Camera.__dealloc__()");

        self->camera.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Camera methods
namespace camera {
    static PyObject *set_projection(CameraObject *self, PyObject *args) {
        float left, right, bottom, top;
        if (!PyArg_ParseTuple(args, "ffff", &left, &right, &bottom, &top)) {
            return nullptr;
        }

        self->camera->setProjection(left, right, bottom, top);
        Py_RETURN_NONE;
    }

    static PyObject *get_visible_frame(CameraObject *self, PyObject *args) {
        auto val = self->camera->getVisibleFrame();

        PyObject * return_dict = PyDict_New();

        PyDict_SetItemString(return_dict, "left", PyFloat_FromDouble(val.left));
        PyDict_SetItemString(return_dict, "right", PyFloat_FromDouble(val.right));
        PyDict_SetItemString(return_dict, "top", PyFloat_FromDouble(val.top));
        PyDict_SetItemString(return_dict, "bottom", PyFloat_FromDouble(val.bottom));

        return return_dict;
    }

    static PyObject *get_projection_frame(CameraObject *self, PyObject *args) {
        auto val = self->camera->getProjectionFrame();

        PyObject * return_dict = PyDict_New();

        PyDict_SetItemString(return_dict, "left", PyFloat_FromDouble(val.left));
        PyDict_SetItemString(return_dict, "right", PyFloat_FromDouble(val.right));
        PyDict_SetItemString(return_dict, "top", PyFloat_FromDouble(val.top));
        PyDict_SetItemString(return_dict, "bottom", PyFloat_FromDouble(val.bottom));

        return return_dict;
    }

    static PyObject *get_visible_width(CameraObject *self, PyObject *args) {
        return PyFloat_FromDouble(self->camera->getVisibleWidth());
    }

    static PyObject *get_visible_height(CameraObject *self, PyObject *args) {
        return PyFloat_FromDouble(self->camera->getVisibleHeight());
    }

    static PyObject *get_projection_width(CameraObject *self, PyObject *args) {
        return PyFloat_FromDouble(self->camera->getProjectionWidth());
    }

    static PyObject *get_projection_height(CameraObject *self, PyObject *args) {
        return PyFloat_FromDouble(self->camera->getProjectionHeight());
    }

    static PyObject *get_visible_size(CameraObject *self, PyObject *args) {
        auto val = self->camera->getVisibleSize();

        PyObject * return_dict = PyDict_New();
        PyDict_SetItemString(return_dict, "width", PyFloat_FromDouble(val.width));
        PyDict_SetItemString(return_dict, "height", PyFloat_FromDouble(val.height));

        return return_dict;
    }

    static PyObject *get_projection_size(CameraObject *self, PyObject *args) {
        auto val = self->camera->getProjectionSize();

        PyObject * return_dict = PyDict_New();
        PyDict_SetItemString(return_dict, "width", PyFloat_FromDouble(val.width));
        PyDict_SetItemString(return_dict, "height", PyFloat_FromDouble(val.height));

        return return_dict;
    }

    static PyObject *move(CameraObject *self, PyObject *args) {
        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        self->camera->move(x, y);
        Py_RETURN_NONE;
    }

    static PyObject *rotate(CameraObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "number", arg);
        }
        #endif

        self->camera->rotate((float) PyFloat_AsDouble(arg));
        Py_RETURN_NONE;
    }

    static PyObject *zoomin(CameraObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "number", arg);
        }
        #endif

        self->camera->zoom((float) PyFloat_AsDouble(arg));
        Py_RETURN_NONE;
    }
}

// Camera getters & setters
namespace camera {
    // X-Position
    static PyObject *get_x(CameraObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->camera->getX());
    }

    static int set_x(CameraObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->camera->setX((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Y-Position
    static PyObject *get_y(CameraObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->camera->getY());
    }

    static int set_y(CameraObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->camera->setY((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Position
    static PyObject *get_position(CameraObject *self, void *Py_UNUSED(closure)) {
        return Py_BuildValue("ff", self->camera->getX(), self->camera->getY());
    }

    static int set_position(CameraObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        float x, y;
        if (!PyArg_ParseTuple(value, "ff", &x, &y)) {
            return -1;
        }

        self->camera->setPosition(x, y);
        return 0;
    }

    // Rotation
    static PyObject *get_rotation(CameraObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->camera->getRotation());
    }

    static int set_rotation(CameraObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->camera->setRotation((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Zoom
    static PyObject *get_zoom(CameraObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->camera->getZoom());
    }

    static int set_zoom(CameraObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->camera->setZoom((float) PyFloat_AsDouble(value));
        return 0;
    }
}

// Camera Type
namespace camera {
    static PyMethodDef methods[] = {
            {"set_projection",        (PyCFunction) set_projection,        METH_VARARGS,
                    "Sets the projection of the camera"},

            {"get_visible_frame",     (PyCFunction) get_visible_frame,     METH_NOARGS,
                    "Gets the currently visible camera frame with left, right, bottom, and top values"},
            {"get_visible_width",     (PyCFunction) get_visible_width,     METH_NOARGS,
                    "Gets the currently visible camera frame width"},
            {"get_visible_height",    (PyCFunction) get_visible_height,    METH_NOARGS,
                    "Gets the currently visible camera frame height"},
            {"get_visible_size",      (PyCFunction) get_visible_size,      METH_NOARGS,
                    "Gets the currently visible camera frame size as width, height"},

            {"get_projection_frame",  (PyCFunction) get_projection_frame,  METH_NOARGS,
                    "Gets the camera projection frame (zoom=1) with left, right, bottom, and top values"},
            {"get_projection_width",  (PyCFunction) get_projection_width,  METH_NOARGS,
                    "Gets the camera projection (zoom=1) width"},
            {"get_projection_height", (PyCFunction) get_projection_height, METH_NOARGS,
                    "Gets the camera projection (zoom=1) height"},
            {"get_projection_size",   (PyCFunction) get_projection_size,   METH_NOARGS,
                    "Gets the camera projection (zoom=1) size as width, height"},

            {"move",                  (PyCFunction) move,                  METH_VARARGS,
                    "Moves the camera"},
            {"rotate",                (PyCFunction) rotate,                METH_O,
                    "Rotates the camera"},
            {"zoomin",                (PyCFunction) zoomin,                METH_O,
                    "Zooms in the camera"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            GETTER_SETTER(x),
            GETTER_SETTER(y),
            GETTER_SETTER(position),
            GETTER_SETTER(rotation),
            GETTER_SETTER(zoom),

            {nullptr}
    };
}

PyTypeObject CameraType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Camera",
        sizeof(CameraObject),
        0,
        (destructor) camera::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) camera::repr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        "",
        (traverseproc) camera::traverse,
        (inquiry) camera::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        (PyMethodDef *) camera::methods,
        nullptr,
        (PyGetSetDef *) camera::getsetters,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) camera::init,
        nullptr,
        camera::new_,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        nullptr,
        nullptr
};

static struct PyModuleDef CameraModule = {
        PyModuleDef_HEAD_INIT,
        "camera",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_camera(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_camera()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&CameraModule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_PYOBJECT_CLASS(CameraType, "Camera");

    static void *PyCamera_API[PyCamera_API_pointers];
    PyObject * c_api_object;

    PyCamera_API[Camera_pytype_NUM] = (void *) Camera_pytype;
    c_api_object = PyCapsule_New((void *) PyCamera_API, "goopylib.ext.camera._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
