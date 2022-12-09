#ifndef GOOPYLIB_TEXTURE_HPP
#define GOOPYLIB_TEXTURE_HPP

struct TextureObject {
    PyObject_HEAD
    unsigned char *data;
    int id;
};

namespace texture {
    namespace object {
        static int traverse(TextureObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
            return 0;
        }

        static int clear(TextureObject *self) {
            glDeleteTextures(1, &self->id);
            return 0;
        }

        static void dealloc(TextureObject *self) {
            PyObject_GC_UnTrack(self);
            clear(self);
            Py_TYPE(self)->tp_free((PyObject *) self);
        }

        static PyObject *tp_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            TextureObject *self;
            self = (TextureObject *) type->tp_alloc(type, 0);
            if (self != nullptr) {
                self->id = 0;
            }
            return (PyObject *) self;
        }

        static int init(TextureObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            int width = 1;
            int height = 1;

            int red, green, blue;
            float alpha = 1.0f;
            PyObject *arg;
            ColorObject *rgb;

            if (PyArg_ParseTuple(args, "iii|fii", &red, &green, &blue, &alpha, &width, &height) or
                PyArg_ParseTuple(args, "(iii)|fii", &red, &green, &blue, &alpha, &width, &height) or
                PyArg_ParseTuple(args, "(iiif)|ii", &red, &green, &blue, &alpha, &width, &height)) {
                PyErr_Clear();
                rgb = (ColorObject *) PyObject_CallOneArg((PyObject * ) & color::type::ColorType,
                                                          Py_BuildValue("iiif", red, green, blue, alpha));
            }
            else if (PyArg_ParseTuple(args, "U|fii", &arg, &alpha, &width, &height) or
                     PyArg_ParseTuple(args, "(Uf)|ii", &arg, &alpha, &width, &height)) {
                PyErr_Clear();
                rgb = (ColorObject *) PyObject_Call((PyObject * ) & color::type::ColorType,
                                                    Py_BuildValue("Of", arg, alpha), nullptr);
            }
            else if (PyArg_ParseTuple(args, "O|ii", &arg, &width, &height) and color::isInstance(arg)) {
                PyErr_Clear();
                rgb = (ColorObject *) arg;
            }
            else {
                RAISE_VALUE_ERROR(-1, "invalid texture format")
            }

            self->data = new unsigned char[width * height * 3];
            for (int i = 0; i < width * height * 3; i += 3) {
                self->data[i] = rgb->red;
                self->data[i + 1] = rgb->green;
                self->data[i + 2] = rgb->blue;
            }

            glGenTextures(1, &self->id);
            glBindTexture(GL_TEXTURE_2D, self->id);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, self->data);
            glGenerateMipmap(GL_TEXTURE_2D);

            return 0;
        }
    }

    namespace type {
        static PyTypeObject TextureType = {
                PyVarObject_HEAD_INIT(nullptr, 0)
                        .tp_name = "goopylib.Texture",
                .tp_doc = PyDoc_STR("Texture object"),
                .tp_basicsize = sizeof(TextureObject),
                .tp_itemsize = 0,
                .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
                .tp_new = object::tp_new,
                .tp_init = (initproc) object::init,
                .tp_dealloc = (destructor) object::dealloc,
                .tp_traverse = (traverseproc) object::traverse,
                .tp_clear = (inquiry) object::clear,
        };
    }

    namespace {
        bool isInstance(PyObject *object) {
            return PyObject_IsInstance(object, (PyObject * ) & texture::type::TextureType);
        }
    }
}

int PyInit_texture(PyObject *m) {
    EXPOSE_CLASS(texture::type::TextureType, "Texture")
    return 0;
}

#endif //GOOPYLIB_TEXTURE_HPP
