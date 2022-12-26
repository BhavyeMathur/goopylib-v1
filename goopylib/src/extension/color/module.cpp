#include "module.h"


static PyMethodDef ColorMethods[] = {

        // RGB to other format functions

        {"rgb_to_hex",  (PyCFunction) color::rgb_to_hex,  METH_VARARGS,
                "rgb_to_hex(int r, int g, int b) -> str '#rrggbb'\nConverts RGB values to a hex string"},

        {"rgb_to_cmyk", (PyCFunction) color::rgb_to_cmyk, METH_VARARGS,
                "rgb_to_cmyk(int r, int g, int b) -> tuple (float c, float m, float y, float k)\nConverts RGB values to CMYK"},

        {"rgb_to_hsl",  (PyCFunction) color::rgb_to_hsl,  METH_VARARGS,
                "rgb_to_hsl(int r, int g, int b) -> tuple (int h, float s, float l)\nConverts RGB values to HSL"},

        {"rgb_to_hsv",  (PyCFunction) color::rgb_to_hsv,  METH_VARARGS,
                "rgb_to_hsv(int r, int g, int b) -> tuple (int h, float s, float v)\nConverts RGB values to HSV"},

        // Hex to other format functions

        {"hex_to_rgb",  (PyCFunction) color::hex_to_rgb,  METH_VARARGS,
                "hex_to_rgb(str hexstring) -> tuple (int r, int g, int b)\nConverts Hex colour values to RGB"},

        {"hex_to_cmyk", (PyCFunction) color::hex_to_cmyk, METH_VARARGS,
                "hex_to_cmyk(str hexstring) -> tuple (float c, float m, float y, float k)\nConverts Hex colour values to CMYK "
                "represented as a tuple"},


        {"hex_to_hsl",  (PyCFunction) color::hex_to_hsl,  METH_VARARGS,
                "hex_to_hsl(str hexstring) -> tuple (int h, float s, float l)\nConverts Hex colour values to HSL"},

        {"hex_to_hsv",  (PyCFunction) color::hex_to_hsv,  METH_VARARGS,
                "hex_to_hsv(str hexstring) -> tuple (int h, float s, float v)\nConverts Hex colour values to HSV"},

        // CMYK to other format functions

        {"cmyk_to_rgb", (PyCFunction) color::cmyk_to_rgb, METH_VARARGS,
                "cmyk_to_rgb(float c, float m, float y, float k) -> tuple (int r, int g, int b)\nConverts CMYK values to RGB"},

        {"cmyk_to_hex", (PyCFunction) color::cmyk_to_hex, METH_VARARGS,
                "cmyk_to_hex(float c, float m, float y, float k) -> str '#rrggbb'\nConverts CMYK values to a hex string"},

        {"cmyk_to_hsl", (PyCFunction) color::cmyk_to_hsl, METH_VARARGS,
                "cmyk_to_hsl(float c, float m, float y, float k) -> tuple (int h, float s, float l)\nConverts CMYK values to HSL"},

        {"cmyk_to_hsv", (PyCFunction) color::cmyk_to_hsv, METH_VARARGS,
                "cmyk_to_hsv(float c, float m, float y, float k) -> tuple (int h, float s, float v)\nConverts CMYK values to HSV"},

        // HSV to other format functions

        {"hsv_to_rgb",  (PyCFunction) color::hsv_to_rgb,  METH_VARARGS,
                "hsv_to_rgb(int h, float s, float v) -> tuple (int r, int g, int b)\nConverts HSV values to RGB"},

        {"hsv_to_hex",  (PyCFunction) color::hsv_to_hex,  METH_VARARGS,
                "hsv_to_hex(int h, float s, float v) -> str '#rrggbb'\nConverts HSV values to a hex string"},

        {"hsv_to_cmyk", (PyCFunction) color::hsv_to_cmyk, METH_VARARGS,
                "hsv_to_cmyk(int h, float s, float v) -> tuple (float c, float m, float y, float k)\nConverts HSV values to CMYK"},

        {"hsv_to_hsl",  (PyCFunction) color::hsv_to_hsl,  METH_VARARGS,
                "hsv_to_hsl(int h, float s, float v) -> tuple (int h, float s, float l)\nConverts HSV values to HSL"},

        // HSL to other format functions

        {"hsl_to_rgb",  (PyCFunction) color::hsl_to_rgb,  METH_VARARGS,
                "hsl_to_rgb(int h, float s, float l) -> tuple (int r, int g, int b)\nConverts HSL values to RGB"},

        {"hsl_to_hex",  (PyCFunction) color::hsl_to_hex,  METH_VARARGS,
                "hsl_to_hex(int h, float s, float l) -> str '#rrggbb'\nConverts HSL values to a hex string"},

        {"hsl_to_cmyk", (PyCFunction) color::hsl_to_cmyk, METH_VARARGS,
                "hsl_to_cmyk(int h, float s, float l) -> tuple (float c, float m, float y, float k)\nConverts HSL values to CMYK"},

        {"hsl_to_hsv",  (PyCFunction) color::hsl_to_hsv,  METH_VARARGS,
                "hsl_to_hsv(int h, float s, float l) -> tuple (int h, float s, float v)\nConverts HSL values to HSV"},

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
