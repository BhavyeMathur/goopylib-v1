#define PY_SSIZE_T_CLEAN 16

#include <Python.h>
#include <math.h>


static PyObject *GraphicsError;


unsigned long long factorial(int number){
    if (number <= 1)
        return 1;
    else
        return number * factorial(number - 1);
}

unsigned long long combination(int n, int k){
    return factorial(n) / (factorial(k) * factorial(n - k));}

float bernstein_polynomial(int i, int n, float t){
    return combination(n, i) * pow(t, i) * pow(1 - t, n - i);}

static PyObject* BezierCurve_factorial(PyObject *self, PyObject *args){
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    return Py_BuildValue("K", factorial(n));
}

static PyObject* BezierCurve_combination(PyObject *self, PyObject *args){
    int n, k;

    if (!PyArg_ParseTuple(args, "ii", &n, &k))
        return NULL;

    return Py_BuildValue("K", combination(n, k));
}

static PyObject* BezierCurve_bernstein_polynomial(PyObject* self, PyObject* args){
    int i, n;
    float t;

    if (!PyArg_ParseTuple(args, "iif", &i, &n, &t))
        return NULL;

    return Py_BuildValue("f", bernstein_polynomial(i, n, t));
}

static PyObject* BezierCurve_bezier_curve(PyObject* self, PyObject* args) {
    Py_ssize_t size;
    float t;
    PyObject *py_control_points, *temp1, *x, *y;

    if (!PyArg_ParseTuple(args, "fO", &t, &py_control_points))
        return NULL;

    if (PyList_Check(py_control_points) == 1) {
        size = PyList_Size(py_control_points);

        if (size > 20) {
            PyErr_SetString(GraphicsError,
            "\n\nGraphicsError: The Bezier Curve Function is no longer accurate after the number of control points exceeds 20, use the py_bezier_curve() function instead");
            return NULL;}

        float sum_x = 0, sum_y = 0;

        if (size > 5) {
            int degree = size - 1;

            for (Py_ssize_t i = 0; i < size; i++) {
                temp1 = PyList_GetItem(py_control_points, i);

                if (PyList_Check(temp1)) {
                    x = PyList_GetItem(temp1, 0);
                    y = PyList_GetItem(temp1, 1);

                    if (PyNumber_Check(x) == 1 && PyNumber_Check(y) == 1) {
                        float coeff = bernstein_polynomial(i, degree, t);

                        sum_x += coeff * PyLong_AsLongLong(x);
                        sum_y += coeff * PyLong_AsLongLong(y);
                    }
                    else {
                        PyErr_SetObject(GraphicsError,
                        PyUnicode_FromFormat("\n\nGraphicsError: x & y value of control_points must be integers, not [%R, %R] at index %zd", x, y, i));
                        return NULL;}
                }
                else {
                    PyErr_SetObject(GraphicsError,
                    PyUnicode_FromFormat("\n\nGraphicsError: each element of control_points must be a list in the form [x, y], not %R at index %zd", temp1, i));

                    return NULL;}
            }
            return Py_BuildValue("[f, f]", sum_x, sum_y);
        }

        float t2 = 0, t3 = 0, t4 = 0;
        PyObject *p0, *p1, *p2, *p3, *p4;
        PyObject *object_x0, *object_x1, *object_x2, *object_x3, *object_x4;
        PyObject *object_y0, *object_y1, *object_y2, *object_y3, *object_y4;

        long long x0, y0, x1, y1, x2, y2, x3, y3, x4, y4;

        switch (size) {
            case 2:
                p0 = PyList_GetItem(py_control_points, 0);
                p1 = PyList_GetItem(py_control_points, 1);

                if (PyList_Check(p0) == 1) {
                    if (PyList_Check(p1) == 1) {

                        object_x0 = PyList_GetItem(p0, 0);
                        object_y0 = PyList_GetItem(p0, 1);
                        object_x1 = PyList_GetItem(p1, 0);
                        object_y1 = PyList_GetItem(p1, 1);

                        if (PyNumber_Check(object_x0) == 1 && PyNumber_Check(object_y0) == 1) {
                            if (PyNumber_Check(object_x1) == 1 && PyNumber_Check(object_y1) == 1) {

                                x0 = PyLong_AsLongLong(object_x0);
                                y0 = PyLong_AsLongLong(object_y0);
                                x1 = PyLong_AsLongLong(object_x1);
                                y1 = PyLong_AsLongLong(object_y1);

                                sum_x = ((1 - t) * x0) + (t * x1);
                                sum_y = ((1 - t) * y0) + (t * y1);

                            } else {
                                PyErr_SetObject(GraphicsError,
                                PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 2nd control point must be integers, not [%R, %R]", object_x1, object_y1));
                                return NULL;}
                        } else {
                            PyErr_SetObject(GraphicsError,
                            PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 1st control point must be integers, not [%R, %R]", object_x0, object_y0));
                            return NULL;}

                    } else {
                        printf("2.1");
                        PyErr_SetObject(GraphicsError,
                        PyUnicode_FromFormat("\n\nGraphicsError: 2nd control point must be a list in the form [x, y], not %R", p1));
                        return NULL;}
                } else {
                    PyErr_SetObject(GraphicsError,
                    PyUnicode_FromFormat("\n\nGraphicsError: 1st control point must be a list in the form [x, y], not %R", p0));
                    return NULL;}

                return Py_BuildValue("[f, f]", sum_x, sum_x);

            case 3:
                t2 = t * t;
                t *= 2;

                p0 = PyList_GetItem(py_control_points, 0);
                p1 = PyList_GetItem(py_control_points, 1);
                p2 = PyList_GetItem(py_control_points, 2);

                if (PyList_Check(p0) == 1) {
                    if (PyList_Check(p1) == 1) {
                        if (PyList_Check(p2) == 1) {

                            object_x0 = PyList_GetItem(p0, 0);
                            object_y0 = PyList_GetItem(p0, 1);
                            object_x1 = PyList_GetItem(p1, 0);
                            object_y1 = PyList_GetItem(p1, 1);
                            object_x2 = PyList_GetItem(p2, 0);
                            object_y2 = PyList_GetItem(p2, 1);

                            if (PyNumber_Check(object_x0) == 1 && PyNumber_Check(object_y0) == 1) {
                                if (PyNumber_Check(object_x1) == 1 && PyNumber_Check(object_y1) == 1) {
                                    if (PyNumber_Check(object_x2) == 1 && PyNumber_Check(object_y2) == 1) {

                                        x0 = PyLong_AsLongLong(object_x0);
                                        y0 = PyLong_AsLongLong(object_y0);
                                        x1 = PyLong_AsLongLong(object_x1);
                                        y1 = PyLong_AsLongLong(object_y1);
                                        x2 = PyLong_AsLongLong(object_x2);
                                        y2 = PyLong_AsLongLong(object_y2);

                                        sum_x = ((t2 - t + 1) * x0) + (((-2 * t2) + t) * x1) + (t2 * x2);
                                        sum_y = ((t2 - t + 1) * y0) + (((-2 * t2) + t) * y1) + (t2 * y2);

                                    } else {
                                        PyErr_SetObject(GraphicsError,
                                        PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 3rd control point must be integers, not [%R, %R]", object_x2, object_y2));
                                        return NULL;}
                                } else {
                                    PyErr_SetObject(GraphicsError,
                                    PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 2nd control point must be integers, not [%R, %R]", object_x1, object_y1));
                                    return NULL;}
                            } else {
                                PyErr_SetObject(GraphicsError,
                                PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 1st control point must be integers, not [%R, %R]", object_x0, object_y0));
                                return NULL;}

                        } else {
                            PyErr_SetObject(GraphicsError,
                            PyUnicode_FromFormat("\n\nGraphicsError: 3rd control point must be a list in the form [x, y], not %R", p2));
                            return NULL;}
                    } else {
                        PyErr_SetObject(GraphicsError,
                        PyUnicode_FromFormat("\n\nGraphicsError: 2nd control point must be a list in the form [x, y], not %R", p1));
                        return NULL;}
                } else {
                    PyErr_SetObject(GraphicsError,
                    PyUnicode_FromFormat("\n\nGraphicsError: 1st control point must be a list in the form [x, y], not %R", p0));
                    return NULL;}

                return Py_BuildValue("[f, f]", sum_x, sum_x);

            case 4:
                t2 = t * t;
                t3 = t2 * t;
                t *= 3;

                p0 = PyList_GetItem(py_control_points, 0);
                p1 = PyList_GetItem(py_control_points, 1);
                p2 = PyList_GetItem(py_control_points, 2);
                p3 = PyList_GetItem(py_control_points, 3);

                if (PyList_Check(p0) == 1) {
                    if (PyList_Check(p1) == 1) {
                        if (PyList_Check(p2) == 1) {
                            if (PyList_Check(p3) == 1) {

                            object_x0 = PyList_GetItem(p0, 0);
                            object_y0 = PyList_GetItem(p0, 1);
                            object_x1 = PyList_GetItem(p1, 0);
                            object_y1 = PyList_GetItem(p1, 1);
                            object_x2 = PyList_GetItem(p2, 0);
                            object_y2 = PyList_GetItem(p2, 1);
                            object_x3 = PyList_GetItem(p3, 0);
                            object_y3 = PyList_GetItem(p3, 1);

                            if (PyNumber_Check(object_x0) == 1 && PyNumber_Check(object_y0) == 1) {
                                if (PyNumber_Check(object_x1) == 1 && PyNumber_Check(object_y1) == 1) {
                                    if (PyNumber_Check(object_x2) == 1 && PyNumber_Check(object_y2) == 1) {
                                        if (PyNumber_Check(object_x3) == 1 && PyNumber_Check(object_y3) == 1) {

                                            x0 = PyLong_AsLongLong(object_x0);
                                            y0 = PyLong_AsLongLong(object_y0);
                                            x1 = PyLong_AsLongLong(object_x1);
                                            y1 = PyLong_AsLongLong(object_y1);
                                            x2 = PyLong_AsLongLong(object_x2);
                                            y2 = PyLong_AsLongLong(object_y2);
                                            x3 = PyLong_AsLongLong(object_x3);
                                            y3 = PyLong_AsLongLong(object_y3);

                                            sum_x = ((-t3 + (3 * t2) - t + 1) * x0) +
                                            (((3 * t3) - (6 * t2) + t) * x1) +
                                            (((-3 * t3) + (3 * t2)) * x2) + (t3 * x3);

                                            sum_y = ((-t3 + (3 * t2) - t + 1) * y0) +
                                            (((3 * t3) - (6 * t2) + t) * y1) +
                                             (((-3 * t3) + (3 * t2)) * y2) + (t3 * y3);

                                        } else {
                                            PyErr_SetObject(GraphicsError,
                                            PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 4th control point must be integers, not [%R, %R]", object_x3, object_y3));
                                            return NULL;}
                                    } else {
                                        PyErr_SetObject(GraphicsError,
                                        PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 3rd control point must be integers, not [%R, %R]", object_x2, object_y2));
                                        return NULL;}
                                } else {
                                    PyErr_SetObject(GraphicsError,
                                    PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 2nd control point must be integers, not [%R, %R]", object_x1, object_y1));
                                    return NULL;}
                            } else {
                                PyErr_SetObject(GraphicsError,
                                PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 1st control point must be integers, not [%R, %R]", object_x0, object_y0));
                                return NULL;}

                        } else {
                            PyErr_SetObject(GraphicsError,
                            PyUnicode_FromFormat("\n\nGraphicsError: 4th control point must be a list in the form [x, y], not %R", p3));
                            return NULL;}
                    } else {
                        PyErr_SetObject(GraphicsError,
                        PyUnicode_FromFormat("\n\nGraphicsError: 3rd control point must be a list in the form [x, y], not %R", p2));
                        return NULL;}
                } else {
                    PyErr_SetObject(GraphicsError,
                    PyUnicode_FromFormat("\n\nGraphicsError: 2nd control point must be a list in the form [x, y], not %R", p1));
                    return NULL;}
            } else {
                PyErr_SetObject(GraphicsError,
                PyUnicode_FromFormat("\n\nGraphicsError: 1st control point must be a list in the form [x, y], not %R", p0));
                return NULL;}

                return Py_BuildValue("[f, f]", sum_x, sum_x);

            case 5:
                t2 = t * t;
                t3 = t2 * t;
                t4 = t3 * t;
                t *= 4;

                p0 = PyList_GetItem(py_control_points, 0);
                p1 = PyList_GetItem(py_control_points, 1);
                p2 = PyList_GetItem(py_control_points, 2);
                p3 = PyList_GetItem(py_control_points, 3);
                p4 = PyList_GetItem(py_control_points, 4);

                if (PyList_Check(p0) == 1) {
                    if (PyList_Check(p1) == 1) {
                        if (PyList_Check(p2) == 1) {
                            if (PyList_Check(p3) == 1) {
                                if (PyList_Check(p4) == 1) {

                                    object_x0 = PyList_GetItem(p0, 0);
                                    object_y0 = PyList_GetItem(p0, 1);
                                    object_x1 = PyList_GetItem(p1, 0);
                                    object_y1 = PyList_GetItem(p1, 1);
                                    object_x2 = PyList_GetItem(p2, 0);
                                    object_y2 = PyList_GetItem(p2, 1);
                                    object_x3 = PyList_GetItem(p3, 0);
                                    object_y3 = PyList_GetItem(p3, 1);
                                    object_x4 = PyList_GetItem(p4, 0);
                                    object_y4 = PyList_GetItem(p4, 1);

                                    if (PyNumber_Check(object_x0) == 1 && PyNumber_Check(object_y0) == 1) {
                                        if (PyNumber_Check(object_x1) == 1 && PyNumber_Check(object_y1) == 1) {
                                            if (PyNumber_Check(object_x2) == 1 && PyNumber_Check(object_y2) == 1) {
                                                if (PyNumber_Check(object_x3) == 1 && PyNumber_Check(object_y3) == 1) {
                                                    if (PyNumber_Check(object_x4) == 1 &&
                                                    PyNumber_Check(object_y4) == 1) {

                                                        x0 = PyLong_AsLongLong(object_x0);
                                                        y0 = PyLong_AsLongLong(object_y0);
                                                        x1 = PyLong_AsLongLong(object_x1);
                                                        y1 = PyLong_AsLongLong(object_y1);
                                                        x2 = PyLong_AsLongLong(object_x2);
                                                        y2 = PyLong_AsLongLong(object_y2);
                                                        x3 = PyLong_AsLongLong(object_x3);
                                                        y3 = PyLong_AsLongLong(object_y3);
                                                        x4 = PyLong_AsLongLong(object_x4);
                                                        y4 = PyLong_AsLongLong(object_y4);

                                                        sum_x = ((t4 - (4 * t3) + (6 * t2) - t + 1) * x0)
                                                        + (((-4 * t4) + (12 * t3) - (12 * t2) + t) * x1) +
                                                        (((6 * t4) - (12 * t3) + (6 * t2)) * x2) +
                                                        (((-4 * t4) + (4 * t3)) * x3) + (t4 * x4);

                                                        sum_y = ((t4 - (4 * t3) + (6 * t2) - t + 1) * y0)
                                                        + (((-4 * t4) + (12 * t3) - (12 * t2) + t) * y1) +
                                                        (((6 * t4) - (12 * t3) + (6 * t2)) * y2) +
                                                        (((-4 * t4) + (4 * t3)) * y3) + (t4 * y4);

                                                    } else{
                                                        PyErr_SetObject(GraphicsError,
                                                        PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 5th control point must be integers, not [%R, %R]", object_x4, object_y4));
                                                        return NULL;}
                                                } else{
                                                    PyErr_SetObject(GraphicsError,
                                                    PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 4th control point must be integers, not [%R, %R]", object_x3, object_y3));
                                                    return NULL;}
                                            } else{
                                                PyErr_SetObject(GraphicsError,
                                                PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 3rd control point must be integers, not [%R, %R]", object_x2, object_y2));
                                                return NULL;}
                                        } else{
                                            PyErr_SetObject(GraphicsError,
                                            PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 2nd control point must be integers, not [%R, %R]", object_x1, object_y1));
                                            return NULL;}
                                    } else{
                                        PyErr_SetObject(GraphicsError,
                                        PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of the 1st control point must be integers, not [%R, %R]", object_x0, object_y0));
                                        return NULL;}

                                } else{
                                    PyErr_SetObject(GraphicsError,
                                    PyUnicode_FromFormat("\n\nGraphicsError: 5th control point must be a list in the form [x, y], not %R", p4));
                                    return NULL;}
                            } else{
                                PyErr_SetObject(GraphicsError,
                                PyUnicode_FromFormat("\n\nGraphicsError: 4th control point must be a list in the form [x, y], not %R", p3));
                                return NULL;}
                        } else{
                            PyErr_SetObject(GraphicsError,
                            PyUnicode_FromFormat("\n\nGraphicsError: 3rd control point must be a list in the form [x, y], not %R", p2));
                            return NULL;}
                    } else{
                        PyErr_SetObject(GraphicsError,
                        PyUnicode_FromFormat("\n\nGraphicsError: 2nd control point must be a list in the form [x, y], not %R", p1));
                        return NULL;}
                } else{
                    PyErr_SetObject(GraphicsError,
                    PyUnicode_FromFormat("\n\nGraphicsError: 1st control point must be a list in the form [x, y], not %R", p0));
                    return NULL;}

                return Py_BuildValue("[f, f]", sum_x, sum_x);
        }
    }
    else {
        PyErr_SetObject(GraphicsError,
        PyUnicode_FromFormat("\n\nGraphicsError: control_points argument for bezier curve must be a list, not %R", py_control_points));

        return NULL;}
}

static PyObject* BezierCurve_rational_bezier_curve(PyObject* self, PyObject* args) {
    Py_ssize_t size;
    float t, sum_x_denominator = 0, sum_y_denominator = 0, sum_x_numerator = 0, sum_y_numerator = 0;
    PyObject *py_control_points, *py_weights, *temp1, *x, *y, *temp2;

    if (!PyArg_ParseTuple(args, "fOO", &t, &py_control_points, &py_weights))
        return NULL;

    if (PyList_Check(py_control_points) == 1) {
        if (PyList_Check(py_weights) == 1) {
            size = PyList_Size(py_control_points);

            if (size > 21) {
                PyErr_SetString(GraphicsError,
                "\n\nGraphicsError: The Rational Bezier Curve Function is no longer accurate after the number of control points exceeds 20, use the py_rational_bezier_curve() function instead");
                return NULL;}

            if (size != PyList_Size(py_weights)) {
                PyErr_SetString(GraphicsError,
                "\n\nGraphicsError: the length of weights must match the length of control_points");
                return NULL;}

            int degree = size - 1;

            for (Py_ssize_t i = 0; i < size; i++){

                temp1 = PyList_GetItem(py_control_points, i);
                temp2 = PyList_GetItem(py_weights, i);

                if (PyList_Check(temp1) == 1) {
                    x = PyList_GetItem(temp1, 0);
                    y = PyList_GetItem(temp1, 1);

                    if (PyFloat_Check(temp2) == 1) {
                        if (PyNumber_Check(x) == 1 && PyNumber_Check(y) == 1) {
                            float coeff = bernstein_polynomial(i, degree, t) * PyFloat_AsDouble(temp2);

                            sum_x_numerator += coeff * PyLong_AsLongLong(x);
                            sum_y_numerator += coeff * PyLong_AsLongLong(y);

                            sum_x_denominator += coeff;
                            sum_y_denominator += coeff;
                        }
                        else {
                            PyErr_SetObject(GraphicsError,
                            PyUnicode_FromFormat("\n\nGraphicsError: x & y elements of control_points at index %xd must be an integer, not [%R, %R]", i, x, y));
                            
                            return NULL;}
                    }
                    else {
                        PyErr_SetObject(GraphicsError,
                        PyUnicode_FromFormat("\n\nGraphicsError: each element of weights must be an integer, not %R at index %zd", temp2, i));
                        
                        return NULL;}
                }
                else {
                    PyErr_SetObject(GraphicsError,
                    PyUnicode_FromFormat("\n\nGraphicsError: each element of control_points must be a list in the form [x, y], not %R at index %zd", temp1, i));

                    return NULL;}
            }

            return Py_BuildValue("[f, f]", sum_x_numerator / sum_x_denominator, sum_y_numerator / sum_y_denominator);
        }
        else {
            PyErr_SetObject(GraphicsError,
            PyUnicode_FromFormat("\n\nGraphicsError: weights argument for rational bezier curve must be a list, not %R", py_weights));

            return NULL;}
    }
    else {
        PyErr_SetObject(GraphicsError,
        PyUnicode_FromFormat("\n\nGraphicsError: control_points argument for rational bezier curve must be a list, not %R", py_control_points));

        return NULL;}
}


static PyMethodDef CBezierCurve_funcs[] = {
    {"factorial", (PyCFunction)BezierCurve_factorial, METH_VARARGS, "factorial(x) -> unsigned long long\nCalculates factorial of x"},
    {"combination", (PyCFunction)BezierCurve_combination, METH_VARARGS, "combination(n, k) -> unsigned long long\nCalculates nCk"},
    {"bernstein_polynomial", (PyCFunction)BezierCurve_bernstein_polynomial, METH_VARARGS,
    "bernstein_polynomial(i, n, t) -> float\nCalculates the ith bernstein_polynomial at t for n-degrees"},

    {"bezier_curve", (PyCFunction)BezierCurve_bezier_curve, METH_VARARGS,
    "bezier_curve(t, control_points) -> [float, float]\nCalculates the bezier curve at point t for control_points"},

    {"rational_bezier_curve", (PyCFunction)BezierCurve_rational_bezier_curve, METH_VARARGS,
    "rational_bezier_curve(t, control_points, weights) -> [float, float]\nCalculates the rational bezier curve at point t for control_points & weights"},

    {NULL, NULL, 0, NULL}};

static struct PyModuleDef CBezierCurveModule = {
    PyModuleDef_HEAD_INIT,
    "CBezierCurveModule", "Functions to Calculate Bezier Curves.",
    -1, CBezierCurve_funcs};

PyMODINIT_FUNC PyInit_CBezierCurve(void){

    PyObject *m;

    m = PyModule_Create(&CBezierCurveModule);
    if (!m) {
        return NULL;}

    GraphicsError = PyErr_NewException("goopylib.GraphicsError.BezierCurve", NULL, NULL);
    Py_XINCREF(GraphicsError);

    if (PyModule_AddObject(m, "GraphicsError", GraphicsError) < 0) {
        Py_XDECREF(GraphicsError);
		Py_CLEAR(GraphicsError);
		Py_DECREF(m);
		return NULL;
	}
    return m;
}
