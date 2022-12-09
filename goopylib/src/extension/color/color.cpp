#include "color.h"

// Color Object
namespace color {
    static int init(ColorObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_COLOR_TRACE("Initializing gp.Color()");

        switch (PyTuple_GET_SIZE(args)) {
            case 0:
                self->color = std::make_shared<gp::Color>();
                break;

            // Hexstring
            case 1:
            case 2: {
                PyObject *obj;
                float alpha = 1.0f;

                if (!PyArg_ParseTuple(args, "O|f", &obj, &alpha)) {
                    return -1;
                }

                if (PyUnicode_Check(obj)) {
                    CHECK_ALPHA(-1)

                    const char *hexstring = PyUnicode_AsUTF8(obj);

                    try {
                        gp::RGB color = gp::hex::toRGB(hexstring);
                        self->color = std::make_shared<gp::Color>(color, alpha);
                    }
                    catch (const std::invalid_argument &iaex) {
                        RAISE_VALUE_ERROR(-1, "invalid hexstring format")
                    }
                }
                else if (color::isinstance(obj)) {
                    self->color = std::make_shared<gp::Color>(*(((ColorObject *) obj)->color));
                }
                else {
                    RAISE_VALUE_ERROR(-1, "invalid color format")
                }

                break;
            }
                // RGB or RGBA
            case 3:
            case 4: {
                int red, green, blue;
                float alpha = 1.0f;

                if (!PyArg_ParseTuple(args, "III|f", &red, &green, &blue, &alpha)) {
                    return -1;
                }

                CHECK_RGBA(-1)

                self->color = std::make_shared<gp::Color>(red, green, blue, alpha);
                break;
            }

            default:
            RAISE_VALUE_ERROR(-1, "invalid color format")
        }

        return 0;
    }

    static PyObject *repr(ColorObject *self) {
        return PyUnicode_FromString(self->color->toString().c_str());
    }

    static int traverse(ColorObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(ColorObject *Py_UNUSED(self)) {
        GP_PY_COLOR_TRACE("Clearing gp.Color()");
        return 0;
    }

    static void dealloc(ColorObject *self) {
        GP_PY_COLOR_TRACE("Deallocating gp.Color()");

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// PyNumber API
namespace color {
    static PyObject *PyNumber_Add(PyObject *o1, PyObject *o2) {
        int red, green, blue;
        float alpha = 1.0f;

        if (color::isinstance(o2)) {
            red = ((ColorObject *) o2)->color->getRed();
            green = ((ColorObject *) o2)->color->getGreen();
            blue = ((ColorObject *) o2)->color->getBlue();

            alpha = ((ColorObject *) o2)->color->getAlpha();
        }
        else {
            #if GP_ERROR_CHECKING
            if (!PyLong_Check(o2)) {
                RAISE_TYPE_ERROR(nullptr, "integer or color", o2)
            }
            #endif

            red = (int) PyLong_AsLong(o2);
            green = red;
            blue = red;
        }

        if (color::isinstance(o1)) {
            red += ((ColorObject *) o1)->color->getRed();
            green += ((ColorObject *) o1)->color->getGreen();
            blue += ((ColorObject *) o1)->color->getBlue();

            alpha = ((ColorObject *) o1)->color->getAlpha();
        }
        else {
            #if GP_ERROR_CHECKING
            if (!PyLong_Check(o1)) {
                RAISE_TYPE_ERROR(nullptr, "integer or color", o1)
            }
            #endif

            int val = (int) PyLong_AsLong(o1);
            red += val;
            green += val;
            blue += val;
        }

        return color::create(red, green, blue, alpha);
    }

    static PyObject *PyNumber_Subtract(PyObject *o1, PyObject *o2) {
        int red, green, blue;
        float alpha = 1.0f;

        if (color::isinstance(o2)) {
            red = -((ColorObject *) o2)->color->getRed();
            green = -((ColorObject *) o2)->color->getGreen();
            blue = -((ColorObject *) o2)->color->getBlue();

            alpha = ((ColorObject *) o2)->color->getAlpha();
        }
        else {
            #if GP_ERROR_CHECKING
            if (!PyLong_Check(o2)) {
                RAISE_TYPE_ERROR(nullptr, "integer or color", o2)
            }
            #endif

            red = -(int) PyLong_AsLong(o2);
            green = red;
            blue = red;
        }

        if (color::isinstance(o1)) {
            red += ((ColorObject *) o1)->color->getRed();
            green += ((ColorObject *) o1)->color->getGreen();
            blue += ((ColorObject *) o1)->color->getBlue();

            alpha = ((ColorObject *) o1)->color->getAlpha();
        }
        else {
            #if GP_ERROR_CHECKING
            if (!PyLong_Check(o1)) {
                RAISE_TYPE_ERROR(nullptr, "integer or color", o1)
            }
            #endif

            int val = (int) PyLong_AsLong(o1);
            red += val;
            green += val;
            blue += val;
        }

        return color::create(red, green, blue, alpha);
    }

    static PyObject *PyNumber_InPlaceAdd(PyObject *o1, PyObject *o2) {
        #if GP_ERROR_CHECKING
        if (!color::isinstance(o1)) {
            PyErr_Format(PyExc_TypeError, "unsupported operand type(s) for +=: '%s' and '%s'", TYPE_NAME(o1), TYPE_NAME(o2));
            return nullptr;
        }
        #endif

        if (color::isinstance(o2)) {
            *((ColorObject *) o1)->color += *((ColorObject *) o1)->color;
        }
        else {
            #if GP_ERROR_CHECKING
            if (!PyLong_Check(o2)) {
                PyErr_Format(PyExc_TypeError, "unsupported operand type(s) for +=: '%s' and '%s'", TYPE_NAME(o1), TYPE_NAME(o2));
                return nullptr;
            }
            #endif

            *((ColorObject *) o1)->color += (int) PyLong_AsLong(o2);
        }

        RETURN_PYOBJECT(o1);
    }

    static PyObject *PyNumber_InPlaceSubtract(PyObject *o1, PyObject *o2) {
        #if GP_ERROR_CHECKING
        if (!color::isinstance(o1)) {
            PyErr_Format(PyExc_TypeError, "unsupported operand type(s) for -=: '%s' and '%s'", TYPE_NAME(o1), TYPE_NAME(o2));
            return nullptr;
        }
        #endif

        if (color::isinstance(o2)) {
            *((ColorObject *) o1)->color -= *((ColorObject *) o2)->color;
        }
        else {
            #if GP_ERROR_CHECKING
            if (!PyLong_Check(o2)) {
                PyErr_Format(PyExc_TypeError, "unsupported operand type(s) for -=: '%s' and '%s'", TYPE_NAME(o1), TYPE_NAME(o2));
                return nullptr;
            }
            #endif

            *((ColorObject *) o1)->color -= (int) PyLong_AsLong(o2);
        }

        RETURN_PYOBJECT(o1);
    }
}

// Getter & Setters
namespace color {
    static int set_red(ColorObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        int red = (int) PyLong_AsLong(value);

        CHECK_RED(-1)

        self->color->setRed(red);
        return 0;
    }

    static PyObject *get_red(ColorObject *self, PyObject *Py_UNUSED(args)) {
        return PyLong_FromLong(self->color->getRed());
    }

    static int set_green(ColorObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        int green = (int) PyLong_AsLong(value);

        CHECK_GREEN(-1)

        self->color->setGreen(green);
        return 0;
    }

    static PyObject *get_green(ColorObject *self, PyObject *Py_UNUSED(args)) {
        return PyLong_FromLong(self->color->getGreen());
    }

    static int set_blue(ColorObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        int blue = (int) PyLong_AsLong(value);

        CHECK_BLUE(-1)

        self->color->setBlue(blue);
        return 0;
    }

    static PyObject *get_blue(ColorObject *self, PyObject *Py_UNUSED(args)) {
        return PyLong_FromLong(self->color->getBlue());
    }

    static int set_alpha(ColorObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        float alpha = (float) PyFloat_AsDouble(value);

        CHECK_ALPHA(-1)

        self->color->setAlpha(alpha);
        return 0;
    }

    static PyObject *get_alpha(ColorObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getAlpha());
    }
}

// Color Type
namespace color {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {"red",   (getter) get_red,   (setter) set_red,   "red",   nullptr},
            {"green", (getter) get_green, (setter) set_green, "green", nullptr},
            {"blue",  (getter) get_blue,  (setter) set_blue,  "blue",  nullptr},
            {"alpha", (getter) get_alpha, (setter) set_alpha, "alpha", nullptr},

            {nullptr}
    };

    static PyNumberMethods numbermethods = {
            .nb_add = color::PyNumber_Add,
            .nb_subtract = color::PyNumber_Subtract,
            .nb_inplace_add = color::PyNumber_InPlaceAdd,
            .nb_inplace_subtract = color::PyNumber_InPlaceSubtract,
    };
}

namespace color::rgb {
    static int init(ColorRGBObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_COLOR_TRACE("Initializing gp.ColorRGB()");

        if (ColorType.tp_init((PyObject *) self, PyTuple_New(0), Py_None) < 0) {
            return -1;
        }

        if (PyTuple_GET_SIZE(args) == 1) {
            PyObject *obj = PyTuple_GET_ITEM(args, 0);
            if (color::isinstance(obj)) {
                self->color = std::make_shared<gp::ColorRGB>(*(((ColorObject *) obj)->color));
                goto finish_init;
            }
        }
        {
            int red, green, blue;
            float alpha = 1.0f;

            if (!PyArg_ParseTuple(args, "III|f", &red, &green, &blue, &alpha)) {
                PyErr_Clear();
                if (!PyArg_ParseTuple(args, "(III)|f", &red, &green, &blue, &alpha)) {
                    PyErr_Clear();
                    if (!PyArg_ParseTuple(args, "(IIIf)", &red, &green, &blue, &alpha)) {

                        // Sets the appropriate error string
                        PyArg_ParseTuple(args, "III|f", &red, &green, &blue, &alpha);
                        return -1;
                    }
                }
            }

            CHECK_RGBA(-1)

            self->color = std::make_shared<gp::ColorRGB>(red, green, blue, alpha);
        }

        finish_init:

        self->base.color = self->color;
        return 0;
    }

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

namespace color::hex {
    static int init(ColorHexObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_COLOR_TRACE("Initializing gp.ColorHex()");

        if (ColorType.tp_init((PyObject *) self, PyTuple_New(0), Py_None) < 0) {
            return -1;
        }

        PyObject *obj;
        float alpha = 1.0f;

        if (!PyArg_ParseTuple(args, "O|f", &obj, &alpha)) {
            PyErr_Clear();
            if (!PyArg_ParseTuple(args, "(Of)", &obj, &alpha)) {
                return -1;
            }
        }

        if (PyUnicode_Check(obj)) {
            CHECK_ALPHA(-1)

            const char *hexstring = PyUnicode_AsUTF8(obj);

            try {
                self->color = std::make_shared<gp::ColorHex>(hexstring, alpha);
            }
            catch (const std::invalid_argument &iaex) {
                RAISE_VALUE_ERROR(-1, "invalid hexstring format")
            }
        }
        else if (color::isinstance(obj)) {
            self->color = std::make_shared<gp::ColorHex>(*(((ColorObject *) obj)->color));
        }
        else {
            RAISE_VALUE_ERROR(-1, "invalid color format")
        }

        self->base.color = self->color;

        return 0;
    }

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

namespace color::cmyk {
    static int init(ColorCMYKObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_COLOR_TRACE("Initializing gp.ColorCMYK()");

        if (ColorType.tp_init((PyObject *) self, PyTuple_New(0), Py_None) < 0) {
            return -1;
        }

        if (PyTuple_GET_SIZE(args) == 1) {
            PyObject *obj = PyTuple_GET_ITEM(args, 0);
            if (color::isinstance(obj)) {
                self->color = std::make_shared<gp::ColorCMYK>(*(((ColorObject *) obj)->color));
                goto finish_init;
            }
        }
        {
            float cyan, magenta, yellow, key;
            float alpha = 1.0f;
            if (!PyArg_ParseTuple(args, "ffff|f", &cyan, &magenta, &yellow, &key, &alpha)) {
                PyErr_Clear();
                if (!PyArg_ParseTuple(args, "(ffff)|f", &cyan, &magenta, &yellow, &key, &alpha)) {
                    PyErr_Clear();
                    if (!PyArg_ParseTuple(args, "(fffff)", &cyan, &magenta, &yellow, &key, &alpha)) {

                        // Sets the appropriate error string
                        PyArg_ParseTuple(args, "ffff|f", &cyan, &magenta, &yellow, &key, &alpha);
                        return -1;
                    }
                }
            }

            CHECK_CMYKA(-1)

            self->color = std::make_shared<gp::ColorCMYK>(cyan, magenta, yellow, key, alpha);
        }

        finish_init:

        self->base.color = self->color;

        return 0;
    }

    // Getter & Setters
    static int set_cyan(ColorCMYKObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value)
        }
        #endif

        float cyan = (float) PyFloat_AsDouble(value);

        CHECK_CYAN(-1)

        self->color->setCyan(cyan);
        return 0;
    }

    static PyObject *get_cyan(ColorCMYKObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getCyan());
    }

    static int set_magenta(ColorCMYKObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value)
        }
        #endif

        float magenta = (float) PyFloat_AsDouble(value);

        CHECK_MAGENTA(-1)

        self->color->setMagenta(magenta);
        return 0;
    }

    static PyObject *get_magenta(ColorCMYKObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getMagenta());
    }

    static int set_yellow(ColorCMYKObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value)
        }
        #endif

        float yellow = (float) PyFloat_AsDouble(value);

        CHECK_YELLOW(-1)

        self->color->setYellow(yellow);
        return 0;
    }

    static PyObject *get_yellow(ColorCMYKObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getYellow());
    }

    static int set_key(ColorCMYKObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value)
        }
        #endif

        float key = (float) PyFloat_AsDouble(value);

        CHECK_KEY(-1)

        self->color->setKey(key);
        return 0;
    }

    static PyObject *get_key(ColorCMYKObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getKey());
    }

    // Color Type
    static PyGetSetDef getsetters[] = {
            {"cyan",    (getter) get_cyan,    (setter) set_cyan,    "cyan",    nullptr},
            {"magenta", (getter) get_magenta, (setter) set_magenta, "magenta", nullptr},
            {"yellow",  (getter) get_yellow,  (setter) set_yellow,  "yellow",  nullptr},
            {"key",     (getter) get_key,     (setter) set_key,     "key",     nullptr},
            {nullptr}
    };
}

namespace color::hsv {
    static int init(ColorHSVObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_COLOR_TRACE("Initializing gp.ColorHSV()");

        if (ColorType.tp_init((PyObject *) self, PyTuple_New(0), Py_None) < 0) {
            return -1;
        }

        if (PyTuple_GET_SIZE(args) == 1) {
            PyObject *obj = PyTuple_GET_ITEM(args, 0);
            if (color::isinstance(obj)) {
                self->color = std::make_shared<gp::ColorHSV>(*(((ColorObject *) obj)->color));
                goto finish_init;
            }
        }
        {
            int hue;
            float saturation, value;
            float alpha = 1.0f;
            if (!PyArg_ParseTuple(args, "iff|f", &hue, &saturation, &value, &alpha)) {
                PyErr_Clear();
                if (!PyArg_ParseTuple(args, "(iff)|f", &hue, &saturation, &value, &alpha)) {
                    PyErr_Clear();
                    if (!PyArg_ParseTuple(args, "(ifff)", &hue, &saturation, &value, &alpha)) {

                        // Sets the appropriate error string
                        PyArg_ParseTuple(args, "iff|f", &hue, &saturation, &value, &alpha);
                        return -1;
                    }
                }
            }

            CHECK_HSVA(-1)

            self->color = std::make_shared<gp::ColorHSV>(hue, saturation, value, alpha);
        }

        finish_init:

        self->base.color = self->color;

        return 0;
    }

    // Getter & Setters
    static int set_hue(ColorHSVObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        int hue = (int) PyLong_AsLong(value);

        CHECK_HUE(-1)

        self->color->setHue(hue);
        return 0;
    }

    static PyObject *get_hue(ColorHSVObject *self, PyObject *Py_UNUSED(args)) {
        return PyLong_FromLong(self->color->getHue());
    }

    static int set_saturation(ColorHSVObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value)
        }
        #endif

        float saturation = (float) PyFloat_AsDouble(value);

        CHECK_SATURATION(-1)

        self->color->setSaturation(saturation);
        return 0;
    }

    static PyObject *get_saturation(ColorHSVObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getSaturation());
    }

    static int set_value(ColorHSVObject *self, PyObject *value_, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value_)) {
            RAISE_TYPE_ERROR(-1, "float", value_)
        }
        #endif

        float value = (float) PyFloat_AsDouble(value_);

        CHECK_VALUE(-1)

        self->color->setValue(value);
        return 0;
    }

    static PyObject *get_value(ColorHSVObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getValue());
    }

    // Color Type
    static PyGetSetDef getsetters[] = {
            {"hue",        (getter) get_hue,        (setter) set_hue,        "hue",        nullptr},
            {"saturation", (getter) get_saturation, (setter) set_saturation, "saturation", nullptr},
            {"value",      (getter) get_value,      (setter) set_value,      "value",      nullptr},
            {nullptr}
    };
}

namespace color::hsl {
    static int init(ColorHSLObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_COLOR_TRACE("Initializing gp.ColorHSL()");

        if (ColorType.tp_init((PyObject *) self, PyTuple_New(0), Py_None) < 0) {
            return -1;
        }

        if (PyTuple_GET_SIZE(args) == 1) {
            PyObject *obj = PyTuple_GET_ITEM(args, 0);
            if (color::isinstance(obj)) {
                self->color = std::make_shared<gp::ColorHSL>(*(((ColorObject *) obj)->color));
                goto finish_init;
            }
        }
        {
            int hue;
            float saturation, luminance;
            float alpha = 1.0f;
            if (!PyArg_ParseTuple(args, "iff|f", &hue, &saturation, &luminance, &alpha)) {
                PyErr_Clear();
                if (!PyArg_ParseTuple(args, "(iff)|f", &hue, &saturation, &luminance, &alpha)) {
                    PyErr_Clear();
                    if (!PyArg_ParseTuple(args, "(ifff)", &hue, &saturation, &luminance, &alpha)) {

                        // Sets the appropriate error string
                        PyArg_ParseTuple(args, "iff|f", &hue, &saturation, &luminance, &alpha);
                        return -1;
                    }
                }
            }

            CHECK_HSLA(-1)

            self->color = std::make_shared<gp::ColorHSL>(hue, saturation, luminance, alpha);
        }

        finish_init:

        self->base.color = self->color;

        return 0;
    }

    // Getter & Setters
    static int set_hue(ColorHSLObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        int hue = (int) PyLong_AsLong(value);

        CHECK_HUE(-1)

        self->color->setHue(hue);
        return 0;
    }

    static PyObject *get_hue(ColorHSLObject *self, PyObject *Py_UNUSED(args)) {
        return PyLong_FromLong(self->color->getHue());
    }

    static int set_saturation(ColorHSLObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value)
        }
        #endif

        float saturation = (float) PyFloat_AsDouble(value);

        CHECK_SATURATION(-1)

        self->color->setSaturation(saturation);
        return 0;
    }

    static PyObject *get_saturation(ColorHSLObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getSaturation());
    }

    static int set_luminance(ColorHSLObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value)
        }
        #endif

        float luminance = (float) PyFloat_AsDouble(value);

        CHECK_LUMINANCE(-1)

        self->color->setLuminance(luminance);
        return 0;
    }

    // Color Type
    static PyObject *get_luminance(ColorHSLObject *self, PyObject *Py_UNUSED(args)) {
        return PyFloat_FromDouble(self->color->getLuminance());
    }

    static PyGetSetDef getsetters[] = {
            {"hue",        (getter) get_hue,        (setter) set_hue,        "hue",        nullptr},
            {"saturation", (getter) get_saturation, (setter) set_saturation, "saturation", nullptr},
            {"luminance",  (getter) get_luminance,  (setter) set_luminance,  "luminance",  nullptr},
            {nullptr}
    };
}

PyTypeObject ColorType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_basicsize = sizeof(ColorObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        .tp_new = PyType_GenericNew,
        .tp_name = "goopylib.Color",
        .tp_init = (initproc) color::init,

        .tp_methods = color::methods,
        .tp_getset = color::getsetters,
        .tp_as_number = &color::numbermethods,

        .tp_traverse = (traverseproc) color::traverse,
        .tp_clear = (inquiry) color::clear,
        .tp_dealloc = (destructor) color::dealloc,

        .tp_repr = (reprfunc) color::repr,
};

PyTypeObject ColorRGBType = {
        PyColorObject_HEAD_INIT
        .tp_basicsize = sizeof(ColorRGBObject),
        .tp_name = "goopylib.ColorRGB",
        .tp_init = (initproc) color::rgb::init,

        .tp_getset = color::rgb::getsetters,
};

PyTypeObject ColorHexType = {
        PyColorObject_HEAD_INIT
        .tp_basicsize = sizeof(ColorHexObject),
        .tp_name = "goopylib.ColorHex",
        .tp_init = (initproc) color::hex::init,

        .tp_getset = color::hex::getsetters,
};

PyTypeObject ColorCMYKType = {
        PyColorObject_HEAD_INIT
        .tp_basicsize = sizeof(ColorCMYKObject),
        .tp_name = "goopylib.ColorCMYK",
        .tp_init = (initproc) color::cmyk::init,

        .tp_getset = color::cmyk::getsetters,
};

PyTypeObject ColorHSVType = {
        PyColorObject_HEAD_INIT
        .tp_basicsize = sizeof(ColorHSVObject),
        .tp_name = "goopylib.ColorHSV",
        .tp_init = (initproc) color::hsv::init,

        .tp_getset = color::hsv::getsetters,
};

PyTypeObject ColorHSLType = {
        PyColorObject_HEAD_INIT
        .tp_basicsize = sizeof(ColorHSLObject),
        .tp_name = "goopylib.ColorHSL",
        .tp_init = (initproc) color::hsl::init,

        .tp_getset = color::hsl::getsetters,
};
