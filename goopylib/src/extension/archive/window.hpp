struct WindowObject {
    ColorObject *background;
    std::vector<TriangleObject *> triangleInstances;
};

namespace window {
    static int set_background(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        ColorObject *tmp = self->background;

        if (color::isInstance(value)) {
            Py_INCREF(value);
            self->background = (ColorObject *) value;
            Py_DECREF(tmp);
        }
        else {
            self->background = (ColorObject *) PyObject_CallOneArg((PyObject * ) & color::type::ColorType, value);
            Py_DECREF(tmp);

            if (self->background == nullptr) {
                RAISE_TYPE_ERROR(-1, "color argument expected, got %S", PyObject_Type(value))
            }
        }
        glClearColor(self->background->r, self->background->g, self->background->b, 1);
        return 0;
    }

    static PyObject *get_background(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return (PyObject *) self->background;
    }

    static PyGetSetDef getsetters[] = {
            {"background", (getter) window::attributes::get_background, (setter) window::attributes::set_background,
             "window background", nullptr},
    };
}

namespace window_ {
    void drawTriangle(WindowObject *self, TriangleObject *triangle) {
        if (std::find(self->triangleInstances.begin(), self->triangleInstances.end(), triangle) ==
            self->triangleInstances.end()) {
            Py_INCREF(triangle);
            self->triangleInstances.push_back(triangle);
        }
    }

    void destroyTriangle(WindowObject *self, TriangleObject *triangle) {
        Py_DECREF(triangle);
        self->triangleInstances.erase(
                std::find(self->triangleInstances.begin(), self->triangleInstances.end(), triangle));
    }
}
