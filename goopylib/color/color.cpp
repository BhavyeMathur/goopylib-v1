#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#define COLOR_MODULE

#include "color.h"
#include "color_object.h"
#include "color_module.h"
#include "color_capsule.h"

#include "macros.h"

#include <goopylib/color/ColorRGB.h>
#include <goopylib/color/ColorHex.h>
#include <goopylib/color/ColorCMYK.h>
#include <goopylib/color/ColorHSV.h>
#include <goopylib/color/ColorHSL.h>

struct ColorRGBObject {
    ColorObject base;
    shared_ptr<gp::ColorRGB> color;
};

struct ColorHexObject {
    ColorObject base;
    shared_ptr<gp::ColorHex> color;
};

struct ColorCMYKObject {
    ColorObject base;
    shared_ptr<gp::ColorCMYK> color;
};

struct ColorHSVObject {
    ColorObject base;
    shared_ptr<gp::ColorHSV> color;
};

struct ColorHSLObject {
    ColorObject base;
    shared_ptr<gp::ColorHSL> color;
};

namespace color {
    static bool isinstance(PyObject * object) {
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
                             Py_BuildValue("iiif", red, green, blue, alpha), nullptr);
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
                self->color = make_shared<gp::Color>(hexstring, alpha);
            }
            catch (const std::invalid_argument &) {
                RAISE_VALUE_ERROR(-1, "invalid hexstring format");
            }

            return 0;
        }
        PyErr_Clear();

        PyObject * obj;
        if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
            self->color = make_shared<gp::Color>(*(((ColorObject *) obj)->color));
            return 0;
        }
        PyErr_Clear();

        int red, green, blue;
        if (PyArg_ParseTuple(args, "iii|f", &red, &green, &blue, &alpha) or
            PyArg_ParseTuple(args, "(iiif)", &red, &green, &blue, &alpha) or
            PyArg_ParseTuple(args, "(iii)|f", &red, &green, &blue, &alpha)) {
            CHECK_RGBA(-1)

            PyErr_Clear();

            self->color = make_shared<gp::Color>(red, green, blue, alpha);
            return 0;
        }
        PyErr_Clear();

        RAISE_VALUE_ERROR(-1, "invalid color format");
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
    static PyObject *PyNumber_Add(PyObject * o1, PyObject * o2) {
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

            const int val = (int) PyLong_AsLong(o1);
            red += val;
            green += val;
            blue += val;
        }

        return color::create(red, green, blue, alpha);
    }

    static PyObject *PyNumber_Subtract(PyObject * o1, PyObject * o2) {
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

            const int val = (int) PyLong_AsLong(o1);
            red += val;
            green += val;
            blue += val;
        }

        return color::create(red, green, blue, alpha);
    }

    static PyObject *PyNumber_InPlaceAdd(PyObject * o1, PyObject * o2) {
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

    static PyObject *PyNumber_InPlaceSubtract(PyObject * o1, PyObject * o2) {
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

        const int red = (int) PyLong_AsLong(value);

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

        const int green = (int) PyLong_AsLong(value);

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

        const int blue = (int) PyLong_AsLong(value);

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

        auto alpha = (float) PyFloat_AsDouble(value);

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
            GETTER_SETTER(red),
            GETTER_SETTER(green),
            GETTER_SETTER(blue),
            GETTER_SETTER(alpha),

            {nullptr}
    };

    static PyNumberMethods numbermethods = {
            color::PyNumber_Add,
            color::PyNumber_Subtract,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            color::PyNumber_InPlaceAdd,
            color::PyNumber_InPlaceSubtract,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
    };
}

namespace color {
    namespace rgb {
        static int init(ColorRGBObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            GP_PY_INFO("gp.color.ColorRGB()");

            int red, green, blue;
            float alpha = 1.0f;
            if (PyArg_ParseTuple(args, "iii|f", &red, &green, &blue, &alpha)) {
                CHECK_RGBA(-1)

                self->color = make_shared<gp::ColorRGB>(red, green, blue, alpha);
                self->base.color = self->color;
                return 0;
            }
            PyErr_Clear();

            PyObject * obj;
            if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
                self->color = make_shared<gp::ColorRGB>(((ColorObject *) obj)->color.get());
                self->base.color = self->color;
                return 0;
            }

            RAISE_VALUE_ERROR(-1, "invalid color format");
        }
    }
}

namespace color {
    namespace hex {
        static int init(ColorHexObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            GP_PY_INFO("gp.color.ColorHex()");

            const char *hexstring;
            float alpha = 1.0f;

            if (PyArg_ParseTuple(args, "s|f", &hexstring, &alpha)) {
                CHECK_ALPHA(-1)

                try {
                    self->color = make_shared<gp::ColorHex>(hexstring, alpha);
                }
                catch (const std::invalid_argument &) {
                    RAISE_VALUE_ERROR(-1, "invalid hexstring format");
                }

                self->base.color = self->color;
                return 0;
            }
            PyErr_Clear();

            PyObject * obj;
            if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
                self->color = make_shared<gp::ColorHex>(((ColorObject *) obj)->color.get());
                self->base.color = self->color;
                return 0;
            }

            RAISE_VALUE_ERROR(-1, "invalid hexadecimal color format");
        }
    }
}

namespace color {
    namespace cmyk {
        static int init(ColorCMYKObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            GP_PY_INFO("gp.color.ColorCMYK()");

            float cyan, magenta, yellow, key;
            float alpha = 1.0f;
            if (PyArg_ParseTuple(args, "ffff|f", &cyan, &magenta, &yellow, &key, &alpha)) {
                CHECK_CMYKA(-1)

                self->color = make_shared<gp::ColorCMYK>(cyan, magenta, yellow, key, alpha);
                self->base.color = self->color;
                return 0;
            }
            PyErr_Clear();

            PyObject * obj;
            if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
                self->color = make_shared<gp::ColorCMYK>(((ColorObject *) obj)->color.get());
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

            auto cyan = (float) PyFloat_AsDouble(value);

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

            auto magenta = (float) PyFloat_AsDouble(value);

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

            auto yellow = (float) PyFloat_AsDouble(value);

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

            auto key = (float) PyFloat_AsDouble(value);

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
                GETTER_SETTER(cyan),
                GETTER_SETTER(magenta),
                GETTER_SETTER(yellow),
                GETTER_SETTER(key),

                {nullptr}
        };
    }
}

namespace color {
    namespace hsv {
        static int init(ColorHSVObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            GP_PY_INFO("gp.color.ColorHSV()");

            int hue;
            float saturation, value;
            float alpha = 1.0f;
            if (PyArg_ParseTuple(args, "iff|f", &hue, &saturation, &value, &alpha)) {
                CHECK_HSVA(-1)

                self->color = make_shared<gp::ColorHSV>(hue, saturation, value, alpha);
                self->base.color = self->color;
                return 0;
            }
            PyErr_Clear();

            PyObject * obj;
            if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
                self->color = make_shared<gp::ColorHSV>(((ColorObject *) obj)->color.get());
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

            const int hue = (int) PyLong_AsLong(value);

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

            auto saturation = (float) PyFloat_AsDouble(value);

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

            auto value = (float) PyFloat_AsDouble(value_);

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
                GETTER_SETTER(hue),
                GETTER_SETTER(saturation),
                GETTER_SETTER(value),

                {nullptr}
        };
    }
}

namespace color {
    namespace hsl {
        static int init(ColorHSLObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            GP_PY_TRACE("gp.color.ColorHSL()");

            int hue;
            float saturation, luminance, alpha = 1.0f;

            if (PyArg_ParseTuple(args, "iff|f", &hue, &saturation, &luminance, &alpha)) {
                CHECK_HSLA(-1)

                self->color = make_shared<gp::ColorHSL>(hue, saturation, luminance, alpha);
                self->base.color = self->color;
                return 0;
            }
            PyErr_Clear();

            PyObject * obj;
            if (PyArg_ParseTuple(args, "!O", &ColorType, &obj)) {
                self->color = make_shared<gp::ColorHSL>(((ColorObject *) obj)->color.get());
                self->base.color = self->color;
                return 0;
            }

            RAISE_VALUE_ERROR(-1, "invalid HSL format");
        }

        // Getter & Setters
        static int set_hue(ColorHSLObject *self, PyObject *value, void *Py_UNUSED(closure)) {
            GP_PY_DEBUG("gp.color.ColorHSL.set_hue()");

            #if GP_ERROR_CHECKING
            if (!PyLong_Check(value)) {
                RAISE_TYPE_ERROR(-1, "integer", value);
            }
            #endif

            const int hue = (int) PyLong_AsLong(value);

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

            auto saturation = (float) PyFloat_AsDouble(value);

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

            auto luminance = (float) PyFloat_AsDouble(value);

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
                GETTER_SETTER(hue),
                GETTER_SETTER(saturation),
                GETTER_SETTER(luminance),

                {nullptr}
        };
    }
}

PyTypeObject ColorType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Color",
        sizeof(ColorObject),
        0,
        (destructor) color::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) color::repr,
        &color::numbermethods,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,
        "",
        (traverseproc) color::traverse,
        (inquiry) color::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        (PyGetSetDef *) color::getsetters,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) color::init,
        nullptr,
        PyType_GenericNew,
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

ColorType(ColorRGB, color::rgb::init, nullptr);

ColorType(ColorHex, color::hex::init, nullptr);

ColorType(ColorCMYK, color::cmyk::init, color::cmyk::getsetters);

ColorType(ColorHSV, color::hsv::init, color::hsv::getsetters);

ColorType(ColorHSL, color::hsl::init, color::hsl::getsetters);


static struct PyModuleDef ColorModule = {
        PyModuleDef_HEAD_INIT,
        "color",
        "",
        -1,
        nullptr,
};


PyMODINIT_FUNC PyInit_color() {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_color()" << std::endl;
    #endif

    PyObject * m;
    m = PyModule_Create(&ColorModule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_PYOBJECT_CLASS(ColorType, "Color")

    ColorRGBType.tp_base = &ColorType;
    ColorHexType.tp_base = &ColorType;
    ColorCMYKType.tp_base = &ColorType;
    ColorHSVType.tp_base = &ColorType;
    ColorHSLType.tp_base = &ColorType;

    EXPOSE_PYOBJECT_CLASS(ColorRGBType, "ColorRGB")
    EXPOSE_PYOBJECT_CLASS(ColorHexType, "ColorHex")
    EXPOSE_PYOBJECT_CLASS(ColorCMYKType, "ColorCMYK")
    EXPOSE_PYOBJECT_CLASS(ColorHSVType, "ColorHSV")
    EXPOSE_PYOBJECT_CLASS(ColorHSLType, "ColorHSL")

    static void *PyColor_API[PyColor_API_pointers];
    PyObject * c_api_object;

    PyColor_API[Color_pytype_NUM] = (void *) Color_pytype;
    c_api_object = PyCapsule_New((void *) PyColor_API, "goopylib.ext.color._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
