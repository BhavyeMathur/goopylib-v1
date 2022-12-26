#include "module.h"


static PyMethodDef ColorMethods[] = {
        {"random_rgb", (PyCFunction) color::random_rgb, METH_NOARGS, "Returns a random RGB color"},
        {"random_hex", (PyCFunction) color::random_hex, METH_NOARGS, "Returns a random Hex color"},
        {"random_cmyk", (PyCFunction) color::random_cmyk, METH_NOARGS, "Returns a random CMYK color"},
        {"random_hsv", (PyCFunction) color::random_hsv, METH_NOARGS, "Returns a random HSV color"},
        {"random_hsl", (PyCFunction) color::random_hsl, METH_NOARGS, "Returns a random HSL color"},

        {nullptr, nullptr, 0, nullptr}

};

static struct PyModuleDef colormodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "color",
        .m_size = -1,
        .m_methods = ColorMethods,
};


PyMODINIT_FUNC PyInit_color() {
    #if GP_LOGGING_LEVEL
    std::cout << "Initializing color logger" << std::endl;
    gp::Log::init();
    #endif

    GP_PY_TRACE("Initializing color module");

    PyObject *m;
    m = PyModule_Create(&colormodule);
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
    PyObject *c_api_object;

    PyColor_API[Color_create_NUM] = (void *)Color_create;
    PyColor_API[Color_isinstance_NUM] = (void *) Color_isinstance;
    PyColor_API[Color_get_pointer_NUM] = (void *) Color_get_pointer;
    c_api_object = PyCapsule_New((void *)PyColor_API, "ext.color._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
