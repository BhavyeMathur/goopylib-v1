#define COLOR_MODULE

#include "color.h"
#include "color_object.h"
#include "color_module.h"
#include "color_capsule.h"

#include "config.h"

#if (GP_LOG_COLOR != true) and (GP_LOG_COLOR <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_COLOR
#endif

#if !GP_VALUE_CHECK_COLOR
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"
#include "macros.h"

struct ColorRGBObject {
    ColorObject base;
    Ref<gp::ColorRGB> color;
};

struct ColorHexObject {
    ColorObject base;
    Ref<gp::ColorHex> color;
};

struct ColorCMYKObject {
    ColorObject base;
    Ref<gp::ColorCMYK> color;
};

struct ColorHSVObject {
    ColorObject base;
    Ref<gp::ColorHSV> color;
};

struct ColorHSLObject {
    ColorObject base;
    Ref<gp::ColorHSL> color;
};

namespace color {
    static bool isinstance(PyObject *object) {
        GP_PY_TRACE("gp.color.isinstance()");
        return PyObject_IsInstance(object, (PyObject *) &ColorType);
    }

    // Create color instances

    static PyObject *create(int red, int green, int blue, float alpha) {
        GP_PY_DEBUG("gp.color.create()");

        red = red > 255 ? 255 : (red < 0 ? 0 : red);
        green = green > 255 ? 255 : (green < 0 ? 0 : green);
        blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);

        alpha = alpha > 1 ? 1 : (alpha < 0 ? 0 : alpha);

        return PyObject_Call((PyObject *) &ColorType,
                             Py_BuildValue("iiif", red, green, blue, alpha), Py_None);
    }
}

// Color Object
namespace color {
    static int init(ColorObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.color.Color()");

        const char *hexstring;
        float alpha = 1.0f;

        if (PyArg_ParseTuple(args, "s|f", &hexstring, &alpha)) {
            CHECK_ALPHA(-1)

            try {
                self->color = std::make_shared<gp::Color>(hexstring, alpha);
            }
            catch (const std::invalid_argument &e) {
                RAISE_VALUE_ERROR(-1, "invalid hexstring format");
            }

            return 0;
        }
        PyErr_Clear();

        PyObject *obj;
        if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
            self->color = std::make_shared<gp::Color>(*(((ColorObject *) obj)->color));
            return 0;
        }
        PyErr_Clear();

        int red, green, blue;
        if (!PyArg_ParseTuple(args, "iii|f", &red, &green, &blue, &alpha)) {
            RAISE_VALUE_ERROR(-1, "invalid color format");
        }

        CHECK_RED(-1)
        CHECK_RGBA(-1)

        self->color = std::make_shared<gp::Color>(red, green, blue, alpha);
        return 0;
    }

    static PyObject *repr(ColorObject *self) {
        GP_PY_TRACE("gp.color.Color.__repr__()");
        return PyUnicode_FromString(self->color->toString().c_str());
    }

    static int traverse(ColorObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(ColorObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.color.Color.clear()");
        return 0;
    }

    static void dealloc(ColorObject *self) {
        GP_PY_DEBUG("gp.color.Color.__dealloc__()");

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// PyNumber API
namespace color {
    static PyObject *PyNumber_Add(PyObject *o1, PyObject *o2) {
        GP_PY_DEBUG("gp.color.Color.__add__()");

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
                RAISE_TYPE_ERROR(nullptr, "integer or color", o2);
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
                RAISE_TYPE_ERROR(nullptr, "integer or color", o1);
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
        GP_PY_DEBUG("gp.color.Color.__sub__()");

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
                RAISE_TYPE_ERROR(nullptr, "integer or color", o2);
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
                RAISE_TYPE_ERROR(nullptr, "integer or color", o1);
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
        GP_PY_DEBUG("gp.color.Color.__iadd__()");

        #if GP_ERROR_CHECKING
        if (!color::isinstance(o1)) {
            PyErr_Format(PyExc_TypeError,
                         "unsupported operand type(s) for +=: '%s' and '%s'", PYOBJECT_NAME(o1), PYOBJECT_NAME(o2));
            return nullptr;
        }
        #endif

        if (color::isinstance(o2)) {
            *((ColorObject *) o1)->color += *((ColorObject *) o1)->color;
        }
        else {
            #if GP_ERROR_CHECKING
            if (!PyLong_Check(o2)) {
                PyErr_Format(PyExc_TypeError,
                             "unsupported operand type(s) for +=: '%s' and '%s'", PYOBJECT_NAME(o1), PYOBJECT_NAME(o2));
                return nullptr;
            }
            #endif

            *((ColorObject *) o1)->color += (int) PyLong_AsLong(o2);
        }

        RETURN_PYOBJECT(o1);
    }

    static PyObject *PyNumber_InPlaceSubtract(PyObject *o1, PyObject *o2) {
        GP_PY_DEBUG("gp.color.Color.__isub__()");

        #if GP_ERROR_CHECKING
        if (!color::isinstance(o1)) {
            PyErr_Format(PyExc_TypeError,
                         "unsupported operand type(s) for -=: '%s' and '%s'", PYOBJECT_NAME(o1), PYOBJECT_NAME(o2));
            return nullptr;
        }
        #endif

        if (color::isinstance(o2)) {
            *((ColorObject *) o1)->color -= *((ColorObject *) o2)->color;
        }
        else {
            #if GP_ERROR_CHECKING
            if (!PyLong_Check(o2)) {
                PyErr_Format(PyExc_TypeError,
                             "unsupported operand type(s) for -=: '%s' and '%s'", PYOBJECT_NAME(o1), PYOBJECT_NAME(o2));
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
        GP_PY_DEBUG("gp.color.Color.set_red()");

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int red = (int) PyLong_AsLong(value);

        CHECK_RED(-1)

        self->color->setRed(red);
        return 0;
    }

    static PyObject *get_red(ColorObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.Color.get_red()");
        return PyLong_FromLong(self->color->getRed());
    }

    static int set_green(ColorObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.Color.set_green()");

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int green = (int) PyLong_AsLong(value);

        CHECK_GREEN(-1)

        self->color->setGreen(green);
        return 0;
    }

    static PyObject *get_green(ColorObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.Color.get_green()");
        return PyLong_FromLong(self->color->getGreen());
    }

    static int set_blue(ColorObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.Color.set_blue()");

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int blue = (int) PyLong_AsLong(value);

        CHECK_BLUE(-1)

        self->color->setBlue(blue);
        return 0;
    }

    static PyObject *get_blue(ColorObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.Color.get_blue()");
        return PyLong_FromLong(self->color->getBlue());
    }

    static int set_alpha(ColorObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.Color.set_alpha()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        float alpha = (float) PyFloat_AsDouble(value);

        CHECK_ALPHA(-1)

        self->color->setAlpha(alpha);
        return 0;
    }

    static PyObject *get_alpha(ColorObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.Color.get_alpha()");
        return PyFloat_FromDouble(self->color->getAlpha());
    }
}

// Color Type
namespace color {
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
        GP_PY_INFO("gp.color.ColorRGB()");

        int red, green, blue;
        float alpha = 1.0f;
        if (PyArg_ParseTuple(args, "iii|f", &red, &green, &blue, &alpha)) {
            CHECK_RGBA(-1)

            self->color = std::make_shared<gp::ColorRGB>(red, green, blue, alpha);
            self->base.color = self->color;
            return 0;
        }
        PyErr_Clear();

        PyObject *obj;
        if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
            self->color = std::make_shared<gp::ColorRGB>(((ColorObject *) obj)->color.get());
            self->base.color = self->color;
            return 0;
        }

        RAISE_VALUE_ERROR(-1, "invalid color format");
    }
}

namespace color::hex {
    static int init(ColorHexObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.color.ColorHex()");

        const char *hexstring;
        float alpha = 1.0f;

        if (PyArg_ParseTuple(args, "s|f", &hexstring, &alpha)) {
            CHECK_ALPHA(-1)

            try {
                self->color = std::make_shared<gp::ColorHex>(hexstring, alpha);
            }
            catch (const std::invalid_argument &e) {
                RAISE_VALUE_ERROR(-1, "invalid hexstring format");
            }

            self->base.color = self->color;
            return 0;
        }
        PyErr_Clear();

        PyObject *obj;
        if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
            self->color = std::make_shared<gp::ColorHex>(((ColorObject *) obj)->color.get());
            self->base.color = self->color;
            return 0;
        }

        RAISE_VALUE_ERROR(-1, "invalid hexadecimal color format");
    }
}

namespace color::cmyk {
    static int init(ColorCMYKObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.color.ColorCMYK()");

        float cyan, magenta, yellow, key;
        float alpha = 1.0f;
        if (PyArg_ParseTuple(args, "ffff|f", &cyan, &magenta, &yellow, &key, &alpha)) {
            CHECK_CMYKA(-1)

            self->color = std::make_shared<gp::ColorCMYK>(cyan, magenta, yellow, key, alpha);
            self->base.color = self->color;
            return 0;
        }
        PyErr_Clear();

        PyObject *obj;
        if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
            self->color = std::make_shared<gp::ColorCMYK>(((ColorObject *) obj)->color.get());
            self->base.color = self->color;
            return 0;
        }

        RAISE_VALUE_ERROR(-1, "invalid CMYK format");
    }

    // Getter & Setters
    static int set_cyan(ColorCMYKObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_INFO("gp.color.ColorCMYK.set_cyan()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value);
        }
        #endif

        float cyan = (float) PyFloat_AsDouble(value);

        CHECK_CYAN(-1)

        self->color->setCyan(cyan);
        return 0;
    }

    static PyObject *get_cyan(ColorCMYKObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorCMYK.get_cyan()");
        return PyFloat_FromDouble(self->color->getCyan());
    }

    static int set_magenta(ColorCMYKObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_INFO("gp.color.ColorCMYK.set_magenta()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value);
        }
        #endif

        float magenta = (float) PyFloat_AsDouble(value);

        CHECK_MAGENTA(-1)

        self->color->setMagenta(magenta);
        return 0;
    }

    static PyObject *get_magenta(ColorCMYKObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorCMYK.get_magenta()");
        return PyFloat_FromDouble(self->color->getMagenta());
    }

    static int set_yellow(ColorCMYKObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_INFO("gp.color.ColorCMYK.set_yellow()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value);
        }
        #endif

        float yellow = (float) PyFloat_AsDouble(value);

        CHECK_YELLOW(-1)

        self->color->setYellow(yellow);
        return 0;
    }

    static PyObject *get_yellow(ColorCMYKObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorCMYK.get_yellow()");
        return PyFloat_FromDouble(self->color->getYellow());
    }

    static int set_key(ColorCMYKObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_INFO("gp.color.ColorCMYK.set_key()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value);
        }
        #endif

        float key = (float) PyFloat_AsDouble(value);

        CHECK_KEY(-1)

        self->color->setKey(key);
        return 0;
    }

    static PyObject *get_key(ColorCMYKObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorCMYK.get_key()");
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
        GP_PY_INFO("gp.color.ColorHSV()");

        int hue;
        float saturation, value;
        float alpha = 1.0f;
        if (PyArg_ParseTuple(args, "iff|f", &hue, &saturation, &value, &alpha)) {
            CHECK_HSVA(-1)

            self->color = std::make_shared<gp::ColorHSV>(hue, saturation, value, alpha);
            self->base.color = self->color;
            return 0;
        }
        PyErr_Clear();

        PyObject *obj;
        if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
            self->color = std::make_shared<gp::ColorHSV>(((ColorObject *) obj)->color.get());
            self->base.color = self->color;
            return 0;
        }

        RAISE_VALUE_ERROR(-1, "invalid HSV format");
    }

    // Getter & Setters
    static int set_hue(ColorHSVObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.ColorHSV.set_hue()");

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int hue = (int) PyLong_AsLong(value);

        CHECK_HUE(-1)

        self->color->setHue(hue);
        return 0;
    }

    static PyObject *get_hue(ColorHSVObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorHSV.get_hue()");
        return PyLong_FromLong(self->color->getHue());
    }

    static int set_saturation(ColorHSVObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.ColorHSV.set_saturation()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value);
        }
        #endif

        float saturation = (float) PyFloat_AsDouble(value);

        CHECK_SATURATION(-1)

        self->color->setSaturation(saturation);
        return 0;
    }

    static PyObject *get_saturation(ColorHSVObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorHSV.get_saturation()");
        return PyFloat_FromDouble(self->color->getSaturation());
    }

    static int set_value(ColorHSVObject *self, PyObject *value_, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.ColorHSV.set_value()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value_)) {
            RAISE_TYPE_ERROR(-1, "float", value_);
        }
        #endif

        float value = (float) PyFloat_AsDouble(value_);

        CHECK_VALUE(-1)

        self->color->setValue(value);
        return 0;
    }

    static PyObject *get_value(ColorHSVObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorHSV.get_value()");
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
        GP_PY_TRACE("gp.color.ColorHSL()");

        int hue;
        float saturation, luminance, alpha = 1.0f;

        if (PyArg_ParseTuple(args, "iff|f", &hue, &saturation, &luminance, &alpha)) {
            CHECK_HSLA(-1)

            self->color = std::make_shared<gp::ColorHSL>(hue, saturation, luminance, alpha);
            self->base.color = self->color;
            return 0;
        }
        PyErr_Clear();

        PyObject *obj;
        if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
            self->color = std::make_shared<gp::ColorHSL>(((ColorObject *) obj)->color.get());
            self->base.color = self->color;
            return 0;
        }

        RAISE_VALUE_ERROR(-1, "invalid HSV format");
    }

    // Getter & Setters
    static int set_hue(ColorHSLObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.ColorHSL.set_hue()");

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int hue = (int) PyLong_AsLong(value);

        CHECK_HUE(-1)

        self->color->setHue(hue);
        return 0;
    }

    static PyObject *get_hue(ColorHSLObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorHSL.get_hue()");
        return PyLong_FromLong(self->color->getHue());
    }

    static int set_saturation(ColorHSLObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.ColorHSL.set_saturation()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value);
        }
        #endif

        float saturation = (float) PyFloat_AsDouble(value);

        CHECK_SATURATION(-1)

        self->color->setSaturation(saturation);
        return 0;
    }

    static PyObject *get_saturation(ColorHSLObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorHSL.get_saturation()");
        return PyFloat_FromDouble(self->color->getSaturation());
    }

    static int set_luminance(ColorHSLObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.color.ColorHSL.set_luminance()");

        #if GP_ERROR_CHECKING
        if (!PyFloat_Check(value)) {
            RAISE_TYPE_ERROR(-1, "float", value);
        }
        #endif

        float luminance = (float) PyFloat_AsDouble(value);

        CHECK_LUMINANCE(-1)

        self->color->setLuminance(luminance);
        return 0;
    }

    // Color Type
    static PyObject *get_luminance(ColorHSLObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_TRACE("gp.color.ColorHSL.get_luminance()");
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
};

PyTypeObject ColorHexType = {
        PyColorObject_HEAD_INIT
        .tp_basicsize = sizeof(ColorHexObject),
        .tp_name = "goopylib.ColorHex",
        .tp_init = (initproc) color::hex::init,
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

static struct PyModuleDef colormodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "color",
        .m_size = -1,
        .m_methods = nullptr,
};


PyMODINIT_FUNC PyInit_color() {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_color()" << std::endl;
    #endif

    PyObject *m;
    m = PyModule_Create(&colormodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_PYOBJECT_CLASS(ColorType, "Color");

    ColorRGBType.tp_base = &ColorType;
    ColorHexType.tp_base = &ColorType;
    ColorCMYKType.tp_base = &ColorType;
    ColorHSVType.tp_base = &ColorType;
    ColorHSLType.tp_base = &ColorType;

    EXPOSE_PYOBJECT_CLASS(ColorRGBType, "ColorRGB");
    EXPOSE_PYOBJECT_CLASS(ColorHexType, "ColorHex");
    EXPOSE_PYOBJECT_CLASS(ColorCMYKType, "ColorCMYK");
    EXPOSE_PYOBJECT_CLASS(ColorHSVType, "ColorHSV");
    EXPOSE_PYOBJECT_CLASS(ColorHSLType, "ColorHSL");

    static void *PyColor_API[PyColor_API_pointers];
    PyObject *c_api_object;

    PyColor_API[Color_pytype_NUM] = (void *) Color_pytype;
    c_api_object = PyCapsule_New((void *) PyColor_API, "goopylib.ext.color._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
