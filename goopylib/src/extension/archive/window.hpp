struct KeyCallback {
    PyObject *callback;
    int keycode;
};

struct WindowObject {
    int windowed_width;

    ColorObject *background;

    int windowed_height;

    int windowed_xpos;
    int windowed_ypos;

    int aspect_ratio_numerator;
    int aspect_ratio_denominator;

    std::vector<KeyCallback> key_callbacks;
    int key_modifiers;

    std::vector<TriangleObject *> triangleInstances;
};

namespace window {
    namespace attributes {
        // Frame size & Content Scale
        static PyObject *get_frame_size(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            int left, top, right, bottom;
            glfwGetWindowFrameSize(self->window, &left, &top, &right, &bottom);
            return PyTuple_Pack(4, PyLong_FromLong(left), PyLong_FromLong(top), PyLong_FromLong(right), PyLong_FromLong(bottom));
        }

        static PyObject *get_content_scale(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            float xscale, yscale;
            glfwGetWindowContentScale(self->window, &xscale, &yscale);
            return PyTuple_Pack(2, PyFloat_FromDouble(xscale), PyFloat_FromDouble(yscale));
        }

        // Aspect Ratio
        static PyObject *set_aspect_ratio(WindowObject *self, PyObject *args, PyObject *kwds) {
            CHECK_WINDOW_ACTIVE(nullptr)

            static const char *kwlist[] = {"numerator", "denominator", nullptr};

            PyObject *tmp_numerator, *tmp_denominator;
            if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO", (char**) kwlist, &tmp_numerator, &tmp_denominator)) {
                return nullptr;
            }

            if (tmp_numerator == Py_None and tmp_denominator == Py_None) {
                glfwSetWindowAspectRatio(self->window, GLFW_DONT_CARE, GLFW_DONT_CARE);
                Py_RETURN_NONE;
            }
            if (!PyLong_Check(tmp_numerator)) {
                RAISE_TYPE_ERROR(nullptr, "integer argument expected, got %S", PyObject_Type(tmp_numerator))
            }
            if (!PyLong_Check(tmp_denominator)) {
                RAISE_TYPE_ERROR(nullptr, "integer argument expected, got %S", PyObject_Type(tmp_denominator))
            }
            int numerator = (int) PyLong_AsLong(tmp_numerator);
            int denominator = (int) PyLong_AsLong(tmp_denominator);

            if (numerator <= 0) {
                RAISE_VALUE_ERROR(nullptr, "aspect ratio numerator must be greater than 0")
            }
            if (denominator <= 0) {
                RAISE_VALUE_ERROR(nullptr, "aspect ratio denominator must be greater than 0")
            }

            int g = gcd(numerator, denominator);
            glfwSetWindowAspectRatio(self->window, numerator / g, denominator / g);
            Py_RETURN_NONE;
        }

        static PyObject *get_aspect_ratio(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            int g = gcd(self->width, self->height);
            self->aspect_ratio_numerator = self->width / g;
            self->aspect_ratio_denominator = self->height / g;

            return PyTuple_Pack(2, PyLong_FromLong(self->aspect_ratio_numerator),
                                PyLong_FromLong(self->aspect_ratio_denominator));
        }

        // -------------------------------------------------------------------------------------------------------------

        // Framebuffer Size
        static int set_framebuffer_size(WindowObject *Py_UNUSED(self), PyObject *Py_UNUSED(value), void *Py_UNUSED(closure)) {
            PyErr_SetString(PyExc_NotImplementedError, "cannot change the size of the window framebuffer");
            return -1;
        }

        static PyObject *get_framebuffer_size(WindowObject *self, void *Py_UNUSED(closure)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            int width, height;
            glfwGetFramebufferSize(self->window, &width, &height);
            return PyTuple_Pack(2, PyLong_FromLong(width), PyLong_FromLong(height));
        }

        // Background Color
        static int set_background(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
            CHECK_WINDOW_ACTIVE(-1)

            ColorObject *tmp = self->background;

            if (color::isInstance(value)) {
                Py_INCREF(value);
                self->background = (ColorObject *) value;
                Py_DECREF(tmp);
            }
            else {
                self->background = (ColorObject *) PyObject_CallOneArg((PyObject *) &color::type::ColorType, value);
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
    }

    namespace states {
        static PyObject *fullscreen(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            if (!glfwGetWindowMonitor(self->window)) {
                self->windowed_width = self->width;
                self->windowed_height = self->height;
                self->windowed_xpos = self->xpos;
                self->windowed_ypos = self->ypos;

                GLFWmonitor *monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(self->window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }
            Py_RETURN_NONE;
        }

        static PyObject *unfullscreen(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            if (glfwGetWindowMonitor(self->window) and self->is_active) {
                glfwSetWindowMonitor(self->window, nullptr, self->windowed_xpos, self->windowed_ypos, self->windowed_width,
                                     self->windowed_height, 0);
            }
            Py_RETURN_NONE;
        }

        static PyObject *minimize(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            glfwIconifyWindow(self->window);
            Py_RETURN_NONE;
        }

        static PyObject *maximize(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            glfwMaximizeWindow(self->window);
            Py_RETURN_NONE;
        }

        static PyObject *restore(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            glfwRestoreWindow(self->window);
            Py_RETURN_NONE;
        }

        static PyObject *show(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            glfwPollEvents(); // TODO I have no idea why these PollEvent functions are needed here
            glfwShowWindow(self->window);
            glfwPollEvents();

            Py_RETURN_NONE;
        }

        static PyObject *hide(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            glfwPollEvents(); // TODO I have no idea why these PollEvent functions are needed here
            glfwHideWindow(self->window);
            glfwPollEvents();

            Py_RETURN_NONE;
        }

        static PyObject *set_focus(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            glfwFocusWindow(self->window);
            Py_RETURN_NONE;
        }

        static PyObject *has_focus(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            if (glfwGetWindowAttrib(self->window, GLFW_FOCUSED)) {
                Py_RETURN_TRUE;
            }
            Py_RETURN_FALSE;
        }

        static PyObject *request_attention(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            glfwRequestWindowAttention(self->window);
            Py_RETURN_NONE;
        }
    }

    namespace events {
        static PyObject *is_mouse_hovering(WindowObject *self, PyObject *Py_UNUSED(args)) {
            CHECK_WINDOW_ACTIVE(nullptr)

            if (glfwGetWindowAttrib(self->window, GLFW_HOVERED)) {
                Py_RETURN_TRUE;
            }
            Py_RETURN_FALSE;
        }

        static PyObject *check_key(WindowObject *self, PyObject *key) {
            CHECK_WINDOW_ACTIVE(nullptr)

            if (!PyLong_Check(key)) {
                RAISE_TYPE_ERROR(nullptr, "key expected, got %S", PyObject_Type(key))
            }

            int state = glfwGetKey(self->window, (int) PyLong_AsLong(key));
            if (glfwGetError(nullptr) == GLFW_INVALID_ENUM) {
                RAISE_VALUE_ERROR(nullptr, "invalid key received")
            }

            if (state == GLFW_PRESS) {
                Py_RETURN_TRUE;
            } else {
                Py_RETURN_FALSE;
            }
        }

        void key_callback(GLFWwindow *window, int key, int Py_UNUSED(scancode), int action, int mods) {
            for (WindowObject *instance: window::instances) {
                if (instance->window == window) {
                    instance->key_modifiers = mods;
                    for (KeyCallback key_callback: instance->key_callbacks) {
                        if (key_callback.keycode == key) {
                            PyGILState_STATE gstate = PyGILState_Ensure();
                            PyObject_CallOneArg(key_callback.callback, PyLong_FromLong(action));
                            PyGILState_Release(gstate);
                        }
                    }
                    break;
                }
            }
        }

        static PyObject *set_key_callback(WindowObject *self, PyObject *args, PyObject *kwds) {
            CHECK_WINDOW_ACTIVE(nullptr)

            static const char *kwlist[] = {"key", "callback", nullptr};

            PyObject *callback, *key;
            if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO", (char **) kwlist, &key, &callback)) {
                return nullptr;
            }

            if (!PyLong_Check(key)) {
                RAISE_TYPE_ERROR(nullptr, "key expected, got %S", PyObject_Type(key))
            }

            int keycode = (int) PyLong_AsLong(key);

            glfwGetKeyScancode(keycode);
            if (glfwGetError(nullptr) == GLFW_INVALID_ENUM) {
                RAISE_VALUE_ERROR(nullptr, "invalid key received")
            }

            if (callback == Py_None) {
                int i = 0;
                for (KeyCallback key_callback: self->key_callbacks) {
                    if (key_callback.keycode == keycode) {
                        self->key_callbacks.erase(self->key_callbacks.begin() + i);
                        break;
                    }
                    i++;
                }
                Py_RETURN_NONE;
            }
            else if (PyCallable_Check(callback)) {
                if (PyFunction_Check(callback) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(callback), "co_argcount")) != 1) {
                    RAISE_VALUE_ERROR(nullptr, "callback must take 1 argument: action")
                }

                bool callback_set = false;
                for (KeyCallback key_callback: self->key_callbacks) {
                    if (key_callback.keycode == keycode) {
                        key_callback.callback = callback;
                        callback_set = true;
                        break;
                    }
                }
                if (!callback_set) {
                    KeyCallback new_callback = {callback, keycode};
                    self->key_callbacks.push_back(new_callback);
                }

                Py_RETURN_NONE;
            }
            else {
                RAISE_TYPE_ERROR(nullptr, "function argument expected, got %S", PyObject_Type(callback))
            }
        }

        static PyObject *check_shift_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
            if (self->key_modifiers & 1) {
                Py_RETURN_TRUE;
            }
            Py_RETURN_FALSE;
        }

        static PyObject *check_control_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
            if (self->key_modifiers & (1 << 1)) {
                Py_RETURN_TRUE;
            }
            Py_RETURN_FALSE;
        }

        static PyObject *check_alt_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
            if (self->key_modifiers & (1 << 2)) {
                Py_RETURN_TRUE;
            }
            Py_RETURN_FALSE;
        }

        static PyObject *check_super_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
            if (self->key_modifiers & (1 << 3)) {
                Py_RETURN_TRUE;
            }
            Py_RETURN_FALSE;
        }
    }

    namespace type {
        static PyMethodDef methods[] = {
                {"set_focus", (PyCFunction) window::states::set_focus, METH_NOARGS,
                        "Sets the input focus to the Window"},
                {"has_focus", (PyCFunction) window::states::has_focus, METH_NOARGS,
                        "Returns whether the Window has input focus"},
                {"request_attention", (PyCFunction) window::states::request_attention, METH_NOARGS,
                        "Requests for user attention on the window"},

                {"fullscreen", (PyCFunction) window::states::fullscreen, METH_NOARGS,
                        "Makes the Window fullscreen"},
                {"unfullscreen", (PyCFunction) window::states::unfullscreen, METH_NOARGS,
                        "Makes the Window windowed"},
                {"minimize", (PyCFunction) window::states::minimize, METH_NOARGS,
                        "Minimizes the Window"},
                {"maximize", (PyCFunction) window::states::maximize, METH_NOARGS,
                        "Maximizes the Window"},
                {"restore", (PyCFunction) window::states::restore, METH_NOARGS,
                        "Restores the Window"},

                {"hide", (PyCFunction) window::states::hide, METH_NOARGS,
                        "Makes the Window invisible"},
                {"show", (PyCFunction) window::states::show, METH_NOARGS,
                        "Makes the Window visible"},

                {"get_frame_size", (PyCFunction) window::attributes::get_frame_size, METH_NOARGS,
                        "Returns a tuple (left, top, right, bottom) containing the frame size of the window"},
                {"get_content_scale", (PyCFunction) window::attributes::get_content_scale, METH_NOARGS,
                        "Returns a tuple (xscale, yscale) containing the scale of the content on the window"},

                {"set_aspect_ratio", (PyCFunction) window::attributes::set_aspect_ratio, METH_VARARGS | METH_KEYWORDS,
                        "Sets the aspect ratio of the window"},
                {"get_aspect_ratio", (PyCFunction) window::attributes::get_aspect_ratio, METH_NOARGS,
                        "Returns a tuple (numerator, denominator) containing the aspect ratio of the window"},

                // Window Events

                {"is_mouse_hovering", (PyCFunction) window::events::is_mouse_hovering, METH_NOARGS,
                        "Returns whether the mouse is hovering over the Window"},
                {"check_key", (PyCFunction) window::events::check_key, METH_O,
                        "Returns whether the key specified is being pressed"},
                {"check_shift_key", (PyCFunction) window::events::check_shift_key, METH_NOARGS,
                        "Returns whether the shift key is being pressed"},
                {"check_alt_key", (PyCFunction) window::events::check_alt_key, METH_NOARGS,
                        "Returns whether the alt key is being pressed"},
                {"check_control_key", (PyCFunction) window::events::check_control_key, METH_NOARGS,
                        "Returns whether the control key is being pressed"},
                {"check_super_key", (PyCFunction) window::events::check_super_key, METH_NOARGS,
                        "Returns whether the super key is being pressed"},
                {"set_key_callback", (PyCFunction) window::events::set_key_callback, METH_VARARGS | METH_KEYWORDS,
                        "Sets a callback function for a keyboard event"},
        };

        static PyGetSetDef getsetters[] = {
                {"background", (getter) window::attributes::get_background, (setter) window::attributes::set_background, "window background", nullptr},
        };
    }
}

namespace window_ {
    void drawTriangle(WindowObject * self, TriangleObject * triangle) {
        if (std::find(self->triangleInstances.begin(), self->triangleInstances.end(), triangle) == self->triangleInstances.end()) {
            Py_INCREF(triangle);
            self->triangleInstances.push_back(triangle);
        }
    }

    void destroyTriangle(WindowObject * self, TriangleObject * triangle) {
        Py_DECREF(triangle);
        self->triangleInstances.erase(std::find(self->triangleInstances.begin(), self->triangleInstances.end(), triangle));
    }

    bool isInstance(PyObject *object) {
        return PyObject_IsInstance(object, (PyObject *) &window::type::WindowType);
    }
}
