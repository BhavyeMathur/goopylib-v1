#pragma once

#include "Point.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Core/VertexArray.h"
#include "src/goopylib/Core/Shader.h"


namespace gp {

    class Triangle {
    public:
        Triangle(Point p1, Point p2, Point p3);
        ~Triangle();

        void draw() const;

        static void bindShader();

        static std::shared_ptr<Triangle> create(Point p1, Point p2, Point p3);

    private:
        Point m_Position;

        static std::unique_ptr<Shader> s_Shader;
    };
}
