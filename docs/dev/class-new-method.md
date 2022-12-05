# Adding a new class method

---
### 1. Create the C++ class method

In `class.cpp` write the class method using either of the signatures:
```c++
static PyObject *Class_method(ClassObject *self, PyObject *Py_UNUSED(ignored)) {}
```
```c++
static PyObject *Class_method(ClassObject *self, PyObject *args) {}
```
```c++
static PyObject *Class_method(ClassObject *self, PyObject *args, PyObject *kwds) {}
```

At the end always use `return someobject;`, `Py_RETURN_NONE;`, `Py_RETURN_TRUE;`, etc.

---
### 2. Add the C++ class method

Add the method to the class methods:
```c++
{"method", (PyCFunction) Class_method, METH_O, "doc"},
```

Use `METH_NOARGS` for a function without arguments, `METH_O` for 1 argument, `METH_VARARGS`
fur multiple arguments, and `METH_KEYWORDS` for keyword arguments.

---
### 3. Add a Python interface for the method

In `class.py` add a fully type-hinted empty method such as:
```python
def method(self, arg: type) -> ReturnType:
    pass
```

---
### 4. Write a unit test for the function

In `tests/class.py` write all the required unit tests for the method and run the tests.