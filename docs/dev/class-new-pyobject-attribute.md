# Adding a new PyObject class attribute

---
### 1. Add the new attribute in C++

Begin by adding the attribute to structure of the custom class.
```c++
PyObject *attribute;
```

Then, add the attribute to the class deallocation function:
```c++
Py_XDECREF(self->attribute);
```

Either initialise the object as `Py_NONE` or use the following template in the class new function:
```c++
self->attribute = ...;
if (self->attribute == NULL) {
    Py_DECREF(self);
    return NULL;
}
```
Make the attribute traversable for Python's cyclic garbage collection:
```c++
Py_VISIT(self->attribute)
```

Make the attribute clearable for the garbage collector:
```c++
Py_CLEAR(self->attribute);
```
