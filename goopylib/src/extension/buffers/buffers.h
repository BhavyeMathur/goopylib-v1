#pragma once

#include "extension/header.h"

#include "goopylib/core/Buffer.h"

extern PyTypeObject BufferElementType;
extern PyTypeObject VertexBufferType;
extern PyTypeObject IndexBufferType;

struct VertexBufferObject {
    PyObject_HEAD
    std::shared_ptr<gp::VertexBuffer> buffer;
    PyObject *data;
    PyObject *layout;
    const char *repr;
};

struct IndexBufferObject {
    PyObject_HEAD
    std::shared_ptr<gp::IndexBuffer> buffer;
    const char *repr;
};
