struct WindowObject {
    std::vector<TriangleObject *> triangleInstances;
};

namespace window_ {
    void drawTriangle(WindowObject *self, TriangleObject *triangle) {
        if (std::find(self->triangleInstances.begin(), self->triangleInstances.end(), triangle) ==
            self->triangleInstances.end()) {
            Py_INCREF(triangle);
            self->triangleInstances.push_back(triangle);
        }
    }

    void destroyTriangle(WindowObject *self, TriangleObject *triangle) {
        Py_DECREF(triangle);
        self->triangleInstances.erase(
                std::find(self->triangleInstances.begin(), self->triangleInstances.end(), triangle));
    }
}
