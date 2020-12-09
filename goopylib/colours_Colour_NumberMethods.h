#define Colour_add_incorrect_input "\n\nGraphicsError: unsupported operand type for +: 'Colour' and '%R'. Must be a " \
                                   "Colour or int, not %R", PyObject_Type(other), other
#define Colour_subtract_incorrect_input "\n\nGraphicsError: unsupported operand type for -: 'Colour' and '%R'. Must " \
                                        "be a Colour or int, not %R", PyObject_Type(other), other
#define Colour_multiply_incorrect_input "\n\nGraphicsError: unsupported operand type for *: 'Colour' and '%R'. Must " \
                                        "be a Colour or int, not %R", PyObject_Type(other), other
#define Colour_remainder_incorrect_input "\n\nGraphicsError: unsupported operand type for %: 'Colour' and '%R'. " \
                                         "Must be a Colour or int, not %R", PyObject_Type(other), other

#define Colour_power_power_incorrect_input "\n\nGraphicsError: unsupported type power for pow(): 'Colour' and " \
                                         "'%R'. Must be a Colour or int, not %R", PyObject_Type(power), power
#define Colour_power_modulo_incorrect_input "\n\nGraphicsError: unsupported type modulo for pow(): 'Colour' and " \
                                         "'%R'. Must be a Colour or int, not %R", PyObject_Type(modulo), modulo

#define Colour_divmod_incorrect_input "\n\nGraphicsError: unsupported operand type for divmod(): 'Colour' and '%R'. " \
                                      "Must be a Colour or int, not %R", PyObject_Type(other), other
#define Colour_truedivide_incorrect_input "\n\nGraphicsError: unsupported operand type for /: 'Colour' and '%R'. " \
                                          "Must be a Colour or int, not %R", PyObject_Type(other), other
#define Colour_floordivide_incorrect_input "\n\nGraphicsError: unsupported operand type for //: 'Colour' and '%R'. " \
                                           "Must be a Colour or int, not %R", PyObject_Type(other), other


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

static PyObject *Colour_add(Colour *self, PyObject *other) {
    if (PyObject_IsInstance(other, (PyObject *)&ColourType)) {
        int red = self->red + PyLong_AsLong(PyObject_GetAttrString(other, "red"));
        int green = self->green + PyLong_AsLong(PyObject_GetAttrString(other, "green"));
        int blue = self->blue + PyLong_AsLong(PyObject_GetAttrString(other, "blue"));

        if (red > 255) {
            red = 255;
        }
        else if (red < 0) {
            red = 0;
        }
        if (green > 255) {
            green = 255;
        }
        else if (green < 0) {
            green = 0;
        }
        if (blue > 255) {
            blue = 255;
        }
        else if (green < 0) {
            blue = 0;
        }

        return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                 PyLong_FromLong(green),
                                                                 PyLong_FromLong(blue), NULL);
    }
    else if (PyLong_Check(other)) {
        int other_converted = PyLong_AsLong(other);

        int red = self->red + other_converted;
        int green = self->green + other_converted;
        int blue = self->blue + other_converted;

        if (red > 255) {
            red = 255;
        }
        else if (red < 0) {
            red = 0;
        }
        if (green > 255) {
            green = 255;
        }
        else if (green < 0) {
            green = 0;
        }
        if (blue > 255) {
            blue = 255;
        }
        else if (green < 0) {
            blue = 0;
        }

        return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                 PyLong_FromLong(green),
                                                                 PyLong_FromLong(blue), NULL);
    }
    raiseGraphicsError(Colour_add_incorrect_input)
}

static PyObject *Colour_subtract(Colour *self, PyObject *other) {
    if (PyObject_IsInstance(other, (PyObject *)&ColourType)) {
        int red = self->red - PyLong_AsLong(PyObject_GetAttrString(other, "red"));
        int green = self->green - PyLong_AsLong(PyObject_GetAttrString(other, "green"));
        int blue = self->blue - PyLong_AsLong(PyObject_GetAttrString(other, "blue"));

        if (red > 255) {
            red = 255;
        }
        else if (red < 0) {
            red = 0;
        }
        if (green > 255) {
            green = 255;
        }
        else if (green < 0) {
            green = 0;
        }
        if (blue > 255) {
            blue = 255;
        }
        else if (green < 0) {
            blue = 0;
        }

        return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                 PyLong_FromLong(green),
                                                                 PyLong_FromLong(blue), NULL);
    }
    else if (PyLong_Check(other)) {
        int other_converted = PyLong_AsLong(other);

        int red = self->red - other_converted;
        int green = self->green - other_converted;
        int blue = self->blue - other_converted;

        if (red > 255) {
            red = 255;
        }
        else if (red < 0) {
            red = 0;
        }
        if (green > 255) {
            green = 255;
        }
        else if (green < 0) {
            green = 0;
        }
        if (blue > 255) {
            blue = 255;
        }
        else if (green < 0) {
            blue = 0;
        }

        return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                 PyLong_FromLong(green),
                                                                 PyLong_FromLong(blue), NULL);
    }
    raiseGraphicsError(Colour_subtract_incorrect_input)
}

static PyObject *Colour_multiply(Colour *self, PyObject *other) {
    if (PyObject_IsInstance(other, (PyObject *)&ColourType)) {
        int red = self->red * PyLong_AsLong(PyObject_GetAttrString(other, "red"));
        int green = self->green * PyLong_AsLong(PyObject_GetAttrString(other, "green"));
        int blue = self->blue * PyLong_AsLong(PyObject_GetAttrString(other, "blue"));

        if (red > 255) {
            red = 255;
        }
        else if (red < 0) {
            red = 0;
        }
        if (green > 255) {
            green = 255;
        }
        else if (green < 0) {
            green = 0;
        }
        if (blue > 255) {
            blue = 255;
        }
        else if (green < 0) {
            blue = 0;
        }

        return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                 PyLong_FromLong(green),
                                                                 PyLong_FromLong(blue), NULL);
    }

    else if (PyLong_Check(other)) {
        int other_converted = PyLong_AsLong(other);

        int red = self->red * other_converted;
        int green = self->green * other_converted;
        int blue = self->blue * other_converted;

        if (red > 255) {
            red = 255;
        }
        else if (red < 0) {
            red = 0;
        }
        if (green > 255) {
            green = 255;
        }
        else if (green < 0) {
            green = 0;
        }
        if (blue > 255) {
            blue = 255;
        }
        else if (green < 0) {
            blue = 0;
        }

        return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                 PyLong_FromLong(green),
                                                                 PyLong_FromLong(blue), NULL);
    }
    raiseGraphicsError(Colour_multiply_incorrect_input)
}

static PyObject *Colour_remainder(Colour *self, PyObject *other) {
    if (PyObject_IsInstance(other, (PyObject *)&ColourType)) {
        int red = self->red % PyLong_AsLong(PyObject_GetAttrString(other, "red"));
        int green = self->green % PyLong_AsLong(PyObject_GetAttrString(other, "green"));
        int blue = self->blue % PyLong_AsLong(PyObject_GetAttrString(other, "blue"));

        return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                 PyLong_FromLong(green),
                                                                 PyLong_FromLong(blue), NULL);
    }

    else if (PyLong_Check(other)) {
        int other_converted = PyLong_AsLong(other);

        int red = self->red % other_converted;
        int green = self->green % other_converted;
        int blue = self->blue % other_converted;

        if (red < 0) {
            red = 0;
        }
        if (green < 0) {
            green = 0;
        }
        if (green < 0) {
            blue = 0;
        }

        return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                 PyLong_FromLong(green),
                                                                 PyLong_FromLong(blue), NULL);
    }
    raiseGraphicsError(Colour_remainder_incorrect_input)
}

static PyObject *Colour_divmod(Colour *self, PyObject *other) {
    if (PyObject_IsInstance(other, (PyObject *)&ColourType)) {
        PyObject* return_tuple = PyTuple_New(2);

        int other_red = PyLong_AsLong(PyObject_GetAttrString(other, "red"));
        int other_green = PyLong_AsLong(PyObject_GetAttrString(other, "green"));
        int other_blue = PyLong_AsLong(PyObject_GetAttrString(other, "blue"));

        PyTuple_SetItem(return_tuple, 0, PyObject_CallFunctionObjArgs(ColourRGB_reference,
                                                                      PyLong_FromLong(self->red / other_red),
                                                                      PyLong_FromLong(self->green / other_green),
                                                                      PyLong_FromLong(self->blue / other_blue), NULL));

        PyTuple_SetItem(return_tuple, 1, PyObject_CallFunctionObjArgs(ColourRGB_reference,
                                                                      PyLong_FromLong(self->red % other_red),
                                                                      PyLong_FromLong(self->green % other_green),
                                                                      PyLong_FromLong(self->blue % other_blue), NULL));

        return return_tuple;
    }
    else if (PyLong_Check(other)) {
        PyObject* return_tuple = PyTuple_New(2);

        int other_converted = PyLong_AsLong(other);

        int red = self->red % other_converted;
        int green = self->green % other_converted;
        int blue = self->blue % other_converted;

        if (red < 0) {
            red = 0;
        }
        if (green < 0) {
            green = 0;
        }
        if (green < 0) {
            blue = 0;
        }

        PyTuple_SetItem(return_tuple, 0, PyObject_CallFunctionObjArgs(ColourRGB_reference,
                                                                      PyLong_FromLong(red),
                                                                      PyLong_FromLong(green),
                                                                      PyLong_FromLong(blue), NULL));

        red = self->red / other_converted;
        green = self->green / other_converted;
        blue = self->blue / other_converted;

        if (red < 0) {
            red = 0;
        }
        if (green < 0) {
            green = 0;
        }
        if (green < 0) {
            blue = 0;
        }

        PyTuple_SetItem(return_tuple, 1, PyObject_CallFunctionObjArgs(ColourRGB_reference,
                                                                      PyLong_FromLong(red),
                                                                      PyLong_FromLong(green),
                                                                      PyLong_FromLong(blue), NULL));

        return return_tuple;
    }
    raiseGraphicsError(Colour_divmod_incorrect_input)
}

static PyObject *Colour_power(Colour *self, PyObject *power, PyObject *modulo) {
    if (PyObject_IsInstance(power, (PyObject *)&ColourType)) {
        if (PyObject_IsInstance(modulo, (PyObject *)&ColourType)) {
            int red = exponentMod(self->red, PyLong_AsLong(PyObject_GetAttrString(power, "red")),
                      PyLong_AsLong(PyObject_GetAttrString(modulo, "red")));
            int green = exponentMod(self->green, PyLong_AsLong(PyObject_GetAttrString(power, "green")),
                        PyLong_AsLong(PyObject_GetAttrString(modulo, "green")));
            int blue = exponentMod(self->blue, PyLong_AsLong(PyObject_GetAttrString(power, "blue")),
                       PyLong_AsLong(PyObject_GetAttrString(modulo, "blue")));

            return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                     PyLong_FromLong(green),
                                                                     PyLong_FromLong(blue), NULL);
        }
        else if (PyLong_Check(modulo)) {
            int modulo_converted = PyLong_AsLong(modulo);

            int red = exponentMod(self->red, PyLong_AsLong(PyObject_GetAttrString(power, "red")), modulo_converted);
            int green = exponentMod(self->green, PyLong_AsLong(PyObject_GetAttrString(power, "green")),
                        modulo_converted);
            int blue = exponentMod(self->blue, PyLong_AsLong(PyObject_GetAttrString(power, "blue")), modulo_converted);

            if (red > 255) {
            red = 255;
            }
            else if (red < 0) {
                red = 0;
            }
            if (green > 255) {
                green = 255;
            }
            else if (green < 0) {
                green = 0;
            }
            if (blue > 255) {
                blue = 255;
            }
            else if (green < 0) {
                blue = 0;
            }

            return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                     PyLong_FromLong(green),
                                                                     PyLong_FromLong(blue), NULL);
        }
        raiseGraphicsError(Colour_power_modulo_incorrect_input)
    }
    else if (PyLong_Check(power)) {
        if (PyObject_IsInstance(modulo, (PyObject *)&ColourType)) {
            int power_converted = PyLong_AsLong(power);

            int red = exponentMod(self->red, power_converted,
                      PyLong_AsLong(PyObject_GetAttrString(modulo, "red")));
            int green = exponentMod(self->green, power_converted,
                        PyLong_AsLong(PyObject_GetAttrString(modulo, "green")));
            int blue = exponentMod(self->blue, power_converted,
                       PyLong_AsLong(PyObject_GetAttrString(modulo, "blue")));

            return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                     PyLong_FromLong(green),
                                                                     PyLong_FromLong(blue), NULL);
        }
        else if (PyLong_Check(modulo)) {
            int power_converted = PyLong_AsLong(power);
            int modulo_converted = PyLong_AsLong(modulo);

            int red = exponentMod(self->red, power_converted, modulo_converted);
            int green = exponentMod(self->green, power_converted, modulo_converted);
            int blue = exponentMod(self->blue, power_converted, modulo_converted);

            if (red > 255) {
            red = 255;
            }
            else if (red < 0) {
                red = 0;
            }
            if (green > 255) {
                green = 255;
            }
            else if (green < 0) {
                green = 0;
            }
            if (blue > 255) {
                blue = 255;
            }
            else if (green < 0) {
                blue = 0;
            }

            return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(red),
                                                                     PyLong_FromLong(green),
                                                                     PyLong_FromLong(blue), NULL);
        }
        raiseGraphicsError(Colour_power_modulo_incorrect_input)
    }
    raiseGraphicsError(Colour_power_power_incorrect_input)
}

static PyObject *Colour_negative(Colour *self) {
    return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(255 - self->red),
                                                             PyLong_FromLong(255 - self->green),
                                                             PyLong_FromLong(255 - self->blue), NULL);
}

static PyObject *Colour_positive(Colour *self) {
    return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(self->red),
                                                             PyLong_FromLong(self->green),
                                                             PyLong_FromLong(self->blue), NULL);
}

static PyObject *Colour_absolute(Colour *self) {

    int absval = (int)round((self->red + self->green + self->blue) / 3.0f);

    return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(absval),
                                                             PyLong_FromLong(absval),
                                                             PyLong_FromLong(absval), NULL);
}

static PyObject *Colour_bool(Colour *self) {
    if ((self->red == 0) && (self->green == 0) && (self->blue == 0)) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}

static PyObject *Colour_invert(Colour *self) {
    return PyObject_CallFunctionObjArgs(ColourRGB_reference, PyLong_FromLong(255 - self->red),
                                                             PyLong_FromLong(255 - self->green),
                                                             PyLong_FromLong(255 - self->blue), NULL);
}

static PyObject *Colour_lshift(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_rshift(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_and(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_xor(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_or(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_int(Colour *self) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_float(Colour *self) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_iadd(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_isubtract(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_imultiply(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_iremainder(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_ipower(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_ilshift(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_irshift(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_iand(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_ixor(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_ior(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_floor_divide(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_true_divide(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_ifloor_divide(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_itrue_divide(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_index(Colour *self, PyObject* index) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_length(Colour *self) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_contains(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_item(Colour *self, PyObject* index) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_dir(Colour *self) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_round(Colour *self, PyObject* n) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_reversed(Colour *self) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_matrix_multiply(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyObject *Colour_imatrix_multiply(Colour *self, PyObject* other) {
    return PyObject_CallFunction(Colour_reference, NULL);
}

static PyNumberMethods Colour_number_methods = {
    (binaryfunc)Colour_add,
    (binaryfunc)Colour_subtract,
    (binaryfunc)Colour_multiply,
    (binaryfunc)Colour_remainder,
    (binaryfunc)Colour_divmod,
    (ternaryfunc)Colour_power,

    (unaryfunc)Colour_negative,
    (unaryfunc)Colour_positive,
    (unaryfunc)Colour_absolute,
    (inquiry)Colour_bool,
    (unaryfunc)Colour_invert,

    (binaryfunc)Colour_lshift,
    (binaryfunc)Colour_rshift,

    (binaryfunc)Colour_and,
    (binaryfunc)Colour_xor,
    (binaryfunc)Colour_or,

    (unaryfunc)Colour_int,
    NULL,
    (unaryfunc)Colour_float,

    (binaryfunc)Colour_iadd,
    (binaryfunc)Colour_isubtract,
    (binaryfunc)Colour_imultiply,
    (binaryfunc)Colour_iremainder,
    (ternaryfunc)Colour_ipower,

    (binaryfunc)Colour_ilshift,
    (binaryfunc)Colour_irshift,

    (binaryfunc)Colour_iand,
    (binaryfunc)Colour_ixor,
    (binaryfunc)Colour_ior,

    (binaryfunc)Colour_floor_divide,
    (binaryfunc)Colour_true_divide,
    (binaryfunc)Colour_ifloor_divide,
    (binaryfunc)Colour_itrue_divide,

    (unaryfunc)Colour_index,

    (binaryfunc)Colour_matrix_multiply,
    (binaryfunc)Colour_imatrix_multiply,
};
