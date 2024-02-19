#pragma once

#include "goopylib/header.h"
#include "scene/Camera.h"

struct CameraObject {
    PyObject_HEAD
    shared_ptr<gp::Camera> camera;
};
