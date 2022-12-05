#ifndef GOOPYLIB_TRIANGLE_H
#define GOOPYLIB_TRIANGLE_H

struct TriangleObject;

namespace triangle {
    namespace {}

    namespace object {
        static int traverse(TriangleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg));

        static int clear(TriangleObject *self);

        static void dealloc(TriangleObject *self);

        static PyObject *tp_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds));

        static int init(TriangleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds));

        static PyObject *repr(TriangleObject *Py_UNUSED(self));
    }

    namespace attributes {
        // X Position
        static int set_x(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure));

        static PyObject *get_x(TriangleObject *self, void *Py_UNUSED(closure));

        // Y Position
        static int set_y(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure));

        static PyObject *get_y(TriangleObject *self, void *Py_UNUSED(closure));

        // Rotation
        static int set_rotation(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure));

        static PyObject *get_rotation(TriangleObject *self, void *Py_UNUSED(closure));

        // X Scale
        static int set_xscale(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure));

        static PyObject *get_xscale(TriangleObject *self, void *Py_UNUSED(closure));

        // X Scale
        static int set_yscale(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure));

        static PyObject *get_yscale(TriangleObject *self, void *Py_UNUSED(closure));
    }

    namespace methods {
        static PyObject *draw(TriangleObject *self, PyObject *args);

        static PyObject *move(TriangleObject *self, PyObject *args);

        static PyObject *scale(TriangleObject *self, PyObject *args);
    }

    namespace type {}
}

namespace triangle_ {
    void draw(TriangleObject *object);
}

int PyInit_triangle(PyObject *m);

#endif //GOOPYLIB_TRIANGLE_H
