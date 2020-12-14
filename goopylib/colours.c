#define PY_SSIZE_T_CLEAN

#define raiseGraphicsError(x) PyErr_SetObject(GraphicsError, PyUnicode_FromFormat(x)); return NULL;

#define hex_digit_to_int_incorrect_input "\n\nGraphicsError: digit value for hex_digit_to_int() function must be " \
                                         "between 0 & f (inclusive), not '%c'", letter

#include <Python.h>
#include <structmember.h>

static PyObject *GraphicsError;

static PyObject *Colour_reference;
static PyObject *ColourRGB_reference;
static PyObject *ColourCMYK_reference;
static PyObject *ColourHSL_reference;
static PyObject *ColourHSV_reference;

/*
------------------------------------------------------------------------------------------------------------------------
Internal Functions

*/

int exponentMod(int base, int power, int modulo)
{
    // base cases
    if (base == 0)
        return 0;
    if (power == 0)
        return 1;

    // If power is even
    long y;
    if (power % 2 == 0) {
        y = exponentMod(base, power / 2, modulo);
        y = (y * y) % modulo;
    }

    // If power is odd
    else {
        y = base % modulo;
        y = (y * exponentMod(base, power - 1, modulo) % modulo) % modulo;
    }

    return (int)((y + modulo) % modulo);
}

/*
------------------------------------------------------------------------------------------------------------------------
Colour Structure Definitions

*/

struct ColourRGB {
    int r, g, b;
};

struct ColourCMYK {
    int c, m, y, k;
};

struct ColourHSL {
    int h, s, l;
};

struct ColourHSV {
    int h, s, v;
};

/*
------------------------------------------------------------------------------------------------------------------------
COLOUR TYPE CONVERSIONS

*/


// RGB to other format

char* rgb_to_hex(int red, int green, int blue) {
    static char hex_string[7];

    sprintf(hex_string, "#%02x%02x%02x", red, green, blue);
    return hex_string;
}


struct ColourCMYK rgb_to_cmyk(int red, int green, int blue) {
    red = red / 255;
    green = green / 255;
    blue = blue / 255;

    double k = 1 - Py_MAX(red, Py_MAX(green, blue));
    double k_inverse = 1 - k;

    struct ColourCMYK return_value = {round(100 * (k_inverse - red) / k_inverse), round(100 * (k_inverse - green) / k_inverse), round(100 * (k_inverse - blue) / k_inverse), round(100 * k)};

    return return_value;
}

/*
def rgb_to_hsl(int red, int green, int blue) {
    red /= 255
    green /= 255
    blue /= 255

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    L = 0.5 * (cmax + cmin)

    if delta == 0:
        h = 0
        s = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
        s = delta / (1 - abs(2 * L - 1))
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
        s = delta / (1 - abs(2 * L - 1))
    else:
        h = 60 * (((red - green) / delta) + 4)
        s = delta / (1 - abs(2 * L - 1))

    return round(h), round(100 * s), round(100 * L)
}

def rgb_to_hsv(int red, int green, int blue) {
    red /= 255
    green /= 255
    blue /= 255

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    if delta == 0:
        h = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
    else:
        h = 60 * (((red - green) / delta) + 4)

    s = 0 if cmax == 0 else (delta / cmax)

    return round(h), round(100 * s), round(100 * cmax)
}

// Hex to other format

def hex_to_rgb(hexstring) {
    return (int(hexstring[i:i + 2], 16) for i in (1, 3, 5))
}

def hex_to_cmyk(hexstring):
    red, green, blue = hex_to_rgb(hexstring)

    red /= 255
    green /= 255
    blue /= 255

    k = 1 - max(red, green, blue)
    k_inverse = 1 - k

    return round(100 * (k_inverse - red) / k_inverse), \
           round(100 * (k_inverse - green) / k_inverse), \
           round(100 * (k_inverse - blue) / k_inverse), \
           round(100 * k)
}

def hex_to_hsl(hexstring) {
    red, green, blue = hex_to_rgb(hexstring)

    red /= 255
    green /= 255
    blue /= 255

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    L = 0.5 * (cmax + cmin)

    if delta == 0:
        h = 0
        s = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
        s = delta / (1 - abs(2 * L - 1))
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
        s = delta / (1 - abs(2 * L - 1))
    else:
        h = 60 * (((red - green) / delta) + 4)
        s = delta / (1 - abs(2 * L - 1))

    return round(h), round(100 * s), round(100 * L)
}

def hex_to_hsv(hexstring) {
    red, green, blue = hex_to_rgb(hexstring)

    red /= 255
    green /= 255
    blue /= 255

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    if delta == 0:
        h = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
    else:
        h = 60 * (((red - green) / delta) + 4)

    s = 0 if cmax == 0 else (delta / cmax)

    return round(h), round(100 * s), round(100 * cmax)
}

// CMYK to other format

def cmyk_to_rgb(cyan, magenta, yellow, key) {
    return round(255 * (1 - (cyan + key) / 100)), \
           round(255 * (1 - (magenta + key) / 100)), \
           round(255 * (1 - (yellow + key) / 100))
}

def cmyk_to_hex(cyan, magenta, yellow, key) {
    return "#%02x%02x%02x" % (round(255 * (1 - (cyan + key) / 100)),
                              round(255 * (1 - (magenta + key) / 100)),
                              round(255 * (1 - (yellow + key) / 100)))
}

def cmyk_to_hsl(cyan, magenta, yellow, key) {
    red = 1 - (cyan + key) / 100
    green = 1 - (magenta + key) / 100
    blue = 1 - (yellow + key) / 100

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    L = 0.5 * (cmax + cmin)

    if delta == 0:
        h = 0
        s = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
        s = delta / (1 - abs(2 * L - 1))
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
        s = delta / (1 - abs(2 * L - 1))
    else:
        h = 60 * (((red - green) / delta) + 4)
        s = delta / (1 - abs(2 * L - 1))

    return round(h), round(100 * s), round(100 * L)
}

def cmyk_to_hsv(cyan, magenta, yellow, key) {
    red = 1 - (cyan + key) / 100
    green = 1 - (magenta + key) / 100
    blue = 1 - (yellow + key) / 100

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    if delta == 0:
        h = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
    else:
        h = 60 * (((red - green) / delta) + 4)

    s = 0 if cmax == 0 else delta / cmax

    return round(h), round(100 * s), round(100 * cmax)
}

// HSV to other format

def hsv_to_rgb(hue, saturation, value) {
    saturation /= 100
    value /= 100

    c = value * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = value - c

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    return round(255 * (rgb_[0] + m)), \
           round(255 * (rgb_[1] + m)), \
           round(255 * (rgb_[2] + m))
}

def hsv_to_hex(hue, saturation, value) {
    saturation /= 100
    value /= 100

    c = value * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = value - c

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    return "#%02x%02x%02x" % (round(255 * (rgb_[0] + m)), round(255 * (rgb_[1] + m)), round(255 * (rgb_[2] + m)))
}

def hsv_to_cmyk(hue, saturation, value) {
    saturation /= 100
    value /= 100

    c = value * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = value - c

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    red = rgb_[0] + m
    green = rgb_[1] + m
    blue = rgb_[2] + m

    k = 1 - max(red, green, blue)
    k_inverse = 1 - k

    return round(100 * (k_inverse - red) / k_inverse), \
           round(100 * (k_inverse - green) / k_inverse), \
           round(100 * (k_inverse - blue) / k_inverse), \
           round(100 * k)
}

def hsv_to_hsl(hue, saturation, value) {
    saturation /= 100
    value /= 100

    L = value - (0.5 * value * saturation)
    saturation = 0 if L == 0 else ((value - L) / min(L, 1 - L))

    return hue, round(100 * saturation), round(100 * L)
}

// HSL to other format

def hsl_to_rgb(hue, saturation, luminance) {
    saturation /= 100
    luminance /= 100

    c = (1 - abs(2 * luminance - 1)) * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = luminance - c / 2

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    return round(255 * (rgb_[0] + m)), round(255 * (rgb_[1] + m)), round(255 * (rgb_[2] + m))
}

def hsl_to_hex(hue, saturation, luminance) {
    saturation /= 100
    luminance /= 100

    c = (1 - abs(2 * luminance - 1)) * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = luminance - c / 2

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    return "#%02x%02x%02x" % (round(255 * (rgb_[0] + m)), round(255 * (rgb_[1] + m)), round(255 * (rgb_[2] + m)))
}

def hsl_to_cmyk(hue, saturation, luminance) {
    saturation /= 100
    luminance /= 100

    c = saturation * (1 - abs(2 * luminance - 1))
    m = luminance - c / 2

    x = c * (1 - abs((hue / 60) % 2 - 1))

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    red = rgb_[0] + m
    green = rgb_[1] + m
    blue = rgb_[2] + m

    k = 1 - max(red, green, blue)
    k_inverse = 1 - k

    return round(100 * (k_inverse - red) / k_inverse), \
           round(100 * (k_inverse - green) / k_inverse), \
           round(100 * (k_inverse - blue) / k_inverse), \
           round(100 * k)
}

def hsl_to_hsv(hue, saturation, luminance) {
    saturation /= 100
    luminance /= 100

    v = luminance + saturation * min(luminance, 1 - luminance)
    saturation = 0 if v == 0 else 2 - (2 * luminance / v)

    return hue, round(100 * saturation), round(100 * v)
}
*/

static PyObject* Colours_rgb_to_hex(PyObject *self, PyObject *args) {
    int red, green, blue;

    if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue))
        return NULL;

    return Py_BuildValue("s", rgb_to_hex(red, green, blue));
}

int hex_digit_to_int(char digit) {

    digit = tolower(digit);

    if (isdigit(digit)) {
        return digit - '0';
    }
    else if (digit == 'a') {
        return 10;
    }
    else if (digit == 'b') {
        return 11;
    }
    else if (digit == 'c') {
        return 12;
    }
    else if (digit == 'd') {
        return 13;
    }
    else if (digit == 'e') {
        return 14;
    }
    else if (digit == 'f') {
        return 15;
    }
    return -1;
}

static PyObject* Colours_hex_digit_to_int(PyObject *self, PyObject *args){
    char letter;

    if (!PyArg_ParseTuple(args, "C", &letter)) {
        return NULL;
    }

    int value = hex_digit_to_int(letter);
    if (value == -1) {
        raiseGraphicsError(hex_digit_to_int_incorrect_input)
    }
    return Py_BuildValue("i", value);
}

/* Colour class*/

/* This structure defines what all attributes a Colour class contains */
typedef struct {
    PyObject_HEAD
    int red, green, blue;  /* RGB values for the colour */
    PyObject *colour;  /* A Hexadecimal value for the colour string */
    PyObject *string;
} Colour;

/* This is a function which deallocates memory for a Colour object*/
static void Colour_dealloc(Colour * self) {
    Py_XDECREF(self->string);
    Py_XDECREF(self->colour);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

/* The _new function creates a new instance of the Colour class*/
static PyObject* Colour_new(PyTypeObject *type, PyObject *args, PyObject*kwds) {
    Colour *self;
    self = (Colour *) type->tp_alloc(type, 0); /* allocates memory for the object */

    if (self != NULL) { /* This ensures that there was no error allocating memory */
        self->string = PyUnicode_FromString("");
        if (self->string == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->red = 0;
        self->green = 0; /* Puts 0 as the default value for each RGB value */
        self->blue = 0;
    }
    return (PyObject *) self;
}

static int Colour_init(Colour *self, PyObject *args, PyObject *kwds) {
    return 0;
}

static PyMemberDef Colour_members[] = {
    {"red", T_INT, offsetof(Colour, red), 0,
     "RGB red value of Colour"},

    {"green", T_INT, offsetof(Colour, green), 0,
     "RGB green value of Colour"},

    {"blue", T_INT, offsetof(Colour, blue), 0,
     "RGB blue value of Colour"},

    {"colour", T_OBJECT_EX, offsetof(Colour, colour), 0,
     "Hexadecimal colour value of Colour"},

     {"string", T_OBJECT_EX, offsetof(Colour, string), 0,
     "Reprent string value of Colour"},

    {NULL}
};

static PyObject *Colour_rgb_string(Colour *self, PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromFormat("rgb %i, %i, %i", self->red, self->green, self->blue);
}

static PyObject *Colour_hex_string(Colour *self, PyObject *Py_UNUSED(ignored)) {
    return self->colour;
}

static Colour *Colour_update_values(Colour *self) {
    self->string = PyUnicode_FromFormat("rgb %c, %c, %c", self->red, self->green, self->blue);
    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);
    return self;
}

static PyMethodDef Colour_methods[] = {
    {"rgb_string", (PyCFunction) Colour_rgb_string, METH_NOARGS,
     "Return the rgb value of the colour"},

     {"hex_string", (PyCFunction) Colour_hex_string, METH_NOARGS,
     "Return the hex value of the colour"},

    {NULL}  /* Sentinel */
};

static PyObject *Colour_repr(Colour *self) {
    Py_INCREF(self->string);
    return self->string;
}

static PyObject *Colour_str(Colour *self) {
    Py_INCREF(self->colour);
    return self->colour;
}

static PyObject *Colour_iter(Colour *self) {

}

static PyTypeObject ColourType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.Colour",
    .tp_doc = "The superclass of all goopylib colour classes",
    .tp_basicsize = sizeof(Colour),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = (newfunc) Colour_new,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) Colour_init,

    .tp_members = Colour_members,
    .tp_methods = Colour_methods,

    .tp_repr = (reprfunc) Colour_repr,
    .tp_str = (reprfunc) Colour_str,
};

#include "colours_Colour_NumberMethods.h"

/* ColourRGB class*/

typedef struct {
    Colour superclass;
    int red, green, blue;  /* RGB values for the colour */
    PyObject *colour;  /* A Hexadecimal value for the colour string */
    PyObject *string;
} ColourRGB;

static int ColourRGB_init(Colour *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"red", "green", "blue", NULL};

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    int red = 0, green = 0, blue = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &red, &green, &blue))
        return -1;

    self->string = PyUnicode_FromFormat("rgb %c, %c, %c", red, green, blue);

    self->red = red;
    self->green = green;
    self->blue = blue;

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourRGBType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourRGB",
    .tp_doc = "An object to represent goopylib colours using RGB values",
    .tp_basicsize = sizeof(ColourRGB),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourRGB_init,
    .tp_members = Colour_members,
};

/* ColourCMYK class*/

typedef struct {
    Colour superclass;
    int red, green, blue;
    PyObject *colour;
    PyObject *string;
} ColourCMYK;

static int ColourCMYK_init(Colour *self, PyObject *args, PyObject *kwds) {

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    static char *kwlist[] = {"c", "m", "y", "k", NULL};

    int c = 0, m = 0, y = 0, k = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist, &c, &m, &y, &k))
        return -1;

    int red = 255 * (1 - (c + k) / 100);
    int green = 255 * (1 - (m + k) / 100);
    int blue = 255 * (1 - (y + k) / 100);

    self->string = PyUnicode_FromFormat("cmyk %c%%, %c%%, %c%%", c, m, y, k);

    self->red = red;
    self->green = green;
    self->blue = blue;

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourCMYKType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourCMYK",
    .tp_doc = "An object to represent goopylib colours using CMYK values",
    .tp_basicsize = sizeof(ColourCMYK),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourCMYK_init,
    .tp_members = Colour_members,
};

/* ColourHex class*/

typedef struct {
    Colour superclass;
    int red, green, blue;
    PyObject *colour;
    PyObject *string;
} ColourHex;

static int ColourHex_init(Colour *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"colour", NULL};

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    PyObject* colour_obj;
    char colour[8];

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|U", kwlist, &colour_obj))
        return -1;

    strncpy(colour, PyBytes_AS_STRING(PyUnicode_AsEncodedString(PyObject_Repr(colour_obj), "utf-8", "~E~")) + 1, 7);
    colour[7] = '\0';

    self->red = (16 * hex_digit_to_int(colour[1])) + hex_digit_to_int(colour[2]);
    self->green = (16 * hex_digit_to_int(colour[3])) + hex_digit_to_int(colour[4]);
    self->blue = (16 * hex_digit_to_int(colour[5])) + hex_digit_to_int(colour[6]);

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);
    self->string = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourHexType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourHex",
    .tp_doc = "An object to represent goopylib colours using Hexadecimal values",
    .tp_basicsize = sizeof(ColourHex),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourHex_init,
    .tp_members = Colour_members,
};

/* ColourHSL class*/

typedef struct {
    Colour superclass;
    int red, green, blue;
    PyObject *colour;
    PyObject *string;
} ColourHSL;

static int ColourHSL_init(Colour *self, PyObject *args, PyObject *kwds) {

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    static char *kwlist[] = {"h", "s", "l", NULL};

    int h = 0, s = 0, l_input = 0;
    float l = 0.0f;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &h, &s, &l_input))
        return -1;

    l = l_input / 100.0f;

    /* Conversion from HSL to RGB */

    float c = (1 - fabsf(2*l - 1)) * (s/100.0f);
    float x = c * (1 - fabsf((float)fmod(h / 60.0f, 2) - 1));
    float m = l - c/2;

    int red = 0, green = 0, blue = 0;

    if (h < 60) {
        red = (int)round(255 * (c + m));
        green = (int)round(255 * (x + m));
        blue = (int)round(255 * m);
    }
    else if (h < 120) {
        red = (int)round(255 * (x + m));
        green = (int)round(255 * (c + m));
        blue = (int)round(255 * m);
    }
    else if (h < 180) {
        red = (int)round(255 * m);
        green = (int)round(255 * (c + m));
        blue = (int)round(255 * (x + m));
    }
    else if (h < 240) {
        red = (int)round(255 * m);
        green = (int)round(255 * (x + m));
        blue = (int)round(255 * (c + m));
    }
    else if (h < 300) {
        red = (int)round(255 * (x + m));
        green = (int)round(255 * m);
        blue = (int)round(255 * (c + m));
    }
    else {
        red = (int)round(255 * (c + m));
        green = (int)round(255 * m);
        blue = (int)round(255 * (x + m));
    }

    self->red = red;
    self->green = green;
    self->blue = blue;

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourHSLType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourHSL",
    .tp_doc = "An object to represent goopylib colours using HSL values",
    .tp_basicsize = sizeof(ColourHSL),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourHSL_init,
    .tp_members = Colour_members,
};

/* ColourHSV class*/

typedef struct {
    Colour superclass;
    int red, green, blue;
    PyObject *colour;
    PyObject *string;
} ColourHSV;

static int ColourHSV_init(Colour *self, PyObject *args, PyObject *kwds) {

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    static char *kwlist[] = {"h", "s", "v", NULL};

    int h = 0, s = 0, v_input = 0;
    float v = 0.0f;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &h, &s, &v_input))
        return -1;

    /* Conversion from HSV to RGB */

    v = v_input / 100.0f;

    float c = v * (s / 100.0f);
    float x = c * (1 - fabsf((float)fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    int red = 0, green = 0, blue = 0;

    if (h < 60) {
        red = (int)round(255 * (c + m));
        green = (int)round(255 * (x + m));
        blue = (int)round(255 * m);
    }
    else if (h < 120) {
        red = (int)round(255 * (x + m));
        green = (int)round(255 * (c + m));
        blue = (int)round(255 * m);
    }
    else if (h < 180) {
        red = (int)round(255 * m);
        green = (int)round(255 * (c + m));
        blue = (int)round(255 * (x + m));
    }
    else if (h < 240) {
        red = (int)round(255 * m);
        green = (int)round(255 * (x + m));
        blue = (int)round(255 * (c + m));
    }
    else if (h < 300) {
        red = (int)round(255 * (x + m));
        green = (int)round(255 * m);
        blue = (int)round(255 * (c + m));
    }
    else {
        red = (int)round(255 * (c + m));
        green = (int)round(255 * m);
        blue = (int)round(255 * (x + m));
    }

    self->red = red;
    self->green = green;
    self->blue = blue;

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourHSVType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourHSV",
    .tp_doc = "An object to represent goopylib colours using HSV values",
    .tp_basicsize = sizeof(ColourHSV),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourHSV_init,
    .tp_members = Colour_members,
};

/* CPython API & Module Related Functions */

static PyMethodDef c_colours_funcs[] = {

    {"rgb_to_hex", (PyCFunction)Colours_rgb_to_hex, METH_VARARGS,
    "rgb_to_hex(int r, int g, int b) -> string (#rrggbb)\nConverts RGB values to a hex string"},

    {"hex_digit_to_int", (PyCFunction)Colours_hex_digit_to_int, METH_VARARGS,
    "hex_digit_to_int(char digit) -> int\nConverts a hexadecimal digit to an integer"},

    {NULL, NULL, 0, NULL}};

static PyModuleDef c_colours_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "c_colours_module",
    .m_doc = "C implementation of a module to work with colours!",
    .m_size = -1, c_colours_funcs};


PyMODINIT_FUNC PyInit_c_colours(void){

    PyObject *m;

    ColourType.tp_as_number = &Colour_number_methods;
    ColourType.tp_as_sequence = &Colour_sequence_methods;
    ColourType.tp_richcompare = (richcmpfunc)&Colour_richcompare;

    ColourRGBType.tp_base = &ColourType;
    ColourHexType.tp_base = &ColourType;
    ColourCMYKType.tp_base = &ColourType;
    ColourHSLType.tp_base = &ColourType;
    ColourHSVType.tp_base = &ColourType;

    if (PyType_Ready(&ColourType) < 0)
        return NULL;
    if (PyType_Ready(&ColourRGBType) < 0)
        return NULL;
    if (PyType_Ready(&ColourCMYKType) < 0)
        return NULL;
    if (PyType_Ready(&ColourHexType) < 0)
        return NULL;
    if (PyType_Ready(&ColourHSLType) < 0)
        return NULL;
    if (PyType_Ready(&ColourHSVType) < 0)
        return NULL;

    m = PyModule_Create(&c_colours_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&ColourType);
    Py_INCREF(&ColourRGBType);
    Py_INCREF(&ColourCMYKType);
    Py_INCREF(&ColourHexType);
    Py_INCREF(&ColourHSLType);
    Py_INCREF(&ColourHSVType);

    if (PyModule_AddObject(m, "Colour", (PyObject *) &ColourType) < 0) {
        Py_DECREF(&ColourType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourRGB", (PyObject *) &ColourRGBType) < 0) {
        Py_DECREF(&ColourRGBType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourCMYK", (PyObject *) &ColourCMYKType) < 0) {
        Py_DECREF(&ColourCMYKType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourHex", (PyObject *) &ColourHexType) < 0) {
        Py_DECREF(&ColourHexType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourHSL", (PyObject *) &ColourHSLType) < 0) {
        Py_DECREF(&ColourHSLType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourHSV", (PyObject *) &ColourHSVType) < 0) {
        Py_DECREF(&ColourHSVType);
        Py_DECREF(m);
        return NULL;}

    GraphicsError = PyErr_NewException("goopylib.GraphicsError.Colours", NULL, NULL);
    Py_XINCREF(GraphicsError);

    Colour_reference = (PyObject *) &ColourType;
    ColourRGB_reference = (PyObject *) &ColourRGBType;
    ColourCMYK_reference = (PyObject *) &ColourCMYKType;
    ColourHSL_reference = (PyObject *) &ColourHSLType;
    ColourHSV_reference = (PyObject *) &ColourHSVType;

    if (PyModule_AddObject(m, "GraphicsError", GraphicsError) < 0) {
        Py_XDECREF(GraphicsError);
		Py_CLEAR(GraphicsError);
		Py_DECREF(m);
		return NULL;}

    return m;
}
