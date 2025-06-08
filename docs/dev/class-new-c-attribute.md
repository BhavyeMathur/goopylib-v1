# Adding a new native class attribute

---
### 1. Add the new attribute in C++

Begin by adding the attribute to structure of the custom class.
```c++
int attribute;
bool attribute2;
```

Initialise the attribute in the `Class_new()` function with a default value:
```c++
self->attribute = 0;
```

Optionally add the attribute to the `Class_init()` function.

**Add getter or setter methods to access the attribute.**

If you want to access the attributes without getters and setters, add it to the Class members:
```c++
{"attribute", T_INT, offsetof(ClassObject, attribute), 0, "class attribute"}
```