# Defining a New Class

---
### 1. Create the Core Class Components

In `module.cpp` start by defining a typedef for the class that contains all the class attributes.

```c++
typedef struct {
    PyObject_HEAD
    // Type-specific fields go here
} CustomObject;
```

Create the new and initialization functions.

```c++
static PyObject * Custom_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    CustomObject *self;
    self = (CustomObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        // initialize attributes to defaults
    }
    return (PyObject *) self;
}
```

```c++
static int Custom_init(CustomObject *self, PyObject *args, PyObject *kwds) {}
```

Use a representation method to convert the class to a printable string.

```c++
static PyObject *Custom_repr(CustomObject *self) {}
```

Finally, define the class type.

```c++
static PyTypeObject CustomType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "custom.Custom",
    .tp_doc = PyDoc_STR("Custom objects"),
    .tp_basicsize = sizeof(CustomObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = Custom_new,
    .tp_init = (initproc) Custom_init,
    .tp_dealloc = (destructor) Custom_dealloc,
    .tp_members = Custom_members,
    .tp_methods = Custom_methods,
    .tp_getset = Custom_getsetters,
    .tp_traverse = (traverseproc) Custom_traverse,
    .tp_clear = (inquiry) Custom_clear,
    .tp_repr = (reprfunc) Custom_repr,
};
```

---
### 2. Cyclic Garbage Collection

Make the class compatible with Python's garbage collector.

```c++
static int Custom_traverse(CustomObject *self, visitproc visit, void *arg) {}
```

```c++
static int Custom_clear(CustomObject *self) {}
```

```c++
static void Custom_dealloc(CustomObject *self) {
    PyObject_GC_UnTrack(self);
    Custom_clear(self);
    Py_TYPE(self)->tp_free((PyObject *) self);
}
```

---
### 3. Class Attributes & Methods

Define the class's attributes as a null-terminated array.

```c++
static PyMemberDef Custom_members[] = {
        {nullptr}
};
```

And next, its methods.

```c++
static PyMethodDef Custom_methods[] = {
        {nullptr}
};
```

Finally, its getters & setters.

```c++
static PyGetSetDef Custom_getsetters[] = {
        {nullptr}
};
```

---
### 4. Final Class Set-up

Finally, expose the class to the user from C++.

```c++
if (PyType_Ready(&CustomType) < 0) {
    return nullptr;
}
Py_INCREF(&CustomType);
if (PyModule_AddObject(m, "Custom", (PyObject *) &CustomType) < 0) {
    Py_DECREF(&CustomType);
    Py_DECREF(m);
    return nullptr;
}
```

Create and document the class in `module.py`.

```python
class Custom:
    def __init__(self):
        ...
```

Write unit tests to test its functionality.