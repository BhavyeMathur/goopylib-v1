# Adding a New Module Function

---
### 1. Create the C++ function

In `module.cpp` write the C++ function required.

If the function has no arguments:
```c++
static PyObject *function(PyObject *self) {}
```

If the function has arguments:
```c++
static PyObject *function(PyObject *self, PyObject *args) {}
```

If the function has keyword arguments:
```c++
static PyObject *function(PyObject *self, PyObject *args, PyObject *kwds) {}
```

---
### 2. Add the function to the PyMethodDef

Use `METH_NOARGS` for a function without arguments, `METH_O` for 1 argument, `METH_VARARGS`
fur multiple arguments, and `METH_KEYWORDS` for keyword arguments.
```c++
{"function", (PyCFunction) function, METH_NOARGS, "documentation"},
```

**Make sure to recompile the C++ extension!**

---
### 3. Add a Python interface for the function

In `module.py` (located in the same folder as `module.so` or `module.pyd`), add the following Python interface:
```python
def function(arg: type) -> ReturnType:
    """
    Function docstring
    """
    
    ...
```

Make sure the function is type-hinted completely.

---
### 4. Write a unit test for the function

In `tests/module.py` create all the required unit tests for the function. Then, make sure to test the function.
