#include "window.h"

// TODO window pointer
// TODO make window key callback compatible with Python lambda functions (raises SIGSEGV error right now)
// TODO window maximize callback does not work
// TODO mouse events
// TODO implement window icons

struct KeyCallback {
    PyObject *callback;
    int keycode;
};

struct WindowObject {
    PyObject_HEAD
    std::unique_ptr<gp::Window> window;

    PyObject *resize_callback;
    PyObject *close_callback;
    PyObject *destroy_callback;
    PyObject *position_callback;
    PyObject *content_scale_callback;
    PyObject *framebuffer_size_callback;
    PyObject *minimize_callback;
    PyObject *maximize_callback;
    PyObject *focus_callback;
    PyObject *refresh_callback;

    PyObject *background;

    std::vector<KeyCallback> key_callbacks;
};

// Window Core
namespace window {
    static int init(WindowObject *self, PyObject *args, PyObject *kwds) {
        GP_PY_WINDOW_INFO("Initializing gp.Window()");

        static const char *kwlist[] = {"width", "height", "title", nullptr};

        PyObject *tmp = nullptr;
        int width, height;
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "II|U", (char **) kwlist, &width, &height, &tmp)) {
            return -1;
        }

        self->background = Color_create(PyTuple_New(0));
        gp::WindowConfig config;

        if (tmp) {
            config = gp::WindowConfig(width, height, PyUnicode_AsUTF8(tmp), 0, 0,
            Color_get_pointer(self->background));
        }
        else {
            config = gp::WindowConfig(width, height, "goopylib Window", 0, 0,
            Color_get_pointer(self->background));
        }
        self->window = gp::make_unique<gp::Window>(config);

        GP_PY_WINDOW_TRACE("Initialized gp.Window()");

        return 0;
    }

    static PyObject *repr(WindowObject *self) {
        if (self->window->isDestroyed()) {
            return PyUnicode_FromString("Destroyed Window()");
        }
        else {
            return PyUnicode_FromFormat("Window(width=%i, height=%i, title='%s')",
                                        self->window->getWidth(), self->window->getHeight(), self->window->getTitle());
        }
    }

    static int traverse(WindowObject *self, visitproc visit, void *arg) {
        Py_VISIT(self->resize_callback);
        Py_VISIT(self->close_callback);
        Py_VISIT(self->destroy_callback);
        Py_VISIT(self->position_callback);
        Py_VISIT(self->content_scale_callback);
        Py_VISIT(self->framebuffer_size_callback);
        Py_VISIT(self->minimize_callback);
        Py_VISIT(self->maximize_callback);
        Py_VISIT(self->focus_callback);
        Py_VISIT(self->refresh_callback);

        Py_VISIT(self->background);

        for (auto key: self->key_callbacks) {
            Py_VISIT(key.callback);
        }

        return 0;
    }

    static int clear(WindowObject *self) {
        GP_PY_WINDOW_TRACE("Clearing gp.Window()");

        self->window.reset();

        Py_CLEAR(self->resize_callback);
        Py_CLEAR(self->close_callback);
        Py_CLEAR(self->position_callback);
        Py_CLEAR(self->destroy_callback);
        Py_CLEAR(self->content_scale_callback);
        Py_CLEAR(self->framebuffer_size_callback);
        Py_CLEAR(self->minimize_callback);
        Py_CLEAR(self->maximize_callback);
        Py_CLEAR(self->focus_callback);
        Py_CLEAR(self->refresh_callback);

        Py_CLEAR(self->background);

        for (auto key: self->key_callbacks) {
            Py_CLEAR(key.callback);
        }

        return 0;
    }

    static void dealloc(WindowObject *self) {
        GP_PY_WINDOW_INFO("Deallocating gp.Window()");

        self->window.reset();

        Py_XDECREF(self->resize_callback);
        Py_XDECREF(self->close_callback);
        Py_XDECREF(self->position_callback);
        Py_XDECREF(self->destroy_callback);
        Py_XDECREF(self->content_scale_callback);
        Py_XDECREF(self->framebuffer_size_callback);
        Py_XDECREF(self->minimize_callback);
        Py_XDECREF(self->maximize_callback);
        Py_XDECREF(self->focus_callback);
        Py_XDECREF(self->refresh_callback);

        Py_XDECREF(self->background);

        for (auto key: self->key_callbacks) {
            Py_XDECREF(key.callback);
        }

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);

        GP_CORE_INFO("Deallocated gp.Window()");
    }
}

// Window Methods
namespace window {
    static PyObject *is_open(WindowObject *self, PyObject *Py_UNUSED(args)) {
        if (self->window->isClosed()) {
            Py_RETURN_FALSE;
        }
        Py_RETURN_TRUE;
    }

    static PyObject *is_closed(WindowObject *self, PyObject *Py_UNUSED(args)) {
        if (self->window->isClosed()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *update(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->update();
        Py_RETURN_NONE;
    }

    static PyObject *destroy(WindowObject *self, PyObject *Py_UNUSED(args)) {
        self->window->destroy();
        Py_RETURN_NONE;
    }
}

// Window States
namespace window {
    static PyObject *restore(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->restore();
        Py_RETURN_NONE;
    }

    static PyObject *is_fullscreen(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isFullscreen()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *fullscreen(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->fullscreen();
        Py_RETURN_NONE;
    }

    static PyObject *is_maximized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isMaximized()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *maximize(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->maximize();
        Py_RETURN_NONE;
    }

    static PyObject *is_minimized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isMinimized()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *minimize(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->minimize();
        Py_RETURN_NONE;
    }

    static PyObject *is_visible(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isVisible()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *show(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->show();
        Py_RETURN_NONE;
    }

    static PyObject *hide(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->hide();
        Py_RETURN_NONE;
    }

    static PyObject *set_focus(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->focus();
        Py_RETURN_NONE;
    }

    static PyObject *has_focus(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->hasFocus()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *request_attention(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->requestAttention();
        Py_RETURN_NONE;
    }
}

// Window Getter & Setters
namespace window {
    // Resizable
    static int set_resizable(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setResizable(value == Py_True);
        return 0;
    }

    static PyObject *is_resizable(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isResizable()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    // Decorated
    static int set_decorated(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setDecorated(value == Py_True);
        return 0;
    }

    static PyObject *is_decorated(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isDecorated()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    // Floating
    static int set_floating(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setFloating(value == Py_True);
        return 0;
    }

    static PyObject *is_floating(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isFloating()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    // Auto Minimized
    static int set_auto_minimized(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setAutoMinimized(value == Py_True);
        return 0;
    }

    static PyObject *is_auto_minimized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isAutoMinimized()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }


    // Focused on Show
    static int set_focused_on_show(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setFocusedOnShow(value == Py_True);
        return 0;
    }

    static PyObject *is_focused_on_show(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isFocusedOnShow()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    // -------------------------------------------------------------------------------------------------------------

    // Width
    static PyObject *get_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getWidth());
    }

    static int set_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        int width = (int) PyLong_AsLong(value);

        #if GP_ERROR_CHECKING
        if (width <= 0) {
            RAISE_VALUE_ERROR(-1, "width must be greater than 0")
        }
        #endif

        self->window->setWidth(width);
        return 0;
    }

    // Height
    static PyObject *get_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getHeight());
    }

    static int set_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        int height = (int) PyLong_AsLong(value);

        #if GP_ERROR_CHECKING
        if (height <= 0) {
            RAISE_VALUE_ERROR(-1, "height must be greater than 0")
        }
        #endif

        self->window->setHeight(height);
        return 0;
    }

    // Title
    static int set_title(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyUnicode_Check(value)) {
            RAISE_TYPE_ERROR(-1, "string argument expected, got %S", PyObject_Type(value))
        }
        #endif

        self->window->setTitle(PyUnicode_AsUTF8(value));
        return 0;
    }

    static PyObject *get_title(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyUnicode_FromString(self->window->getTitle());
    }

    // X Position
    static int set_x_position(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }

        self->window->setXPos((int) PyLong_AsLong(value));
        return 0;
    }

    static PyObject *get_x_position(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyLong_FromLong(self->window->getXPos());
    }

    // Y Position
    static int set_y_position(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }

        self->window->setYPos((int) PyLong_AsLong(value));
        return 0;
    }

    static PyObject *get_y_position(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyLong_FromLong(self->window->getYPos());
    }

    // Background
    static int set_background(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (Color_isinstance(value)) {
            SET_PYOBJECT_ATTRIBUTE(self->background, value)
        }
        else {
            PyObject *tmp = self->background;
            self->background = Color_create(value);
            Py_XDECREF(tmp);

            if (self->background == nullptr) {
                RAISE_TYPE_ERROR(-1, "color", value)
            }
        }

        self->window->setBackground(Color_get_pointer(self->background));

        return 0;
    }

    static PyObject *get_background(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        RETURN_PYOBJECT(self->background)
    }

    // Minimum Width
    static PyObject *get_min_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getMinimumWidth());
    }

    static int set_min_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (PyLong_Check(value)) {
            int minWidth = (int) PyLong_AsLong(value);

            #if GP_ERROR_CHECKING
            if (minWidth < 0) {
                RAISE_VALUE_ERROR(-1, "minimum width must be greater than or equal to 0")
            }
            #endif

            self->window->setMinimumWidth(minWidth);
        }
        else if (value == Py_None) {
            self->window->setMinimumWidth(0);
        }
        else {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        return 0;
    }

    // Minimum Height
    static PyObject *get_min_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getMinimumHeight());
    }

    static int set_min_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (PyLong_Check(value)) {
            int minHeight = (int) PyLong_AsLong(value);
            #if GP_ERROR_CHECKING
            if (minHeight < 0) {
                RAISE_VALUE_ERROR(-1, "minimum height must be greater than or equal to 0")
            }
            #endif

            self->window->setMinimumHeight(minHeight);
        }
        else if (value == Py_None) {
            self->window->setMinimumHeight(0);
        }
        else {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        return 0;
    }

    // Maximum Width
    static PyObject *get_max_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getMaximumWidth());
    }

    static int set_max_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (PyLong_Check(value)) {
            int maxWidth = (int) PyLong_AsLong(value);

            #if GP_ERROR_CHECKING
            // The greater than 0 case must be checked because the minimum width for no value is -1
            // thus an input of 0 would pass the next test if min_width was never set
            if (maxWidth < 0) {
                RAISE_VALUE_ERROR(-1, "maximum width must be greater than or equal to 0")
            }
            if (maxWidth < self->window->getMinimumWidth()) {
                RAISE_VALUE_ERROR(-1, "maximum width must be greater than or equal to minimum width")
            }
            #endif

            self->window->setMaximumWidth(maxWidth);
        }
        else if (value == Py_None) {
            self->window->setMaximumWidth(MAX_WIDTH);
        }
        else {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        return 0;
    }

    // Maximum Height
    static PyObject *get_max_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getMaximumHeight());
    }

    static int set_max_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (PyLong_Check(value)) {
            int maxHeight = (int) PyLong_AsLong(value);

            #if GP_ERROR_CHECKING
            // the greater than 0 case must be checked because the minimum height for no value is -1
            // thus an input of 0 would pass the next test if min_height was never set
            if (maxHeight < 0) {
                RAISE_VALUE_ERROR(-1, "maximum height must be greater than or equal to 0")
            }
            if (maxHeight < self->window->getMinimumHeight()) {
                RAISE_VALUE_ERROR(-1, "maximum height must be greater than or equal to minimum height")
            }
            #endif

            self->window->setMaximumHeight(maxHeight);
        }
        else if (value == Py_None) {
            self->window->setMaximumHeight(MAX_HEIGHT);
        }
        else {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        return 0;
    }
}

// Window Get & Set functions
namespace window {
    // Size
    static PyObject *set_size(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        int width, height;
        if (!PyArg_ParseTuple(args, "ii", &width, &height)) {
            return nullptr;
        }

        #if GP_ERROR_CHECKING
        if (width <= 0) {
            RAISE_VALUE_ERROR(nullptr, "width must be greater than 0")
        }
        if (height <= 0) {
            RAISE_VALUE_ERROR(nullptr, "height must be greater than 0")
        }
        #endif

        self->window->setSize(width, height);
        Py_RETURN_NONE;
    }

    static PyObject *get_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getWidth()), PyLong_FromLong(self->window->getHeight()));
    }

    // Position
    static PyObject *set_position(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        int x_position, y_position;
        if (!PyArg_ParseTuple(args, "ii", &x_position, &y_position)) {
            return nullptr;
        }

        self->window->setPosition(x_position, y_position);
        Py_RETURN_NONE;
    }

    static PyObject *get_position(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getXPos()), PyLong_FromLong(self->window->getYPos()));
    }

    // Size Limits
    static PyObject *set_size_limits(WindowObject *self, PyObject *args, PyObject *kwds) {
        CHECK_WINDOW_ACTIVE(nullptr)

        static const char *kwlist[] = {"min_width", "min_height", "max_width", "max_height", nullptr};

        PyObject *min_width, *min_height, *max_width, *max_height;
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "OOOO", (char **) kwlist, &min_width, &min_height, &max_width,
                                         &max_height)) {
            return nullptr;
        }

        int tmp_min_width, tmp_min_height, tmp_max_width, tmp_max_height;
        if (PyLong_Check(min_width)) {
            tmp_min_width = (int) PyLong_AsLong(min_width);
        }
        else if (min_width == Py_None) {
            tmp_min_width = 0;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", min_width)
        }

        if (PyLong_Check(max_width)) {
            tmp_max_width = (int) PyLong_AsLong(max_width);
        }
        else if (max_width == Py_None) {
            tmp_max_width = MAX_WIDTH;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", max_width)
        }

        if (PyLong_Check(min_height)) {
            tmp_min_height = (int) PyLong_AsLong(min_height);
        }
        else if (min_height == Py_None) {
            tmp_min_height = 0;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", min_height)
        }

        if (PyLong_Check(max_height)) {
            tmp_max_height = (int) PyLong_AsLong(max_height);
        }
        else if (max_height == Py_None) {
            tmp_max_height = MAX_HEIGHT;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", max_height)
        }

        #if GP_ERROR_CHECKING
        if (tmp_min_width < 0) {
            RAISE_VALUE_ERROR(nullptr, "minimum width must be greater than or equal to 0")
        }
        if (tmp_max_width < 0) {
            RAISE_VALUE_ERROR(nullptr, "maximum width must be greater than or equal to 0")
        }
        if (tmp_max_width < tmp_min_width) {
            RAISE_VALUE_ERROR(nullptr, "maximum width must be greater than or equal to minimum width")
        }

        if (tmp_min_height < 0) {
            RAISE_VALUE_ERROR(nullptr, "minimum height must be greater than or equal to 0")
        }
        if (tmp_max_height < 0) {
            RAISE_VALUE_ERROR(nullptr, "maximum height must be greater than or equal to 0")
        }
        if (tmp_max_height < tmp_min_height) {
            RAISE_VALUE_ERROR(nullptr, "maximum height must be greater than or equal to minimum height")
        }
        #endif

        self->window->setSizeLimits(tmp_min_width, tmp_min_height,
                                    tmp_max_width, tmp_max_height);
        Py_RETURN_NONE;
    }

    // Minimum Size
    static PyObject *set_minimum_size(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        PyObject *min_width, *min_height;
        if (!PyArg_ParseTuple(args, "OO", &min_width, &min_height)) {
            return nullptr;
        }

        int tmp_width, tmp_height;

        if (PyLong_Check(min_width)) {
            tmp_width = (int) PyLong_AsLong(min_width);
        }
        else if (min_width == Py_None) {
            tmp_width = 0;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", min_width)
        }

        if (PyLong_Check(min_height)) {
            tmp_height = (int) PyLong_AsLong(min_height);
        }
        else if (min_height == Py_None) {
            tmp_height = 0;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", min_height)
        }

        #if GP_ERROR_CHECKING
        if (tmp_width < 0) {
            RAISE_VALUE_ERROR(nullptr, "minimum width must be greater than or equal to 0")
        }
        if (tmp_height < 0) {
            RAISE_VALUE_ERROR(nullptr, "minimum height must be greater than or equal to 0")
        }
        #endif

        self->window->setMinimumSize(tmp_width, tmp_height);
        Py_RETURN_NONE;
    }

    static PyObject *get_minimum_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getMinimumWidth()),
                            PyLong_FromLong(self->window->getMinimumHeight()));
    }

    // Maximum Size
    static PyObject *set_maximum_size(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        PyObject *max_width, *max_height;
        if (!PyArg_ParseTuple(args, "OO", &max_width, &max_height)) {
            return nullptr;
        }

        int tmp_width, tmp_height;

        if (PyLong_Check(max_width)) {
            tmp_width = (int) PyLong_AsLong(max_width);
        }
        else if (max_width == Py_None) {
            tmp_width = MAX_WIDTH;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", max_width)
        }

        if (PyLong_Check(max_height)) {
            tmp_height = (int) PyLong_AsLong(max_height);
        }
        else if (max_height == Py_None) {
            tmp_height = MAX_HEIGHT;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", max_height)
        }

        #if GP_ERROR_CHECKING
        if (tmp_width < 0) {
            RAISE_VALUE_ERROR(nullptr, "maximum width must be greater than or equal to 0")
        }
        if (tmp_width < self->window->getMinimumWidth()) {
            RAISE_VALUE_ERROR(nullptr, "maximum width must be greater than or equal to minimum width")
        }

        if (tmp_height < 0) {
            RAISE_VALUE_ERROR(nullptr, "maximum height must be greater than or equal to 0")
        }
        if (tmp_height < self->window->getMinimumHeight()) {
            RAISE_VALUE_ERROR(nullptr, "maximum height must be greater than or equal to minimum height")
        }
        #endif

        self->window->setMaximumSize(tmp_width, tmp_height);
        Py_RETURN_NONE;
    }

    static PyObject *get_maximum_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getMaximumWidth()),
                            PyLong_FromLong(self->window->getMaximumHeight()));
    }

    // Aspect Ratio
    static PyObject *set_aspect_ratio(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        PyObject *tmp_numerator, *tmp_denominator;
        if (!PyArg_ParseTuple(args, "OO", &tmp_numerator, &tmp_denominator)) {
            return nullptr;
        }

        if (tmp_numerator == Py_None and tmp_denominator == Py_None) {
            self->window->setAspectRatio(-1, -1);
            Py_RETURN_NONE;
        }

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(tmp_numerator)) {
            RAISE_TYPE_ERROR(nullptr, "integer", tmp_numerator)
        }
        if (!PyLong_Check(tmp_denominator)) {
            RAISE_TYPE_ERROR(nullptr, "integer", tmp_denominator)
        }
        #endif

        int numerator = (int) PyLong_AsLong(tmp_numerator);
        int denominator = (int) PyLong_AsLong(tmp_denominator);

        #if GP_ERROR_CHECKING
        if (numerator <= 0) {
            RAISE_VALUE_ERROR(nullptr, "aspect ratio numerator must be greater than 0")
        }
        if (denominator <= 0) {
            RAISE_VALUE_ERROR(nullptr, "aspect ratio denominator must be greater than 0")
        }
        #endif

        self->window->setAspectRatio(numerator, denominator);
        Py_RETURN_NONE;
    }

    static PyObject *get_aspect_ratio(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        gp::AspectRatio value = self->window->getAspectRatio();
        return PyTuple_Pack(2, PyLong_FromLong(value.numerator), PyLong_FromLong(value.denominator));
    }

    // Frame size & Content Scale
    static PyObject *get_frame_size(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        gp::WindowFrame value = self->window->getFrameSize();
        return Py_BuildValue("iiii", value.left, value.top, value.right, value.bottom);
    }

    static PyObject *get_content_scale(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        gp::ContentScale value = self->window->getContentScale();
        return PyTuple_Pack(2, PyFloat_FromDouble(value.xScale), PyFloat_FromDouble(value.yScale));
    }

    // Framebuffer Size
    static PyObject *get_framebuffer_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        gp::FramebufferSize value = self->window->getFramebufferSize();
        return PyTuple_Pack(2, PyLong_FromLong(value.width), PyLong_FromLong(value.height));
    }
}

// Window Input Events
namespace window {
    static PyObject *is_mouse_hovering(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isMouseHovering()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_shift_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->checkShiftKey()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_control_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->checkControlKey()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_alt_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->checkAltKey()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_super_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->checkSuperKey()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_key(WindowObject *self, PyObject *arg) {
        CHECK_WINDOW_ACTIVE(nullptr)

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "key", arg)
        }
        #endif

        return PyLong_FromLong(self->window->checkKey((int) PyLong_AsLong(arg)));
    }

    static PyObject *set_key_callback(WindowObject *self, PyObject *args, PyObject *kwds) {
        CHECK_WINDOW_ACTIVE(nullptr)

        static const char *kwlist[] = {"key", "callback", nullptr};

        PyObject *callback;
        int key;
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "iO", (char **) kwlist, &key, &callback)) {
            return nullptr;
        }

        #if GP_ERROR_CHECKING
        glfwGetKeyScancode(key);
        if (glfwGetError(nullptr) == GLFW_INVALID_ENUM) {
            RAISE_VALUE_ERROR(nullptr, "invalid key received")
        }
        #endif

        if (callback == Py_None) {
            int i = 0;
            for (KeyCallback key_callback: self->key_callbacks) {
                if (key_callback.keycode == key) {
                    Py_DECREF(self->key_callbacks[i].callback);
                    self->key_callbacks.erase(self->key_callbacks.begin() + i);
                    break;
                }
                i++;
            }
            self->window->setKeyCallback(key, nullptr);
        }
        else if (PyCallable_Check(callback)) {
            #if GP_ERROR_CHECKING
            if (PyFunction_Check(callback) and
                PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(callback), "co_argcount")) != 1) {
                RAISE_VALUE_ERROR(nullptr, "callback must take 1 argument: action")
            }
            #endif

            for (KeyCallback key_callback: self->key_callbacks) {
                if (key_callback.keycode == key) {
                    SET_PYOBJECT_ATTRIBUTE(key_callback.callback, callback)
                    goto callback_set;
                }
            }

            {
                KeyCallback new_callback = {callback, key};
                self->key_callbacks.push_back(new_callback);
            }

            callback_set:

            Py_INCREF(callback);
            self->window->setKeyCallback(key, [callback](gp::Window *window, int action) {
                PyGILState_STATE gstate = PyGILState_Ensure();
                PyObject_CallOneArg(callback, PyLong_FromLong(action));
                PyGILState_Release(gstate);
            });
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "callable", callback)
        }
        Py_RETURN_NONE;
    }
}

// Window Callbacks
namespace window {

    // Resize
    static int set_resize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 2) {
            RAISE_VALUE_ERROR(-1, "callback must take 2 arguments: width, height")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->resize_callback, value)

        self->window->setResizeCallback([self](gp::Window *window, int width, int height) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->resize_callback, "ii", width, height);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_resize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->resize_callback)
    }

    // Close
    static int set_close_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 0) {
            RAISE_VALUE_ERROR(-1, "callback must not take arguments")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->close_callback, value)
        self->window->setCloseCallback([self](gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->close_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_close_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->close_callback)
    }

    // Destroy
    static int set_destroy_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 0) {
            RAISE_VALUE_ERROR(-1, "callback must not take arguments")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->destroy_callback, value)
        self->window->setDestroyCallback([self](gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->destroy_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_destroy_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->destroy_callback)
    }

    // Position
    static int set_position_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 2) {
            RAISE_VALUE_ERROR(-1, "callback must take 2 arguments: xpos, ypos")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->position_callback, value)
        self->window->setPositionCallback([self](gp::Window *window, int xPos, int yPos) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->position_callback, "ii", xPos, yPos);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_position_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->position_callback)
    }

    // Minimize
    static int set_minimize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 1) {
            RAISE_VALUE_ERROR(-1, "callback must take 1 argument: minimized")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->minimize_callback, value)
        self->window->setMinimizeCallback([self](gp::Window *window, bool minimized) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->minimize_callback, "O", minimized ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_minimize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->minimize_callback)
    }

    // Maximize
    static int set_maximize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 1) {
            RAISE_VALUE_ERROR(-1, "callback must take 1 argument: maximized")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->maximize_callback, value)
        self->window->setMaximizeCallback([self](gp::Window *window, bool maximized) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->maximize_callback, "O", maximized ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_maximize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->maximize_callback)
    }

    // Focus
    static int set_focus_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 1) {
            RAISE_VALUE_ERROR(-1, "callback must take 1 argument: focused")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->focus_callback, value)
        self->window->setFocusCallback([self](gp::Window *window, bool focused) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->focus_callback, "O", focused ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_focus_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->focus_callback)
    }

    // Refresh
    static int set_refresh_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 0) {
            RAISE_VALUE_ERROR(-1, "callback must not take arguments")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->refresh_callback, value)
        self->window->setRefreshCallback([self](gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->refresh_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_refresh_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->refresh_callback)
    }

    // Content Scale
    static int set_content_scale_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 2) {
            RAISE_VALUE_ERROR(-1, "callback must take 2 arguments: xscale, yscale")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->content_scale_callback, value)
        self->window->setContentScaleCallback([self](gp::Window *window, float xScale, float yScale) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->content_scale_callback, "ff", xScale, yScale);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_content_scale_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->content_scale_callback)
    }

    // Framebuffer Size
    static int set_framebuffer_size_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and
            PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 2) {
            RAISE_VALUE_ERROR(-1, "callback must take 2 arguments: width, height")
        }
                #endif

        SET_PYOBJECT_ATTRIBUTE(self->framebuffer_size_callback, value)
        self->window->setFramebufferSizeCallback([self](gp::Window *window, int width, int height) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->framebuffer_size_callback, "ii", width, height);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_framebuffer_size_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->framebuffer_size_callback)
    }
}

// Window Type
namespace window {
    static PyMethodDef methods[] = {

            // Core Window Methods

            {"update",               (PyCFunction) update,               METH_NOARGS,
                    "Update the Window"},
            {"destroy",              (PyCFunction) destroy,              METH_NOARGS,
                    "Destroys the Window"},

            {"is_open",              (PyCFunction) is_open,              METH_NOARGS,
                    "Returns whether the Window is open"},
            {"is_closed",            (PyCFunction) is_closed,            METH_NOARGS,
                    "Returns whether the Window is closed"},

            // Window State Methods

            {"restore",              (PyCFunction) restore,              METH_NOARGS,
                    "Restores the Window"},
            {"fullscreen",           (PyCFunction) fullscreen,           METH_NOARGS,
                    "Makes the Window fullscreen"},
            {"is_fullscreen",        (PyCFunction) is_fullscreen,        METH_NOARGS,
                    "Returns if the Window is fullscreen"},
            {"maximize",             (PyCFunction) maximize,             METH_NOARGS,
                    "Maximizes the Window"},
            {"is_maximized",         (PyCFunction) is_maximized,         METH_NOARGS,
                    "Returns if the Window is maximized"},
            {"minimize",             (PyCFunction) minimize,             METH_NOARGS,
                    "Minimizes the Window"},
            {"is_minimized",         (PyCFunction) is_minimized,         METH_NOARGS,
                    "Returns if the Window is minimized"},

            {"show",                 (PyCFunction) show,                 METH_NOARGS,
                    "Makes the Window visible"},
            {"hide",                 (PyCFunction) hide,                 METH_NOARGS,
                    "Makes the Window invisible"},
            {"is_visible",           (PyCFunction) is_visible,           METH_NOARGS,
                    "Returns if the Window is visible"},

            {"set_focus",            (PyCFunction) set_focus,            METH_NOARGS,
                    "Sets the input focus to the Window"},
            {"has_focus",            (PyCFunction) has_focus,            METH_NOARGS,
                    "Returns whether the Window has input focus"},
            {"request_attention",    (PyCFunction) request_attention,    METH_NOARGS,
                    "Requests for user attention on the window"},

            // Window Get & Set Methods

            {"set_size_limits",      (PyCFunction) set_size_limits,      METH_VARARGS | METH_KEYWORDS,
                    "Sets the minimum and maximum size for the window"},
            {"set_minimum_size",     (PyCFunction) set_minimum_size,     METH_VARARGS,
                    "Sets the minimum size for the window"},
            {"set_maximum_size",     (PyCFunction) set_maximum_size,     METH_VARARGS,
                    "Sets the maximum size for the window"},
            {"get_minimum_size",     (PyCFunction) get_minimum_size,     METH_NOARGS,
                    "Returns a tuple (width, height) containing the minimum size for the window"},
            {"get_maximum_size",     (PyCFunction) get_maximum_size,     METH_NOARGS,
                    "Returns a tuple (width, height) containing the maximum size for the window"},

            {"get_size",             (PyCFunction) get_size,             METH_NOARGS,
                    "Returns the Window's width and height as a tuple"},
            {"set_size",             (PyCFunction) set_size,             METH_VARARGS,
                    "Sets the Window's width and height"},
            {"get_position",         (PyCFunction) get_position,         METH_NOARGS,
                    "Returns the Window's x and y position as a tuple"},
            {"set_position",         (PyCFunction) set_position,         METH_VARARGS,
                    "Sets the Window's x and y position"},

            {"set_aspect_ratio",     (PyCFunction) set_aspect_ratio,     METH_VARARGS,
                    "Sets the aspect ratio of the window"},
            {"get_aspect_ratio",     (PyCFunction) get_aspect_ratio,     METH_NOARGS,
                    "Returns a tuple (numerator, denominator) containing the aspect ratio of the window"},

            {"get_frame_size",       (PyCFunction) get_frame_size,       METH_NOARGS,
                    "Returns a tuple (left, top, right, bottom) containing the frame size of the window"},
            {"get_content_scale",    (PyCFunction) get_content_scale,    METH_NOARGS,
                    "Returns a tuple (xscale, yscale) containing the scale of the content on the window"},
            {"get_framebuffer_size", (PyCFunction) get_framebuffer_size, METH_NOARGS,
                    "Returns a tuple (width, height) containing the size of the Window's framebuffer"},

            // Window Input Events

            {"is_mouse_hovering",    (PyCFunction) is_mouse_hovering,    METH_NOARGS,
                    "Returns whether the mouse is hovering over the Window"},
            {"check_shift_key",      (PyCFunction) check_shift_key,      METH_NOARGS,
                    "Returns whether the shift key is being pressed"},
            {"check_alt_key",        (PyCFunction) check_alt_key,        METH_NOARGS,
                    "Returns whether the alt key is being pressed"},
            {"check_control_key",    (PyCFunction) check_control_key,    METH_NOARGS,
                    "Returns whether the control key is being pressed"},
            {"check_super_key",      (PyCFunction) check_super_key,      METH_NOARGS,
                    "Returns whether the fromRGB key is being pressed"},

            {"check_key",            (PyCFunction) check_key,            METH_O,
                    "Returns whether the key specified is being pressed"},
            {"set_key_callback",     (PyCFunction) set_key_callback,     METH_VARARGS | METH_KEYWORDS,
                    "Sets a callback function for a keyboard event"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {"width",                     (getter) get_width,                     (setter) set_width,                     "width",                     nullptr},
            {"height",                    (getter) get_height,                    (setter) set_height,                    "height",                    nullptr},
            {"title",                     (getter) get_title,                     (setter) set_title,                     "title",                     nullptr},

            {"x_position",                (getter) get_x_position,                (setter) set_x_position,                "x position",                nullptr},
            {"y_position",                (getter) get_y_position,                (setter) set_y_position,                "y position",                nullptr},

            {"background",                (getter) window::get_background,        (setter) window::set_background,        "background",                nullptr},

            {"min_width",                 (getter) get_min_width,                 (setter) set_min_width,                 "minimum width",             nullptr},
            {"max_width",                 (getter) get_max_width,                 (setter) set_max_width,                 "maximum width",             nullptr},
            {"min_height",                (getter) get_min_height,                (setter) set_min_height,                "minimum height",            nullptr},
            {"max_height",                (getter) get_max_height,                (setter) set_max_height,                "maximum height",            nullptr},

            {"resizable",                 (getter) is_resizable,                  (setter) set_resizable,                 "resizable",                 nullptr},
            {"decorated",                 (getter) is_decorated,                  (setter) set_decorated,                 "decorated",                 nullptr},
            {"auto_minimized",            (getter) is_auto_minimized,             (setter) set_auto_minimized,            "auto minimized",            nullptr},
            {"floating",                  (getter) is_floating,                   (setter) set_floating,                  "floating",                  nullptr},
            {"focused_on_show",           (getter) is_focused_on_show,            (setter) set_focused_on_show,           "focused on show",           nullptr},

            {"resize_callback",           (getter) get_resize_callback,           (setter) set_resize_callback,           "resize callback",           nullptr},
            {"position_callback",         (getter) get_position_callback,         (setter) set_position_callback,         "position callback",         nullptr},
            {"framebuffer_size_callback", (getter) get_framebuffer_size_callback, (setter) set_framebuffer_size_callback, "framebuffer size callback", nullptr},
            {"close_callback",            (getter) get_close_callback,            (setter) set_close_callback,            "close callback",            nullptr},
            {"content_scale_callback",    (getter) get_content_scale_callback,    (setter) set_content_scale_callback,    "content scale callback",    nullptr},
            {"destroy_callback",          (getter) get_destroy_callback,          (setter) set_destroy_callback,          "destroy callback",          nullptr},
            {"minimize_callback",         (getter) get_minimize_callback,         (setter) set_minimize_callback,         "minimize callback",         nullptr},
            {"maximize_callback",         (getter) get_maximize_callback,         (setter) set_maximize_callback,         "maximize callback",         nullptr},
            {"focus_callback",            (getter) get_focus_callback,            (setter) set_focus_callback,            "focus callback",            nullptr},
            {"refresh_callback",          (getter) get_refresh_callback,          (setter) set_refresh_callback,          "refresh callback",          nullptr},

            {nullptr}
    };
}

PyTypeObject WindowType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Window",
        .tp_basicsize = sizeof(WindowObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

        .tp_new = PyType_GenericNew,
        .tp_init = (initproc) window::init,

        .tp_methods = window::methods,
        .tp_getset = window::getsetters,

        .tp_traverse = (traverseproc) window::traverse,
        .tp_clear = (inquiry) window::clear,
        .tp_dealloc = (destructor) window::dealloc,

        .tp_repr = (reprfunc) window::repr,
};

namespace window {
    bool isinstance(PyObject *object) {
        return PyObject_IsInstance(object, (PyObject *) &WindowType);
    }
}

static struct PyModuleDef windowmodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "core",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_window(void) {
    #if GP_LOGGING
    std::cout << "Initializing window logger" << std::endl;
    #endif
    gp::initialize();

    GP_PY_TRACE("Initializing window module");

    PyObject *m = PyModule_Create(&windowmodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_CLASS(WindowType, "Window")

    if (import_color() < 0) {
        return nullptr;
    }

    return m;
}
