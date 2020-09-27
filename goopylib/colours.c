#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <structmember.h>

static PyObject *GraphicsError;

/* Colour class*/

typedef struct {
    PyObject_HEAD
    int red, green, blue;
    char colour[7];
} Colour;

static void Colour_dealloc(PyObject * self) {
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject* Colour_new(PyTypeObject *type, PyObject *args, PyObject*kwds) {
    Colour *self;

    self = (Colour *) type->tp_alloc(type, 0);

    if (self != NULL) {
        strncpy(self->colour, "#000000", 7);

        self->red = 0;
        self->green = 0;
        self->blue = 0;
    }
    return (PyObject *) self;
}

static int Colour_init(Colour *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"red", "green", "blue", NULL};

    int red = 0, green = 0, blue = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &red, &green, &blue))
        return -1;

    self->red = red;
    self->green = green;
    self->blue = blue;

    sprintf(self->colour, "#%x%x%x", red, green, blue);

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

    {NULL}
};

static PyObject *Colour_rgb(Colour *self, PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromFormat("rgb %i, %i, %i", self->red, self->green, self->blue);
}

static PyObject *Colour_repr(Colour *self) {
    return PyUnicode_FromString(self.colour);
}

static PyObject *Colour_str(Colour *self) {
    return PyUnicode_FromString(self.colour);
}

static PyObject *Colour_richcompare(Colour *self, PyObject *other, int op) {
    /* Py_LT, Py_LE, Py_EQ, Py_NE, Py_GT, Py_GE*/

}

static PyObject *Colour_iter(Colour *self) {

}

static PyObject *Colour_add(Colour *self, PyObject* other) {

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

typedef struct {
    (binaryfunc) *Colour_add;
    (binaryfunc) *Colour_subtract;
    (binaryfunc) *Colour_multiply;
    (binaryfunc) *Colour_remainder;
    (binaryfunc) *Colour_divmod;
    (ternaryfunc) *Colour_power;
    (unaryfunc) *Colour_negative;
    (unaryfunc) *Colour_positive;
    (unaryfunc) *Colour_absolute;
    (inquiry) *Colour_bool;
    (binaryfunc) *Colour_invert;
    (binaryfunc) *Colour_lshift;
    (binaryfunc) *Colour_rshift;
    (binaryfunc) *Colour_and;
    (binaryfunc) *Colour_xor;
    (binaryfunc) *Colour_or;
    (unaryfunc) *Colour_int;
    NULL;
    (unaryfunc) *Colour_float;

    (binaryfunc) *Colour_iadd;
    (binaryfunc) *Colour_isubtract;
    (binaryfunc) *Colour_imultiply;
    (binaryfunc) *Colour_iremainder;
    (ternaryfunc) *Colour_ipower;
    (binaryfunc) *Colour_ilshift;
    (binaryfunc) *Colour_irshift;
    (binaryfunc) *Colour_iand;
    (binaryfunc) *Colour_ixor;
    (binaryfunc) *Colour_ior;

    (binaryfunc) *Colour_floor_divide;
    (binaryfunc) *Colour_true_divide;
    (binaryfunc) *Colour_ifloor_divide;
    (binaryfunc) *Colour_itrue_divide;

    (unaryfunc) *Colour_index;

    (binaryfunc) *Colour_matrix_multiply;
    (binaryfunc) *Colour_imatrix_mulitply;

} Colour_PyNumberMethods;


static PyTypeObject ColourType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.Colour",
    .tp_doc = "The superclass of all goopylib colour classes",
    .tp_basicsize = sizeof(Colour),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_alloc = PyType_GenericNew
    .tp_new = Colour_new,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) Colour_init,
    .tp_members = Colour_members,

    .tp_repr = (reprfunc) Colour_repr,
    .tp_str = (reprfunc) Colour_str,
    .tp_richcompare = (richcmpfunc) Colour_richcompare,
    .tp_iter = (getiterfunc) Colour_iter,
    .tp_as_number = Colour_PyNumberMethods,
};

/* ColourRGB class*/

typedef struct {
    PyObject_HEAD
    int red, green, blue;
    char colour[7];
} ColourRGB;

static PyObject* ColourRGB_new(PyTypeObject *type, PyObject *args, PyObject*kwds) {
    ColourRGB *self;

    self = (ColourRGB *) type->tp_alloc(type, 0);

    if (self != NULL) {
        strncpy(self->colour, "#000000", 7);

        self->red = 0;
        self->green = 0;
        self->blue = 0;
    }
    return (PyObject *) self;
}

static int ColourRGB_init(ColourRGB *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"red", "green", "blue", NULL};

    int red = 0, green = 0, blue = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &red, &green, &blue))
        return -1;

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
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_new = ColourRGB_new,
    .tp_init = (initproc) ColourRGB_init,
    .tp_members = Colour_members,
};

/* ColourCMYK class*/

typedef struct {
    PyObject_HEAD
    int red, green, blue;
    char colour[7];
} ColourCMYK;

static PyObject* ColourCMYK_new(PyTypeObject *type, PyObject *args, PyObject*kwds) {
    ColourCMYK *self;

    self = (ColourCMYK *) type->tp_alloc(type, 0);

    if (self != NULL) {
        strncpy(self->colour, "#000000", 7);

        self->red = 0;
        self->green = 0;
        self->blue = 0;
    }
    return (PyObject *) self;
}

static int ColourCMYK_init(ColourCMYK *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"c", "m", "y", "k", NULL};

    int c = 0, m = 0, y = 0, k = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist, &c, &m, &y, &k))
        return -1;

    int red = 255 * (1 - (c + k) / 100);
    int green = 255 * (1 - (m + k) / 100);
    int blue = 255 * (1 - (y + k) / 100);

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
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_new = ColourCMYK_new,
    .tp_init = (initproc) ColourCMYK_init,
    .tp_members = Colour_members,
};

/* ColourHex class*/

typedef struct {
    PyObject_HEAD
    int red, green, blue;
    char colour[7];
} ColourHex;

static PyObject* ColourHex_new(PyTypeObject *type, PyObject *args, PyObject*kwds) {
    ColourHex *self;

    self = (ColourHex *) type->tp_alloc(type, 0);

    if (self != NULL) {
        strncpy(self->colour, "#000000", 7);

        self->red = 0;
        self->green = 0;
        self->blue = 0;
    }
    return (PyObject *) self;
}

static int ColourHex_init(ColourHex *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"colour", NULL};

    PyObject *hexstring_object;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist, &hexstring_object))
        return -1;

    char colour[7];
    strcpy(colour, PyBytes_AsString(hexstring_object));

    self->red = ((colour[1] <= '9') ? colour[1] - '0' : (colour[1] & 0x7) + 9 << 4) +
                 (colour[2] <= '9') ? colour[2] - '0' : (colour[2] & 0x7) + 9;
    self->green = ((colour[3] <= '9') ? colour[3] - '0' : (colour[3] & 0x7) + 9 << 4) +
                   (colour[4] <= '9') ? colour[4] - '0' : (colour[4] & 0x7) + 9;
    self->blue = ((colour[5] <= '9') ? colour[5] - '0' : (colour[5] & 0x7) + 9 << 4) +
                  (colour[6] <= '9') ? colour[6] - '0' : (colour[6] & 0x7) + 9;;

    strcpy(self->colour, colour);

    return 0;
}

static PyTypeObject ColourHexType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourRGB",
    .tp_doc = "An object to represent goopylib colours using Hexadecimal values",
    .tp_basicsize = sizeof(ColourHex),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_new = ColourHex_new,
    .tp_init = (initproc) ColourHex_init,
    .tp_members = Colour_members,
};

/* Other Functions */

char* rgb_to_hex(int red, int green, int blue) {
    char hex_string[7];

    sprintf(hex_string, "#%x%x%x", red, green, blue);
    return hex_string;
}



/* CPython API & Module Related Functions */

static PyMethodDef CColours_funcs[] = {
    /*
    {"ColourRGB", (PyCFunction)Colours_NewColourRGB, METH_VARARGS,
    "ColourRGB(r, g, b): creates a new colour with the specified RGB values"},*/

    {NULL, NULL, 0, NULL}};

static struct PyModuleDef CColoursModule = {
    PyModuleDef_HEAD_INIT,
    "CColoursModule", "A module to work with colours!",
    -1, CColours_funcs};


PyMODINIT_FUNC PyInit_CColours(void){

    PyObject *m;

    if (PyType_Ready(&ColourType) < 0)
        return NULL;
    if (PyType_Ready(&ColourRGBType) < 0)
        return NULL;
    if (PyType_Ready(&ColourCMYKType) < 0)
        return NULL;
    if (PyType_Ready(&ColourHexType) < 0)
        return NULL;

    m = PyModule_Create(&CColoursModule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&ColourType);
    Py_INCREF(&ColourRGBType);
    Py_INCREF(&ColourCMYKType);
    Py_INCREF(&ColourHexType);

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

    GraphicsError = PyErr_NewException("goopylib.GraphicsError.Colours", NULL, NULL);
    Py_XINCREF(GraphicsError);

    if (PyModule_AddObject(m, "GraphicsError", GraphicsError) < 0) {
        Py_XDECREF(GraphicsError);
		Py_CLEAR(GraphicsError);
		Py_DECREF(m);
		return NULL;}

    return m;
}
