#include "color.h"

struct ColorObject {
    PyObject_HEAD
    std::shared_ptr<gp::Color> color;
};

struct ColorRGBObject {
    ColorObject base;
    std::shared_ptr<gp::ColorRGB> color;
};

struct ColorHexObject {
    ColorObject base;
    std::shared_ptr<gp::ColorHex> color;
};

struct ColorCMYKObject {
    ColorObject base;
    std::shared_ptr<gp::ColorCMYK> color;
};

struct ColorHSVObject {
    ColorObject base;
    std::shared_ptr<gp::ColorHSV> color;
};

struct ColorHSLObject {
    ColorObject base;
    std::shared_ptr<gp::ColorHSL> color;
};


// Color Object
namespace color {
    static int init(ColorObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_COLOR_TRACE("Initializing gp.Color()");

        switch (PyTuple_GET_SIZE(args)) {
            case 0:
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

    // Getter & Setters
    static int set_red(ColorObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        unsigned int red = PyLong_AsLong(value);

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

        unsigned int green = PyLong_AsLong(value);

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

        unsigned int blue = PyLong_AsLong(value);

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

        .tp_traverse = (traverseproc) color::traverse,
        .tp_clear = (inquiry) color::clear,
        .tp_dealloc = (destructor) color::dealloc,

        .tp_repr = (reprfunc) color::repr,
};

// Color Subclasses
namespace color {
    namespace rgb {
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

    namespace hex {
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

    namespace cmyk {
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

    namespace hsv {
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

            unsigned int hue = PyLong_AsLong(value);

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

    namespace hsl {
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

            unsigned int hue = PyLong_AsLong(value);

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
}

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

// Color Conversions
namespace color {

    // RGB to other format

    static PyObject *rgb_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        return PyUnicode_FromString(gp::rgb::toHex(red, green, blue));
    }

    static PyObject *rgb_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::CMYK color_cmyk = gp::rgb::toCMYK(red, green, blue);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    static PyObject *rgb_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::HSV color_hsv = gp::rgb::toHSV(red, green, blue);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    static PyObject *rgb_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::HSL color_hsl = gp::rgb::toHSL(red, green, blue);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // Hex to other format

    static PyObject *hex_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::RGB color_rgb = gp::hex::toRGB(hexstring);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    static PyObject *hex_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::CMYK color_cmyk = gp::hex::toCMYK(hexstring);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    static PyObject *hex_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::HSL color_hsl = gp::hex::toHSL(hexstring);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    static PyObject *hex_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::HSV color_hsv = gp::hex::toHSV(hexstring);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    // CMYK to other format

    static PyObject *cmyk_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::RGB color_rgb = gp::cmyk::toRGB(cyan, magenta, yellow, key);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    static PyObject *cmyk_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        return PyUnicode_FromString(gp::cmyk::toHex(cyan, magenta, yellow, key));
    }

    static PyObject *cmyk_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::HSV color_hsv = gp::cmyk::toHSV(cyan, magenta, yellow, key);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    static PyObject *cmyk_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::HSL color_hsl = gp::cmyk::toHSL(cyan, magenta, yellow, key);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // HSV to other format

    static PyObject *hsv_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::RGB color_rgb = gp::hsv::toRGB(hue, saturation, value);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    static PyObject *hsv_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        return PyUnicode_FromString(gp::hsv::toHex(hue, saturation, value));
    }

    static PyObject *hsv_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::CMYK color_cmyk = gp::hsv::toCMYK(hue, saturation, value);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    static PyObject *hsv_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::HSL color_hsl = gp::hsv::toHSL(hue, saturation, value);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // HSL to other format

    static PyObject *hsl_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::RGB color_rgb = gp::hsl::toRGB(hue, saturation, luminance);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    static PyObject *hsl_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        return PyUnicode_FromString(gp::hsl::toHex(hue, saturation, luminance));
    }

    static PyObject *hsl_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::CMYK color_cmyk = gp::hsl::toCMYK(hue, saturation, luminance);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    static PyObject *hsl_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::HSV color_hsv = gp::hsl::toHSV(hue, saturation, luminance);

        return Py_BuildValue("ifff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }
}

// Utility Color Functions
namespace color {
    static PyObject *random_rgb(PyObject *Py_UNUSED(self)) {
        gp::ColorRGB rgb = gp::randomRGB();
        return PyObject_Call((PyObject *) &ColorRGBType,
                             Py_BuildValue("iii", rgb.getRed(), rgb.getGreen(), rgb.getBlue()), Py_None);
    }

    static PyObject *random_hex(PyObject *Py_UNUSED(self)) {
        gp::ColorHex hex = gp::randomHex();
        return PyObject_CallOneArg((PyObject *) &ColorHexType,
                                   PyUnicode_FromString(hex.toString().c_str()));
    }

    static PyObject *random_cmyk(PyObject *Py_UNUSED(self)) {
        gp::ColorCMYK cmyk = gp::randomCMYK();
        return PyObject_Call((PyObject *) &ColorCMYKType,
                             Py_BuildValue("ffff", cmyk.getCyan(), cmyk.getMagenta(), cmyk.getYellow(), cmyk.getKey()),
                             Py_None);
    }

    static PyObject *random_hsv(PyObject *Py_UNUSED(self)) {
        gp::ColorHSV hsv = gp::randomHSV();
        return PyObject_Call((PyObject *) &ColorHSVType,
                             Py_BuildValue("iff", hsv.getHue(), hsv.getSaturation(), hsv.getValue()),
                             Py_None);
    }

    static PyObject *random_hsl(PyObject *Py_UNUSED(self)) {
        gp::ColorHSL hsl = gp::randomHSL();
        return PyObject_Call((PyObject *) &ColorHSLType,
                             Py_BuildValue("iff", hsl.getHue(), hsl.getSaturation(), hsl.getLuminance()),
                             Py_None);
    }
}

static PyMethodDef ColorMethods[] = {

        // RGB to other format functions

        {"rgb_to_hex", (PyCFunction) color::rgb_to_hex, METH_VARARGS,
         "rgb_to_hex(int r, int g, int b) -> str '#rrggbb'\nConverts RGB values to a hex string"},

        {"rgb_to_cmyk", (PyCFunction) color::rgb_to_cmyk, METH_VARARGS,
         "rgb_to_cmyk(int r, int g, int b) -> tuple (float c, float m, float y, float k)\nConverts RGB values to CMYK"},

        {"rgb_to_hsl", (PyCFunction) color::rgb_to_hsl, METH_VARARGS,
         "rgb_to_hsl(int r, int g, int b) -> tuple (int h, float s, float l)\nConverts RGB values to HSL"},

        {"rgb_to_hsv", (PyCFunction) color::rgb_to_hsv, METH_VARARGS,
         "rgb_to_hsv(int r, int g, int b) -> tuple (int h, float s, float v)\nConverts RGB values to HSV"},

        // Hex to other format functions

        {"hex_to_rgb", (PyCFunction) color::hex_to_rgb, METH_VARARGS,
         "hex_to_rgb(str hexstring) -> tuple (int r, int g, int b)\nConverts Hex colour values to RGB"},

        {"hex_to_cmyk", (PyCFunction) color::hex_to_cmyk, METH_VARARGS,
         "hex_to_cmyk(str hexstring) -> tuple (float c, float m, float y, float k)\nConverts Hex colour values to CMYK "
         "represented as a tuple"},


        {"hex_to_hsl", (PyCFunction) color::hex_to_hsl, METH_VARARGS,
         "hex_to_hsl(str hexstring) -> tuple (int h, float s, float l)\nConverts Hex colour values to HSL"},

        {"hex_to_hsv", (PyCFunction) color::hex_to_hsv, METH_VARARGS,
         "hex_to_hsv(str hexstring) -> tuple (int h, float s, float v)\nConverts Hex colour values to HSV"},

        // CMYK to other format functions

        {"cmyk_to_rgb", (PyCFunction) color::cmyk_to_rgb, METH_VARARGS,
         "cmyk_to_rgb(float c, float m, float y, float k) -> tuple (int r, int g, int b)\nConverts CMYK values to RGB"},

        {"cmyk_to_hex", (PyCFunction) color::cmyk_to_hex, METH_VARARGS,
         "cmyk_to_hex(float c, float m, float y, float k) -> str '#rrggbb'\nConverts CMYK values to a hex string"},

        {"cmyk_to_hsl", (PyCFunction) color::cmyk_to_hsl, METH_VARARGS,
         "cmyk_to_hsl(float c, float m, float y, float k) -> tuple (int h, float s, float l)\nConverts CMYK values to HSL"},

        {"cmyk_to_hsv", (PyCFunction) color::cmyk_to_hsv, METH_VARARGS,
         "cmyk_to_hsv(float c, float m, float y, float k) -> tuple (int h, float s, float v)\nConverts CMYK values to HSV"},

        // HSV to other format functions

        {"hsv_to_rgb", (PyCFunction) color::hsv_to_rgb, METH_VARARGS,
         "hsv_to_rgb(int h, float s, float v) -> tuple (int r, int g, int b)\nConverts HSV values to RGB"},

        {"hsv_to_hex", (PyCFunction) color::hsv_to_hex, METH_VARARGS,
         "hsv_to_hex(int h, float s, float v) -> str '#rrggbb'\nConverts HSV values to a hex string"},

        {"hsv_to_cmyk", (PyCFunction) color::hsv_to_cmyk, METH_VARARGS,
         "hsv_to_cmyk(int h, float s, float v) -> tuple (float c, float m, float y, float k)\nConverts HSV values to CMYK"},

        {"hsv_to_hsl", (PyCFunction) color::hsv_to_hsl, METH_VARARGS,
         "hsv_to_hsl(int h, float s, float v) -> tuple (int h, float s, float l)\nConverts HSV values to HSL"},

        // HSL to other format functions

        {"hsl_to_rgb", (PyCFunction) color::hsl_to_rgb, METH_VARARGS,
         "hsl_to_rgb(int h, float s, float l) -> tuple (int r, int g, int b)\nConverts HSL values to RGB"},

        {"hsl_to_hex", (PyCFunction) color::hsl_to_hex, METH_VARARGS,
         "hsl_to_hex(int h, float s, float l) -> str '#rrggbb'\nConverts HSL values to a hex string"},

        {"hsl_to_cmyk", (PyCFunction) color::hsl_to_cmyk, METH_VARARGS,
         "hsl_to_cmyk(int h, float s, float l) -> tuple (float c, float m, float y, float k)\nConverts HSL values to CMYK"},

        {"hsl_to_hsv", (PyCFunction) color::hsl_to_hsv, METH_VARARGS,
         "hsl_to_hsv(int h, float s, float l) -> tuple (int h, float s, float v)\nConverts HSL values to HSV"},

        // Utility Colour Functions

        {"random_rgb", (PyCFunction) color::random_rgb, METH_NOARGS, "Returns a random RGB color"},
        {"random_hex", (PyCFunction) color::random_hex, METH_NOARGS, "Returns a random Hex color"},
        {"random_cmyk", (PyCFunction) color::random_cmyk, METH_NOARGS, "Returns a random CMYK color"},
        {"random_hsv", (PyCFunction) color::random_hsv, METH_NOARGS, "Returns a random HSV color"},
        {"random_hsl", (PyCFunction) color::random_hsl, METH_NOARGS, "Returns a random HSL color"},

        {nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef colormodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "color",
        .m_size = -1,
        .m_methods = ColorMethods,
};

namespace color {
    bool isinstance(PyObject *object) {
        return PyObject_IsInstance(object, (PyObject *) &ColorType);
    }
}

PyMODINIT_FUNC PyInit_color(void) {
    gp::CoreLogger = spdlog::get("GOOPYLIB");
    gp::PythonLogger = spdlog::get("PYTHON");
    gp::ClientLogger = spdlog::get("CLIENT");

    GP_PY_COLOR_TRACE("Initializing color module");

    PyObject *m;
    m = PyModule_Create(&colormodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_CLASS(ColorType, "Color")

    ColorRGBType.tp_base = &ColorType;
    ColorHexType.tp_base = &ColorType;
    ColorCMYKType.tp_base = &ColorType;
    ColorHSVType.tp_base = &ColorType;
    ColorHSLType.tp_base = &ColorType;

    EXPOSE_CLASS(ColorRGBType, "ColorRGB")
    EXPOSE_CLASS(ColorHexType, "ColorHex")
    EXPOSE_CLASS(ColorCMYKType, "ColorCMYK")
    EXPOSE_CLASS(ColorHSVType, "ColorHSV")
    EXPOSE_CLASS(ColorHSLType, "ColorHSL")

    return m;
}
