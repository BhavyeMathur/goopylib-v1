#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <structmember.h>

static PyObject *GraphicsError;
static PyObject *ColourRGB_reference;

/* Other Functions */

char* rgb_to_hex(int red, int green, int blue) {
    char hex_string[7];

    sprintf(hex_string, "#%x%x%x", red, green, blue);
    return hex_string;
}

static PyObject* Colours_rgb_to_hex(PyObject *self, PyObject *args){
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
    else {
        PyErr_SetObject(GraphicsError, PyUnicode_FromString("\n\nGraphicsError: digit value for hex_digit_to_int() function must be between 0 & f (inclusive)"));
        return -1;
    }
}

static PyObject* Colours_hex_digit_to_int(PyObject *self, PyObject *args){
    char letter;

    if (!PyArg_ParseTuple(args, "C", &letter)) {
        return NULL;
    }

    return Py_BuildValue("i", hex_digit_to_int(letter));
}

/* Colour class*/

/* This structure defines what all attributes a Colour class contains */
typedef struct {
    PyObject_HEAD
    int red, green, blue;  /* RGB values for the colour */
    char colour[7];  /* A Hexadecimal value for the colour string */
    PyObject *string;
} Colour;

/* This is a function which deallocates memory for a Colour object*/
static void Colour_dealloc(Colour * self) {
    Py_XDECREF(self->string);
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

        strncpy(self->colour, "#000000", 7); /* Puts a black hexadecimal value into the colour variable */

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

    {"colour", T_STRING, offsetof(Colour, colour), 0,
     "Hexadecimal colour value of Colour"},

     {"string", T_OBJECT_EX, offsetof(Colour, string), 0,
     "Reprent string value of Colour"},

    {NULL}
};

static PyObject *Colour_rgb_string(Colour *self, PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromFormat("rgb %i, %i, %i", self->red, self->green, self->blue);
}

static PyObject *Colour_hex_string(Colour *self, PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromString(self->colour);
}

static PyMethodDef Colour_methods[] = {
    {"rgb_string", (PyCFunction) Colour_rgb_string, METH_NOARGS,
     "Return the rgb value of the colour"},

     {"hex_string", (PyCFunction) Colour_hex_string, METH_NOARGS,
     "Return the hex value of the colour"},

    {NULL}  /* Sentinel */
};

static PyObject *Colour_repr(Colour *self) {
    return self->string;
}

static PyObject *Colour_str(Colour *self) {
    return PyUnicode_FromString(self->colour);
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
    .tp_new = Colour_new,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) Colour_init,

    .tp_members = Colour_members,
    .tp_methods = Colour_methods,

    .tp_repr = (reprfunc) Colour_repr,
    .tp_str = (reprfunc) Colour_str,
    .tp_iter = (getiterfunc) Colour_iter,
};

/* ColourRGB class*/

typedef struct {
    Colour superclass;
    int red, green, blue;  /* RGB values for the colour */
    char colour[7];  /* A Hexadecimal value for the colour string */
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

    sprintf(self->colour, "#%x%x%x", red, green, blue);

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
    char colour[7];
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

    sprintf(self->colour, "#%x%x%x", red, green, blue);

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
    char colour[7];
    PyObject *string;
} ColourHex;

static int ColourHex_init(Colour *self, PyObject *args, PyObject *kwds) {

    static char *kwlist[] = {"colour", NULL};
    PyObject *colour_object;
    const char colour[7];

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|U", kwlist, &colour_object))
        return -1;

    colour_object = PyUnicode_AsASCIIString(colour_object);
    strcpy(colour, PyBytes_AsString(colour_object));

    self->string = colour;

    self->red = (16 * hex_digit_to_int(colour[1])) + hex_digit_to_int(colour[2]);
    self->green = (16 * hex_digit_to_int(colour[3])) + hex_digit_to_int(colour[4]);
    self->blue = (16 * hex_digit_to_int(colour[5])) + hex_digit_to_int(colour[6]);

    strcpy(self->colour, colour);

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

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
    char colour[7];
    PyObject *string;
} ColourHSL;

static int ColourHSL_init(Colour *self, PyObject *args, PyObject *kwds) {

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    static char *kwlist[] = {"h", "s", "l", NULL};

    int h = 0;
    float s = 0, l = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iff", kwlist, &h, &s, &l))
        return -1;

    /* Conversion from HSL to RGB */

    float c = (1 - abs(2*l - 1)) * s;
    float x = c * (1 - abs(fmod(h / 60.0f, 2) - 1));
    float m = l - c / 2;

    int red = 0, green = 0, blue = 0;

    if (h < 60) {
        red = 255 * (c + m);
        green = 255 * (x + m);
        blue = 255 * m;}

    else if (h < 120) {
        red = 255 * (x + m);
        green = 255 * (c + m);
        blue = 255 * m;}

    else if (h < 180) {
        red = 255 * m;
        green = 255 * (c + m);
        blue = 255 * (x + m);}

    else if (h < 240) {
        red = 255 * m;
        green = 255 * (x + m);
        blue = 255 * (c + m);}

    else if (h < 300) {
        red = 255 * (x + m);
        green = 255 * m;
        blue = 255 * (c + m);}

    else {
        red = 255 * (c + m);
        green = 255 * m;
        blue = 255 * (x + m);}

    self->red = red;
    self->green = green;
    self->blue = blue;

    sprintf(self->colour, "#%x%x%x", red, green, blue);

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
    char colour[7];
    PyObject *string;
} ColourHSV;

static int ColourHSV_init(Colour *self, PyObject *args, PyObject *kwds) {

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    static char *kwlist[] = {"h", "s", "v", NULL};

    int h = 0, s = 0, v = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &h, &s, &v))
        return -1;

    /* Conversion from HSV to RGB */

    float c = v * s;
    float x = c * (1 - abs(fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    int red = 0, green = 0, blue = 0;

    if (h < 60) {
        red = 255 * (c + m);
        green = 255 * (x + m);
        blue = 255 * m;}

    else if (h < 120) {
        red = 255 * (x + m);
        green = 255 * (c + m);
        blue = 255 * m;}

    else if (h < 180) {
        red = 255 * m;
        green = 255 * (c + m);
        blue = 255 * (x + m);}

    else if (h < 240) {
        red = 255 * m;
        green = 255 * (x + m);
        blue = 255 * (c + m);}

    else if (h < 300) {
        red = 255 * (x + m);
        green = 255 * m;
        blue = 255 * (c + m);}

    else {
        red = 255 * (c + m);
        green = 255 * m;
        blue = 255 * (x + m);}

    self->red = red;
    self->green = green;
    self->blue = blue;

    sprintf(self->colour, "#%x%x%x", red, green, blue);

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

/* Colour Object Functions */

static PyObject *Colour_richcompare(Colour *self, PyObject *other, int op) {
    /*
    if (PyObject_IsInstance(other, (PyObject *)&ColourType)) {
        switch (op) {
            case Py_LT:
                if (self->red + self->green + self->blue < other->red + other->green + other->blue) {
                    Py_RETURN_TRUE;}
                else {
                    Py_RETURN_FALSE;}

            case Py_LE:
                if (self->red + self->green + self->blue <= other->red + other->green + other->blue) {
                    Py_RETURN_TRUE;}
                else {
                    Py_RETURN_FALSE;}

            case Py_EQ:
                if (self->red + self->green + self->blue == other->red + other->green + other->blue) {
                    Py_RETURN_TRUE;}
                else {
                    Py_RETURN_FALSE;}

            case Py_NE:
                if (!(self->red + self->green + self->blue == other->red + other->green + other->blue)) {
                    Py_RETURN_TRUE;}
                else {
                    Py_RETURN_FALSE;}

            case Py_GT:
                if (self->red + self->green + self->blue > other->red + other->green + other->blue) {
                    Py_RETURN_TRUE;}
                else {
                    Py_RETURN_FALSE;}

            case Py_GE:
                if (self->red + self->green + self->blue >= other->red + other->green + other->blue) {
                    Py_RETURN_TRUE;}
                else {
                    Py_RETURN_FALSE;}
        }
    }
    else {
        PyErr_SetObject(GraphicsError, PyUnicode_FromFormat("\n\nGraphicsError: comparing operations '<' '>' '=' '!=' '<=' '>=' for Colour object must be with another Colour Type, not %R", other));
        return NULL;}

    Py_RETURN_FALSE; */
}

static PyObject *Colour_add(Colour *self, PyObject* other) {
    return PyObject_CallFunctionObjArgs(ColourRGB_reference, 255, 0, 0);
}

static PyObject *Colour_subtract(Colour *self, PyObject* other) {

}

static PyObject *Colour_multiply(Colour *self, PyObject* other) {

}

static PyObject *Colour_remainder(Colour *self, PyObject* other) {

}

static PyObject *Colour_divmod(Colour *self, PyObject* other) {

}

static PyObject *Colour_power(Colour *self, PyObject* other) {

}

static PyObject *Colour_negative(Colour *self, PyObject* other) {

}

static PyObject *Colour_positive(Colour *self, PyObject* other) {

}

static PyObject *Colour_absolute(Colour *self, PyObject* other) {

}

static PyObject *Colour_bool(Colour *self, PyObject* other) {

}

static PyObject *Colour_invert(Colour *self, PyObject* other) {

}

static PyObject *Colour_lshift(Colour *self, PyObject* other) {

}

static PyObject *Colour_rshift(Colour *self, PyObject* other) {

}

static PyObject *Colour_and(Colour *self, PyObject* other) {

}

static PyObject *Colour_xor(Colour *self, PyObject* other) {

}

static PyObject *Colour_or(Colour *self, PyObject* other) {

}

static PyObject *Colour_int(Colour *self) {

}

static PyObject *Colour_float(Colour *self) {

}

static PyObject *Colour_iadd(Colour *self, PyObject* other) {

}

static PyObject *Colour_isubtract(Colour *self, PyObject* other) {

}

static PyObject *Colour_imultiply(Colour *self, PyObject* other) {

}

static PyObject *Colour_iremainder(Colour *self, PyObject* other) {

}

static PyObject *Colour_ipower(Colour *self, PyObject* other) {

}

static PyObject *Colour_ilshift(Colour *self, PyObject* other) {

}

static PyObject *Colour_irshift(Colour *self, PyObject* other) {

}

static PyObject *Colour_iand(Colour *self, PyObject* other) {

}

static PyObject *Colour_ixor(Colour *self, PyObject* other) {

}

static PyObject *Colour_ior(Colour *self, PyObject* other) {

}

static PyObject *Colour_floor_divide(Colour *self, PyObject* other) {

}

static PyObject *Colour_true_divide(Colour *self, PyObject* other) {

}

static PyObject *Colour_ifloor_divide(Colour *self, PyObject* other) {

}

static PyObject *Colour_itrue_divide(Colour *self, PyObject* other) {

}

static PyObject *Colour_index(Colour *self, PyObject* index) {

}

static PyObject *Colour_length(Colour *self) {

}

static PyObject *Colour_contains(Colour *self, PyObject* other) {

}

static PyObject *Colour_item(Colour *self, PyObject* index) {

}

static PyObject *Colour_dir(Colour *self) {

}

static PyObject *Colour_round(Colour *self, PyObject* n) {

}

static PyObject *Colour_reversed(Colour *self) {

}

static PyObject *Colour_matrix_multiply(Colour *self, PyObject* other) {

}

static PyObject *Colour_imatrix_multiply(Colour *self, PyObject* other) {

}

/* CPython API & Module Related Functions */

static PyMethodDef CColours_funcs[] = {

    {"rgb_to_hex", (PyCFunction)Colours_rgb_to_hex, METH_VARARGS,
    "rgb_to_hex(int r, int g, int b) -> string (#rrggbb)\nConverts RGB values to a hex string"},

    {"hex_digit_to_int", (PyCFunction)Colours_hex_digit_to_int, METH_VARARGS,
    "hex_digit_to_int(char digit) -> int\nConverts a hexadecimal digit to an integer"},

    {NULL, NULL, 0, NULL}};

static PyModuleDef CColoursModule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "CColoursModule",
    .m_doc = "C implementation of a module to work with colours!",
    .m_size = -1, CColours_funcs};


PyMODINIT_FUNC PyInit_CColours(void){

    PyObject *m;

    ColourRGBType.tp_base = &ColourType;
    ColourHexType.tp_base = &ColourType;
    ColourCMYKType.tp_base = &ColourType;
    ColourHSLType.tp_base = &ColourType;
    ColourHSVType.tp_base = &ColourType;

    /*
    ColourType.tp_as_number->nb_add = (binaryfunc)Colour_add;


    ColourType.tp_as_number->nb_subtract = (binaryfunc)Colour_subtract;
    ColourType.tp_as_number->nb_multiply = (binaryfunc)Colour_multiply;
    ColourType.tp_as_number->nb_remainder = (binaryfunc)Colour_remainder;
    ColourType.tp_as_number->nb_divmod = (binaryfunc)Colour_divmod;
    ColourType.tp_as_number->nb_power = (ternaryfunc)Colour_power;

    ColourType.tp_as_number->nb_negative = (unaryfunc)Colour_negative;
    ColourType.tp_as_number->nb_positive = (unaryfunc)Colour_positive;
    ColourType.tp_as_number->nb_absolute = (unaryfunc)Colour_absolute;

    ColourType.tp_as_number->nb_bool = (inquiry)Colour_bool;
    ColourType.tp_as_number->nb_invert = (unaryfunc)Colour_invert;
    ColourType.tp_as_number->nb_lshift = (binaryfunc)Colour_lshift;
    ColourType.tp_as_number->nb_rshift = (binaryfunc)Colour_rshift;

    ColourType.tp_as_number->nb_and = (binaryfunc)Colour_and;
    ColourType.tp_as_number->nb_xor = (binaryfunc)Colour_xor;
    ColourType.tp_as_number->nb_or = (binaryfunc)Colour_or;

    ColourType.tp_as_number->nb_int = (unaryfunc)Colour_int;
    ColourType.tp_as_number->nb_float = (unaryfunc)Colour_float;

    ColourType.tp_as_number->nb_inplace_add = (binaryfunc)Colour_iadd;
    ColourType.tp_as_number->nb_inplace_subtract = (binaryfunc)Colour_isubtract;
    ColourType.tp_as_number->nb_inplace_multiply = (binaryfunc)Colour_imultiply;
    ColourType.tp_as_number->nb_inplace_remainder = (binaryfunc)Colour_remainder;
    ColourType.tp_as_number->nb_inplace_power = (ternaryfunc)Colour_ipower;

    ColourType.tp_as_number->nb_inplace_lshift = (binaryfunc)Colour_ilshift;
    ColourType.tp_as_number->nb_inplace_rshift = (binaryfunc)Colour_irshift;

    ColourType.tp_as_number->nb_inplace_and = (binaryfunc)Colour_iadd;
    ColourType.tp_as_number->nb_inplace_xor = (binaryfunc)Colour_ixor;
    ColourType.tp_as_number->nb_inplace_or = (binaryfunc)Colour_ior;

    ColourType.tp_as_number->nb_floor_divide = (binaryfunc)Colour_floor_divide;
    ColourType.tp_as_number->nb_true_divide = (binaryfunc)Colour_true_divide;
    ColourType.tp_as_number->nb_inplace_floor_divide = (binaryfunc)Colour_ifloor_divide;
    ColourType.tp_as_number->nb_inplace_true_divide = (binaryfunc)Colour_itrue_divide;

    ColourType.tp_as_number->nb_index = (unaryfunc)Colour_index;

    ColourType.tp_as_number->nb_matrix_multiply = (binaryfunc)Colour_matrix_multiply;
    ColourType.tp_as_number->nb_inplace_matrix_multiply = (binaryfunc)Colour_imatrix_multiply;

    */

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

    m = PyModule_Create(&CColoursModule);
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

    ColourRGB_reference = (PyObject *) &ColourRGBType;

    if (PyModule_AddObject(m, "GraphicsError", GraphicsError) < 0) {
        Py_XDECREF(GraphicsError);
		Py_CLEAR(GraphicsError);
		Py_DECREF(m);
		return NULL;}

    return m;
}
