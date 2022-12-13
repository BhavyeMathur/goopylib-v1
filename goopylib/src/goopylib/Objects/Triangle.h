#pragma once

#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Core/VertexArray.h"
#include "src/goopylib/Core/Shader.h"


namespace gp {

    struct Point {
        float x;
        float y;
    };

    class Triangle {
    public:
        Triangle(Point p1, Point p2, Point p3);
        ~Triangle();

        void draw() const;

        static void bindShader();

        static std::shared_ptr<Triangle> create(Point p1, Point p2, Point p3);

    private:
        Point m_Position;

        VertexArray m_VertexArray;
        VertexBuffer m_VertexBuffer;

        static std::shared_ptr<IndexBuffer> s_IndexBuffer;
        static std::unique_ptr<Shader> s_Shader;
    };
}
