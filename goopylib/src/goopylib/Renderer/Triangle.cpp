#include "Triangle.h"

namespace gp {

    std::unique_ptr<Shader> Triangle::s_Shader = nullptr;

    static const char *vertexShaderSource = "#version 330 core\n"
                                            "layout (location = 0) in vec3 aPos;"
                                            "void main() {"
                                            "   gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);}";

    static const char *fragmentShaderSource = "#version 330 core\n"
                                              "out vec4 FragColor;"
                                              "void main() {"
                                              "   FragColor = vec4(0.3f, 0.5f, 0.2f, 1.0f);}";

    Triangle::Triangle(Point p1, Point p2, Point p3)
            : m_Position{(p1.x + p2.x + p3.x) / 3.0f,
                         (p1.y + p2.y + p3.y) / 3.0f} {
    }

    Triangle::~Triangle() = default;

    void Triangle::bindShader(){
        if (!s_Shader) {
            s_Shader = CreateScope<Shader>(vertexShaderSource, fragmentShaderSource);
        }

        s_Shader->bind();
    }

    Ref<Triangle> Triangle::create(Point p1, Point p2, Point p3) {
        return CreateRef<Triangle>(p1, p2, p3);
    }
}
