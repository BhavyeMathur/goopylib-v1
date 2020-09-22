#define PY_SSIZE_T_CLEAN 16

#include <Python.h>
#include <math.h>


struct DoubleTuple2 {
    double x, y;
};

unsigned long long factorial(unsigned long long number){
    if (number <= 1)
        return 1;
    else
        return number * factorial(number - 1);
}

unsigned long long combination(unsigned long long n, unsigned long long k){
    return factorial(n) / (factorial(k) * factorial(n - k));}

double bernstein_polynomial(unsigned long long i, unsigned long long n, double t){
    return combination(n, i) * pow(t, i) * pow(1 - t, n - i);}

struct DoubleTuple2 raw_bezier_curve(long double t, unsigned long long size, long long control_points[]){
    double sum_x = 0, sum_y = 0;
    int i = 0;

    while (i < size) {
        sum_x += bernstein_polynomial(i, size, t) * control_points[i];
        sum_y += bernstein_polynomial(i, size, t) * control_points[i + 1];

        i++;
    }

    struct DoubleTuple2 point;
    point.x = sum_x;
    point.y = sum_y;

    return point;
}


static PyObject* BezierCurve_factorial(PyObject *self, PyObject *args){
    unsigned long long n;

    if (!PyArg_ParseTuple(args, "K", &n))
        return NULL;

    return Py_BuildValue("K", factorial(n));
}

static PyObject* BezierCurve_combination(PyObject *self, PyObject *args){
    unsigned long long n, k;

    if (!PyArg_ParseTuple(args, "KK", &n, &k))
        return NULL;

    return Py_BuildValue("K", combination(n, k));
}

static PyObject* BezierCurve_bernstein_polynomial(PyObject* self, PyObject* args){
    unsigned long long i, n;
    long double t;

    if (!PyArg_ParseTuple(args, "KKd", &i, &n, &t))
        return NULL;

    return Py_BuildValue("d", bernstein_polynomial(i, n, t));
}

static PyObject* BezierCurve_raw_bezier_curve(PyObject* self, PyObject* args){
    unsigned long long size;
    double t;
    PyObject *py_control_points, *temp1, *x, *y;

    if (!PyArg_ParseTuple(args, "dO", &t, &py_control_points))
        return NULL;

    size = PyLong_AsUnsignedLongLong(PyLong_FromSsize_t(PyList_GET_SIZE(py_control_points)));

    long long *control_points = (long long*)malloc(size * sizeof(long long) * 2);

    for (unsigned long long i = 0; i < size; i+=2){

        temp1 = PyList_GetItem(py_control_points, i);

        if (temp1 == NULL)
            return NULL;

        x = PyList_GetItem(temp1, 0);
        y = PyList_GetItem(temp1, 1);

        if (PyNumber_Check(x) != 1 || PyNumber_Check(y) != 1){
            PyErr_SetString(PyExc_TypeError, "Control Points Argument is Non-Numeric");
            return NULL;}

        control_points[i] = PyLong_AsLongLong(x);
        control_points[i + 1] = PyLong_AsLongLong(y);

        Py_DECREF(x);
        Py_DECREF(y);
        Py_DECREF(temp1);

        if (PyErr_Occurred())
            return NULL;
    }

    Py_DECREF(py_control_points);

    struct DoubleTuple2 point = raw_bezier_curve(t, size, control_points);
    printf("x: %lf, y: %lf", point.x, point.y);
    return Py_BuildValue("[dd]", point.x, point.y);
}


static PyMethodDef BezierCurve_funcs[] = {
    {"factorial", (PyCFunction)BezierCurve_factorial, METH_VARARGS, "factorial(x): calculates factorial of x"},
    {"combination", (PyCFunction)BezierCurve_combination, METH_VARARGS, "combination(n, k): calculates nCk"},
    {"bernstein_polynomial", (PyCFunction)BezierCurve_bernstein_polynomial, METH_VARARGS,
    "bernstein_polynomial(i, n, t): calculates the ith bernstein_polynomial at t for n-degrees"},

    {"raw_bezier_curve", (PyCFunction)BezierCurve_raw_bezier_curve, METH_VARARGS,
    "raw_bezier_curve(t, control_points): calculates the bezier curve at point t for control_points"},

    {NULL, NULL, 0, NULL}};

static struct PyModuleDef BezierCurveModule = {
    PyModuleDef_HEAD_INIT,
    "BezierCurveModule", "Functions to Calculate Bezier Curves.",
    -1, BezierCurve_funcs};

PyMODINIT_FUNC PyInit_BezierCurve(void){
    return PyModule_Create(&BezierCurveModule);
}