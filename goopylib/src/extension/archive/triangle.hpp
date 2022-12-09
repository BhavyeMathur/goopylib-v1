#ifndef GOOPYLIB_TRIANGLE_HPP
#define GOOPYLIB_TRIANGLE_HPP

struct TriangleObject {
    PyObject_HEAD
    int VBO;
    int VAO;
    bool buffersInitialised;

    int shader;

    float rotation;
    float scaleX;
    float scaleY;
    float x;
    float y;
    glm::mat4 rotationMatrix;
    glm::mat4 translationMatrix;
    glm::mat4 scaleMatrix;
    int transformMatrixLocation;

    WindowObject *window;
    TextureObject *fill;
};

namespace triangle {
    namespace {
        const int triangleIndices[3] = {0, 1, 2};
    }

    namespace object {
        static int traverse(TriangleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
            return 0;
        }

        static int clear(TriangleObject *self) {
            if (self->buffersInitialised) {
                glDeleteVertexArrays(1, &self->VAO);
                glDeleteBuffers(1, &self->VBO);
                glDeleteProgram(self->shader);

            }
            if ((PyObject *) self->window != Py_None) {
                window_::destroyTriangle(self->window, self);
            }

            return 0;
        }

        static void dealloc(TriangleObject *self) {
            PyObject_GC_UnTrack(self);
            clear(self);
            Py_TYPE(self)->tp_free((PyObject *) self);
        }

        static PyObject *tp_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            TriangleObject *self;
            self = (TriangleObject *) type->tp_alloc(type, 0);
            if (self != nullptr) {
                self->VBO = 0;
                self->VAO = 0;
                self->shader = 0;
                self->buffersInitialised = false;

                self->rotation = 0;
                self->scaleX = 1;
                self->scaleY = 1;
                self->translationMatrix = glm::mat4(1.0);
                self->rotationMatrix = glm::mat4(1.0);
                self->scaleMatrix = glm::mat4(1.0);

                self->window = (WindowObject *) Py_None;
                self->fill = (TextureObject *) PyObject_CallObject((PyObject * ) & texture::type::TextureType,
                                                                   Py_BuildValue("((iii))", 255, 255, 255));
            }
            return (PyObject *) self;
        }

        static int init(TriangleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            CHECK_GLFW_CONTEXT(-1)

            float x1, y1, x2, y2, x3, y3;
            if (!PyArg_ParseTuple(args, "(ff)(ff)(ff)", &x1, &y1, &x2, &y2, &x3, &y3)) {
                return -1;
            }

            self->x = (x1 + x2 + x3) / 3;
            self->y = (y1 + y2 + y3) / 3;

            x1 -= self->x;
            x2 -= self->x;
            x3 -= self->x;
            y1 -= self->y;
            y2 -= self->y;
            y3 -= self->y;

            float minx, miny, maxx, maxy;
            if (x1 > x2) {
                minx = x2;
                maxx = x1;
            }
            else {
                minx = x1;
                maxx = x2;
            }
            if (x3 > maxx) {
                maxx = x3;
            }
            else if (x3 < minx) {
                minx = x3;
            }

            if (y1 > y2) {
                miny = y2;
                maxy = y1;
            }
            else {
                miny = y1;
                maxy = y2;
            }
            if (y3 > maxy) {
                maxy = y3;
            }
            else if (y3 < miny) {
                miny = y3;
            }

            float width = maxx - minx;
            float height = maxy - miny;

            self->translationMatrix = glm::translate(self->translationMatrix, glm::vec3(self->x, self->y, 0));

            const char *vertexShaderSource = "#version 330 core\n"
                                             "layout (location = 0) in vec2 position;"
                                             "layout (location = 1) in vec2 texCoord;"
                                             "uniform mat4 transform;"
                                             "out vec2 TexCoord;"
                                             "void main() {"
                                             "  gl_Position = transform * vec4(position, 0.0f, 1.0f);"
                                             "  TexCoord = texCoord;"
                                             "}";
            const char *fragmentShaderSource = "#version 330 core\n"
                                               "out vec4 FragColor;"
                                               "in vec2 TexCoord;"
                                               "uniform sampler2D Texture;"
                                               "void main() {"
                                               //"    FragColor = vec4(TexCoord.x, TexCoord.y, 1.0f, 1.0f);"
                                               "    FragColor = texture(Texture, TexCoord);"
                                               "}";

            self->shader = createShader(vertexShaderSource, fragmentShaderSource);
            self->transformMatrixLocation = glGetUniformLocation(self->shader, "transform");

            float vertexData[] = {x1, y1, (x1 - minx) / width, (y1 - miny) / height,
                                  x2, y2, (x2 - minx) / width, (y2 - miny) / height,
                                  x3, y3, (x3 - minx) / width, (y3 - miny) / height};

            glGenVertexArrays(1, &self->VAO);
            glGenBuffers(1, &self->VBO);
            glBindVertexArray(self->VAO);

            glBindBuffer(GL_ARRAY_BUFFER, self->VBO);
            glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertexData, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            return 0;
        }

        static PyObject *repr(TriangleObject *Py_UNUSED(self)) {
            return PyUnicode_FromString("Triangle()");
        }
    }

    namespace attributes {
        // X Position
        static int set_x(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
            if (!PyNumber_Check(value)) {
                RAISE_TYPE_ERROR(-1, "number argument expected, got %S", PyObject_Type(value))
            }

            auto x = (float) PyFloat_AsDouble(value);
            self->translationMatrix = glm::translate(self->translationMatrix, glm::vec3(x - self->x, 0, 0));
            self->x = x;

            return 0;
        }

        static PyObject *get_x(TriangleObject *self, void *Py_UNUSED(closure)) {
            return PyFloat_FromDouble(self->x);
        }

        // Y Position
        static int set_y(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
            if (!PyNumber_Check(value)) {
                RAISE_TYPE_ERROR(-1, "number argument expected, got %S", PyObject_Type(value))
            }

            auto y = (float) PyFloat_AsDouble(value);
            float dy = y - self->y;
            self->translationMatrix = glm::translate(self->translationMatrix,
                                                     glm::vec3(0, dy, 0));
            self->y = y;

            return 0;
        }

        static PyObject *get_y(TriangleObject *self, void *Py_UNUSED(closure)) {
            return PyFloat_FromDouble(self->y);
        }

        // Y Position
        static int set_rotation(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
            if (!PyNumber_Check(value)) {
                RAISE_TYPE_ERROR(-1, "number argument expected, got %S", PyObject_Type(value))
            }

            auto angle = glm::radians((float) PyFloat_AsDouble(value));
            self->rotationMatrix = glm::rotate(self->rotationMatrix,
                                               angle - self->rotation,
                                               glm::vec3(0.0f, 0.0f, 1.0f));
            self->rotation = angle;

            return 0;
        }

        static PyObject *get_rotation(TriangleObject *self, void *Py_UNUSED(closure)) {
            return PyFloat_FromDouble(glm::degrees(self->rotation));
        }

        // X Scale
        static int set_xscale(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
            if (!PyNumber_Check(value)) {
                RAISE_TYPE_ERROR(-1, "number argument expected, got %S", PyObject_Type(value))
            }

            auto scaleX = (float) PyFloat_AsDouble(value);
            self->scaleMatrix = glm::scale(self->scaleMatrix,
                                           glm::vec3(scaleX / self->scaleX, 1.0f, 1.0f));
            self->scaleX = scaleX;

            return 0;
        }

        static PyObject *get_xscale(TriangleObject *self, void *Py_UNUSED(closure)) {
            return PyFloat_FromDouble(self->scaleX);
        }

        // X Scale
        static int set_yscale(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
            if (!PyNumber_Check(value)) {
                RAISE_TYPE_ERROR(-1, "number argument expected, got %S", PyObject_Type(value))
            }

            auto scaleY = (float) PyFloat_AsDouble(value);
            self->scaleMatrix = glm::scale(self->scaleMatrix,
                                           glm::vec3(1.0f, scaleY / self->scaleY, 1.0f));
            self->scaleY = scaleY;

            return 0;
        }

        static PyObject *get_yscale(TriangleObject *self, void *Py_UNUSED(closure)) {
            return PyFloat_FromDouble(self->scaleY);
        }

        // Fill
        static int set_fill(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
            if (texture::isInstance(value)) {
                TextureObject *tmp = self->fill;
                Py_INCREF(value);
                self->fill = (TextureObject *) value;
                Py_DECREF(tmp);
            }
            else {
                self->fill = (TextureObject *) PyObject_CallObject((PyObject * ) & texture::type::TextureType,
                                                                   PyTuple_Pack(1, value));
            }

            return 0;
        }

        static PyObject *get_fill(TriangleObject *self, void *Py_UNUSED(closure)) {
            RETURN_PYOBJECT((PyObject *) self->fill)
        }
    }

    namespace methods {
        static PyObject *draw(TriangleObject *self, PyObject *value) {
            if (!window_::isInstance(value)) {
                RAISE_TYPE_ERROR(nullptr, "goopylib Window expected, got %S", PyObject_Type(value))
            }
            self->window = (WindowObject *) value;
            window_::drawTriangle(self->window, self);
            RETURN_PYOBJECT((PyObject *) self)
        }

        static PyObject *move(TriangleObject *self, PyObject *args) {
            float dx, dy;
            if (!PyArg_ParseTuple(args, "ff", &dx, &dy)) {
                return nullptr;
            }
            self->translationMatrix = glm::translate(self->translationMatrix,
                                                     glm::vec3(dx, dy, 0));
            self->x += dx;
            self->y += dy;
            RETURN_PYOBJECT((PyObject *) self)
        }

        static PyObject *scale(TriangleObject *self, PyObject *args) {
            float scaleX, scaleY;
            if (PyTuple_GET_SIZE(args) == 1) {
                if (!PyArg_ParseTuple(args, "f", &scaleX)) {
                    return nullptr;
                }
                scaleY = scaleX;
            }
            else {
                if (!PyArg_ParseTuple(args, "ff", &scaleX, &scaleY)) {
                    return nullptr;
                }
            }

            self->scaleMatrix = glm::scale(self->scaleMatrix,
                                           glm::vec3(scaleX, scaleY, 1.0f));
            self->scaleX *= scaleX;
            self->scaleY *= scaleY;
            RETURN_PYOBJECT((PyObject *) self)
        }
    }

    namespace type {
        static PyMethodDef methods[] = {
                {"draw",  (PyCFunction) methods::draw,  METH_O,
                        "Draws the triangle to a Window"},
                {"move",  (PyCFunction) methods::move,  METH_VARARGS,
                        "Moves the triangle"},
                {"scale", (PyCFunction) methods::scale, METH_VARARGS,
                        "Scales the triangle"},
                {nullptr}
        };

        static PyGetSetDef getsetters[] = {
                {"x",        (getter) triangle::attributes::get_x,        (setter) triangle::attributes::set_x,        "triangle x-position", nullptr},
                {"y",        (getter) triangle::attributes::get_y,        (setter) triangle::attributes::set_y,        "triangle y-position", nullptr},
                {"rotation", (getter) triangle::attributes::get_rotation, (setter) triangle::attributes::set_rotation, "triangle rotation",   nullptr},
                {"xscale",   (getter) triangle::attributes::get_xscale,   (setter) triangle::attributes::set_xscale,   "triangle x-scale",    nullptr},
                {"yscale",   (getter) triangle::attributes::get_yscale,   (setter) triangle::attributes::set_yscale,   "triangle y-scale",    nullptr},

                {"fill",     (getter) triangle::attributes::get_fill,     (setter) triangle::attributes::set_fill,     "triangle fill",       nullptr},

                {nullptr}
        };

        static PyTypeObject TriangleType = {
                PyVarObject_HEAD_INIT(nullptr, 0)
                        .tp_name = "goopylib.Triangle",
                .tp_doc = PyDoc_STR("Triangle objects"),
                .tp_basicsize = sizeof(TriangleObject),
                .tp_itemsize = 0,
                .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
                .tp_methods = methods,
                .tp_getset = getsetters,
                .tp_new = object::tp_new,
                .tp_init = (initproc) object::init,
                .tp_dealloc = (destructor) object::dealloc,
                .tp_traverse = (traverseproc) object::traverse,
                .tp_clear = (inquiry) object::clear,
                .tp_repr = (reprfunc) object::repr,
        };
    }
}

namespace triangle_ {
    void draw(TriangleObject *self, glm::mat4 projection) {
        glUseProgram(self->shader);
        glUniformMatrix4fv(self->transformMatrixLocation, 1, GL_FALSE, glm::value_ptr(
                projection * (self->translationMatrix * (self->scaleMatrix * self->rotationMatrix))));
        glBindTexture(GL_TEXTURE_2D, self->fill->id);
        glBindVertexArray(self->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

int PyInit_triangle(PyObject *m) {
    EXPOSE_CLASS(triangle::type::TriangleType, "Triangle")
    return 0;
}

#endif //GOOPYLIB_TRIANGLE_HPP
