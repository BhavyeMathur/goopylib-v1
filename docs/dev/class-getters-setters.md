# Adding a class getter & setter function

---
### 1. Create the C++ setter function

The setter function allows the user to set the value of an attribute by typing `obj.thing = value`.

In `class.cpp` write the setter function using the following template:
```c++
static int Class_setter_thing(ClassObject *self, PyObject *value, void *closure) {}
```

Inside the function body, first check the type of object supplied as the argument. For instance, checking for an integer:
```c++
if (PyLong_Check(value)) {
    // do code
    return 0;
}
```

You may nest multiple if statements to ensure a valid value has been entered. Outside the `if` statement, raise a `TypeError` or a `ValueError`:
```c++
PyErr_Format(PyExc_TypeError, "integer argument expected, got %S", PyObject_Type(value));
return -1;
```
```c++
PyErr_SetString(PyExc_ValueError, "error string");
return -1;
```

#### Setting PyObject* attributes

To set a class attribute that is a `PyObject*` use the following template:
```c++
PyObject *tmp = self->attribute;
Py_INCREF(value);
self->attribute = value;
Py_DECREF(tmp);
```

---
### 2. Create the C++ set function
The set function allows the user to set the value of an attribute by calling `obj.set_thing(value)`. Use the following template for the set function:
```c++
static PyObject *Class_set_thing(ClassObject *self, PyObject *obj) {
    if (Class_setter_thing(self, obj, nullptr)) {
        return nullptr;
    }
    Py_RETURN_NONE;
}
```

---
### 3. Create the C++ getter function

The getter function allows the user to get the value of an attribute by calling `obj.get_thing()` or typing `obj.thing`.

Write the getter function using the following template:
```c++
static PyObject *Class_get_thing(ClassObject *self, void *closure) {}
```

#### Getting PyObject* attributes

To get a class attribute that is a `PyObject*` use the following template:
```c++
Py_INCREF(self->attribute);
return self->attribute;
```

---
### 4. Add the getter and setter functions

First, add the `get_thing()` method to the class methods:
```c++
{"get_thing", (PyCFunction) Class_get_thing, METH_NOARGS, "doc"},
```
Next, add the `set_thing()` method to the class methods:
```c++
{"set_thing", (PyCFunction) Class_set_thing, METH_O, "doc"},
```
Then, add the getter-setter pair to the class:
```c++
{"thing", (getter) Class_get_thing, (setter) Class_setter_thing, "class thing", nullptr},
```

---
### 5. Add the Python interface for the getters & setters

In `class.py` add the following methods to the class:
```python
def get_thing(self) -> type:
    pass

def set_thing(self, thing: type) -> NoReturn:
    pass
```
Then add the class attribute to the initialisation function:
```python
self.thing: type = 0
```

---
### 6. Write unit tests for getters & setters

In `tests/class.py` create at least the following unit tests and test the methods.
```python
def test_get_thing(self):
    self.assertEqual(obj.thing, "value")
    self.assertEqual(obj.get_thing(), "value")

def test_set_thing(self):
    obj.thing = "value"
    self.assertEqual(obj.thing, "value")

    obj.set_thing("value2")
    self.assertEqual(obj.get_thing(), "value2")
```
Also write unit tests to test for invalid inputs to the setter:
```python
def test_set_thing_invalid(self):
    with self.assertRaises(TypeError):
        obj.thing = "wrongtype"
    with self.assertRaises(TypeError):
        obj.set_thing("wrongtype")
```
