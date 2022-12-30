#pragma once

#include "header.h"
#include "color_object.h"

extern PyTypeObject ColorType;

struct ColorRGBObject;

struct ColorHexObject;

struct ColorCMYKObject;

struct ColorHSVObject;

struct ColorHSLObject;

namespace color {
    static bool isinstance(PyObject *object);

    static PyObject *create(int red, int green, int blue, float alpha = 1.0f);
}

// Color Object
namespace color {
    static int init(ColorObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(ColorObject *self);

    static int traverse(ColorObject *self, visitproc visit, void *arg);

    static int clear(ColorObject *self);

    static void dealloc(ColorObject *self);
}

// PyNumber API
namespace color {
    static PyObject *PyNumber_Add(PyObject *o1, PyObject *o2);

    static PyObject *PyNumber_Subtract(PyObject *o1, PyObject *o2);

    static PyObject *PyNumber_InPlaceAdd(PyObject *o1, PyObject *o2);

    static PyObject *PyNumber_InPlaceSubtract(PyObject *o1, PyObject *o2);
}

// Getter & Setters
namespace color {
    static int set_red(ColorObject *self, PyObject *value, void *closure);

    static PyObject *get_red(ColorObject *self, PyObject *args);

    static int set_green(ColorObject *self, PyObject *value, void *closure);

    static PyObject *get_green(ColorObject *self, PyObject *args);

    static int set_blue(ColorObject *self, PyObject *value, void *closure);

    static PyObject *get_blue(ColorObject *self, PyObject *args);

    static int set_alpha(ColorObject *self, PyObject *value, void *closure);

    static PyObject *get_alpha(ColorObject *self, PyObject *args);
}

namespace color::rgb {
    static int init(ColorRGBObject *self, PyObject *args, PyObject *kwds);
}

namespace color::hex {
    static int init(ColorHexObject *self, PyObject *args, PyObject *kwds);
}

namespace color::cmyk {
    static int init(ColorCMYKObject *self, PyObject *args, PyObject *kwds);

    static int set_cyan(ColorCMYKObject *self, PyObject *value, void *closure);

    static PyObject *get_cyan(ColorCMYKObject *self, PyObject *args);

    static int set_magenta(ColorCMYKObject *self, PyObject *value, void *closure);

    static PyObject *get_magenta(ColorCMYKObject *self, PyObject *args);

    static int set_yellow(ColorCMYKObject *self, PyObject *value, void *closure);

    static PyObject *get_yellow(ColorCMYKObject *self, PyObject *args);

    static int set_key(ColorCMYKObject *self, PyObject *value, void *closure);

    static PyObject *get_key(ColorCMYKObject *self, PyObject *args);
}

namespace color::hsv {
    static int init(ColorHSVObject *self, PyObject *args, PyObject *kwds);
    
    static int set_hue(ColorHSVObject *self, PyObject *value, void *closure);

    static PyObject *get_hue(ColorHSVObject *self, PyObject *args);

    static int set_saturation(ColorHSVObject *self, PyObject *value, void *closure);

    static PyObject *get_saturation(ColorHSVObject *self, PyObject *args);

    static int set_value(ColorHSVObject *self, PyObject *value_, void *closure);

    static PyObject *get_value(ColorHSVObject *self, PyObject *args);
}

namespace color::hsl {
    static int init(ColorHSLObject *self, PyObject *args, PyObject *kwds);
    
    static int set_hue(ColorHSLObject *self, PyObject *value, void *closure);

    static PyObject *get_hue(ColorHSLObject *self, PyObject *args);

    static int set_saturation(ColorHSLObject *self, PyObject *value, void *closure);

    static PyObject *get_saturation(ColorHSLObject *self, PyObject *args);

    static int set_luminance(ColorHSLObject *self, PyObject *value, void *closure);
    
    static PyObject *get_luminance(ColorHSLObject *self, PyObject *args);
}
