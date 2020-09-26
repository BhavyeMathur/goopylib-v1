
static PyMethodDef Easing_funcs[] = {
    {"factorial", (PyCFunction)BezierCurve_factorial, METH_VARARGS, "factorial(x): calculates factorial of x"},

    {NULL, NULL, 0, NULL}};

static struct PyModuleDef EasingModule = {
    PyModuleDef_HEAD_INIT,
    "EasingModule", "Functions to calculate easing functions for animations.",
    -1, Easing_funcs};

PyMODINIT_FUNC PyInit_Easing(void){
    return PyModule_Create(&EasingModule);
}