#pragma once

#include "goopylib/header.h"

struct CameraObject;


// Camera Core
namespace camera {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(CameraObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(CameraObject *self);

    static int traverse(CameraObject *self, visitproc visit, void *arg);

    static int clear(CameraObject *self);

    static void dealloc(CameraObject *self);
}

// Camera methods
namespace camera {
    static PyObject *set_projection(CameraObject *self, PyObject *args);

    static PyObject *get_visible_frame(CameraObject *self, PyObject *args);

    static PyObject *get_projection_frame(CameraObject *self, PyObject *args);
    
    static PyObject *get_visible_width(CameraObject *self, PyObject *args);
    
    static PyObject *get_visible_height(CameraObject *self, PyObject *args);
    
    static PyObject *get_projection_width(CameraObject *self, PyObject *args);
    
    static PyObject *get_projection_height(CameraObject *self, PyObject *args);

    static PyObject *get_visible_size(CameraObject *self, PyObject *args);

    static PyObject *get_projection_size(CameraObject *self, PyObject *args);

    static PyObject *move(CameraObject *self, PyObject *args);

    static PyObject *rotate(CameraObject *self, PyObject *arg);

    static PyObject *zoomin(CameraObject *self, PyObject *arg);
}

// Camera getters & setters
namespace camera {
    static PyObject *get_x(CameraObject *self, void *closure);

    static int set_x(CameraObject *self, PyObject *value, void *closure);

    static PyObject *get_y(CameraObject *self, void *closure);

    static int set_y(CameraObject *self, PyObject *value, void *closure);

    static PyObject *get_position(CameraObject *self, void *closure);

    static int set_position(CameraObject *self, PyObject *value, void *closure);

    static PyObject *get_rotation(CameraObject *self, void *closure);

    static int set_rotation(CameraObject *self, PyObject *value, void *closure);

    static PyObject *get_zoom(CameraObject *self, void *closure);

    static int set_zoom(CameraObject *self, PyObject *value, void *closure);
}


extern PyTypeObject CameraType;
