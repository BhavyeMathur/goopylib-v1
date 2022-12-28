#pragma once

#include "ext/header.h"

#include "goopylib/core/Buffer.h"

extern PyTypeObject BufferElementType;
extern PyTypeObject VertexBufferType;
extern PyTypeObject IndexBufferType;

struct VertexBufferObject {
    PyObject_HEAD
    Ref<gp::VertexBuffer> buffer;
    PyObject *data;
    PyObject *layout;
    const char *repr;
};

struct IndexBufferObject {
    PyObject_HEAD
    Ref<gp::IndexBuffer> buffer;
    const char *repr;
};
