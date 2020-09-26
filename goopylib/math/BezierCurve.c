#define PY_SSIZE_T_CLEAN 16

#include <Python.h>
#include <math.h>


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

PyObject* bezier_curve(float t, int size, long long control_points[]){

    float sum_x = 0, sum_y = 0;

    if (size > 5)

        int degree = size - 1, index = 0;

        size *= 2;

        for (int i = 0; i < size; i += 2) {
            float coeff = bernstein_polynomial(index, degree, t);
            sum_x += coeff * control_points[i];
            sum_y += coeff * control_points[i + 1];

            index++;
        }

        return Py_BuildValue("[f, f]", sum_x, sum_y);

    float t2 = 0, t3 = 0, t4 = 0;

    switch (size) {
        case 2:
            sum_x = ((1 - t) * control_points[0]) + (t * control_points[2]);
            sum_y = ((1 - t) * control_points[1]) + (t * control_points[3]);
            break;

        case 3:
            t2 = t * t;

            t *= 2;

            sum_x = ((t2 - t + 1) * control_points[0]) +
            (((-2 * t2) + t) * control_points[2]) +
            (t2 * control_points[4]);

            sum_y = ((t2 - t + 1) * control_points[1]) +
            (((-2 * t2) + t) * control_points[3]) +
            (t2 * control_points[5]);

            break;

        case 4:
            t2 = t * t;
            t3 = t2 * t;

            t *= 3;

            sum_x = ((-t3 + (3 * t2) - t + 1) * control_points[0]) +
            (((3 * t3) - (6 * t2) + t) * control_points[2]) +
            (((-3 * t3) + (3 * t2)) * control_points[4]) +
            (t3 * control_points[6]);

            sum_y = ((-t3 + (3 * t2) - t + 1) * control_points[1]) +
            (((3 * t3) - (6 * t2) + t) * control_points[3]) +
             (((-3 * t3) + (3 * t2)) * control_points[5]) +
            (t3 * control_points[7]);

            break;

        case 5:
            t2 = t * t;
            t3 = t2 * t;
            t4 = t3 * t;

            t *= 4;

            sum_x = ((t4 - (4 * t3) + (6 * t2) - t + 1) * control_points[0]) +
            (((-4 * t4) + (12 * t3) - (12 * t2) + t) * control_points[2]) +
            (((6 * t4) - (12 * t3) + (6 * t2)) * control_points[4]) +
            (((-4 * t4) + (4 * t3)) * control_points[6]) +
            (t4 * control_points[8]);

            sum_y = ((t4 - (4 * t3) + (6 * t2) - t + 1) * control_points[1]) +
            (((-4 * t4) + (12 * t3) - (12 * t2) + t) * control_points[3]) +
            (((6 * t4) - (12 * t3) + (6 * t2)) * control_points[5]) +
            (((-4 * t4) + (4 * t3)) * control_points[7]) +
            (t4 * control_points[9]);

            break;}

    return Py_BuildValue("[f, f]", sum_x, sum_x);
}

PyObject* rational_bezier_curve(float t, int size, long long control_points[],
float weights[]) {

    float sum_x_denominator = 0, sum_y_denominator = 0, sum_x_numerator = 0, sum_y_numerator = 0;
    int degree = size - 1, index = 0;

    size *= 2;

    for (int i = 0; i < size; i += 2) {
        float coeff = bernstein_polynomial(index, degree, t) * weights[index];
        sum_x_numerator += coeff * control_points[i];
        sum_y_numerator += coeff * control_points[i + 1];

        sum_x_denominator += coeff;
        sum_y_denominator += coeff;

        index++;
    }

    return Py_BuildValue("[f, f]", sum_x_numerator / sum_x_denominator, sum_y_numerator / sum_y_denominator);
}

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
    int size;
    float t;
    PyObject *py_control_points, *temp1, *x, *y;

    if (!PyArg_ParseTuple(args, "fO", &t, &py_control_points))
        return NULL;

    size = PyLong_AsLong(PyLong_FromSsize_t(PyList_GET_SIZE(py_control_points)));

    long long *control_points = (long long*)malloc(size * sizeof(long long) * 2);
    int index = 0;

    for (int i = 0; i < size; i++){

        temp1 = PyList_GetItem(py_control_points, i);

        x = PyList_GetItem(temp1, 0);
        y = PyList_GetItem(temp1, 1);

        control_points[index] = PyLong_AsLongLong(x);
        control_points[index + 1] = PyLong_AsLongLong(y);
        index += 2;
    }

    return bezier_curve(t, size, control_points);
}

static PyObject* BezierCurve_rational_bezier_curve(PyObject* self, PyObject* args) {
    Py_ssize_t size;
    float t;
    PyObject *py_control_points, *py_weights, *temp1, *x, *y, *temp2;

    if (!PyArg_ParseTuple(args, "fOO", &t, &py_control_points, &py_weights))
        return NULL;

    if (PyList_Check(py_control_points) == 1) {
        if (PyList_Check(py_weights) == 1) {
            size = PyList_Size(py_control_points);

            if (size > 21) {
                PyErr_SetString(PyErr_NewException("GraphicsError", NULL, NULL),
                "\n\nGraphicsError: The Rational Bezier Curve Function is no longer accurate after the number of control points exceeds 20, use the py_rational_bezier_curve() function instead");
                return NULL;}

            if (size != PyList_Size(py_weights)) {
                PyErr_SetString(PyErr_NewException("GraphicsError", NULL, NULL),
                "\n\nGraphicsError: the length of weights must match the length of control_points");
                return NULL;}

            long long *control_points = (long long*)malloc(size * sizeof(long long) * 2);
            float *weights = (float*)malloc(size * sizeof(float));
            int index = 0;

            for (Py_ssize_t i = 0; i < size; i++){

                temp1 = PyList_GetItem(py_control_points, i);
                temp2 = PyList_GetItem(py_weights, i);

                if (PyList_Check(temp1) == 1) {
                    x = PyList_GetItem(temp1, 0);
                    y = PyList_GetItem(temp1, 1);

                    if (PyFloat_Check(temp2) == 1 || PyNumber_Check(temp2) == 1) {
                        if (PyNumber_Check(x) == 1 && PyNumber_Check(y) == 1) {
                            weights[i] = PyFloat_AsDouble(temp2);

                            control_points[index] = PyLong_AsLongLong(x);
                            control_points[index + 1] = PyLong_AsLongLong(y);
                            index += 2;}
                        else {
                            PyErr_SetString(PyErr_NewException("GraphicsError", NULL, NULL),

                            PyBytes_AsString(PyBytes_FromFormat("\n\nGraphicsError: x & y elements of control_points at index %xd must be an integer, not [%s, %s]",
                            i, PyBytes_AsString(PyObject_Repr(x)), PyBytes_AsString(PyObject_Repr(y)))));
                            return NULL;}
                    }
                    else {
                        PyErr_SetString(PyErr_NewException("GraphicsError", NULL, NULL),
                        PyBytes_AsString(PyBytes_FromFormat("\n\nGraphicsError: each element of weights must be an integer or float, not %s at index %zd",
                        PyBytes_AsString(PyObject_Repr(temp2)), i)));

                        return NULL;}
                }
                else {
                    PyErr_SetString(PyErr_NewException("GraphicsError", NULL, NULL),
                    PyBytes_AsString(PyBytes_FromFormat("\n\nGraphicsError: each element of control_points must be a list in the form [x, y], not %s at index %zd",
                    PyBytes_AsString(PyObject_Repr(temp1)), i)));

                    return NULL;}
            }

            return rational_bezier_curve(t, size, control_points, weights);
        }
        else {
            PyErr_SetString(PyErr_NewException("GraphicsError", NULL, NULL),
            PyBytes_AsString(PyBytes_FromFormat("\n\nGraphicsError: weights argument for rational bezier curve must be a list, not %s",
            PyBytes_AsString(PyObject_Repr(py_weights)))));

            return NULL;}
    }
    else {
        PyErr_SetString(PyErr_NewException("GraphicsError", NULL, NULL),

        PyBytes_AsString(PyBytes_FromFormat("\n\nGraphicsError: control_points argument for rational bezier curve must be a list, not %s",
        PyBytes_AsString(PyObject_Repr(py_control_points)))));

        return NULL;}
}



static PyMethodDef CBezierCurve_funcs[] = {
    {"factorial", (PyCFunction)BezierCurve_factorial, METH_VARARGS, "factorial(x): calculates factorial of x"},
    {"combination", (PyCFunction)BezierCurve_combination, METH_VARARGS, "combination(n, k): calculates nCk"},
    {"bernstein_polynomial", (PyCFunction)BezierCurve_bernstein_polynomial, METH_VARARGS,
    "bernstein_polynomial(i, n, t): calculates the ith bernstein_polynomial at t for n-degrees"},

    {"bezier_curve", (PyCFunction)BezierCurve_bezier_curve, METH_VARARGS,
    "bezier_curve(t, control_points): calculates the bezier curve at point t for control_points"},

    {"rational_bezier_curve", (PyCFunction)BezierCurve_rational_bezier_curve, METH_VARARGS,
    "rational_bezier_curve(t, control_points, weights): calculates the rational bezier curve at point t for control_points & weights"},

    {NULL, NULL, 0, NULL}};

static struct PyModuleDef CBezierCurveModule = {
    PyModuleDef_HEAD_INIT,
    "CBezierCurveModule", "Functions to Calculate Bezier Curves.",
    -1, CBezierCurve_funcs};

PyMODINIT_FUNC PyInit_CBezierCurve(void){
    return PyModule_Create(&CBezierCurveModule);
}