#include "Triangle.h"

namespace gp {

    std::shared_ptr<IndexBuffer> Triangle::s_IndexBuffer = nullptr;
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
                         (p1.y + p2.y + p3.y) / 3.0f},
              m_VertexArray(),
              m_VertexBuffer({p1.x, p1.y, p2.x, p2.y, p3.x, p3.y}) {

        if (!s_IndexBuffer) {
            uint32_t indices[] = {0, 1, 2};
            s_IndexBuffer = std::make_shared<IndexBuffer>(indices, 3);

            s_Shader = make_unique<Shader>(vertexShaderSource, fragmentShaderSource);
        }

        m_VertexArray.setIndexBuffer(s_IndexBuffer);

        m_VertexBuffer.setLayout({{gp::ShaderDataType::Float2, "vertices"}});

        m_VertexArray.addVertexBuffer(m_VertexBuffer);
    }

    Triangle::~Triangle() = default;

    void Triangle::draw() const {
        m_VertexArray.draw();
    }

    void Triangle::bindShader(){
        s_Shader->bind();
    }

    std::shared_ptr<Triangle> Triangle::create(Point p1, Point p2, Point p3) {
        return std::make_shared<Triangle>(p1, p2, p3);
    }
}
