#pragma once

#include "pch.h"
#include "Point.h"
#include "Triangle.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Core/VertexArray.h"

namespace gp {
    struct TriangleVertex {
        float x;
        float y;
    };
}

namespace gp {
    class Renderer {
    public:
        Renderer();

        void drawTriangle(Point p1, Point p2, Point p3);

        void flush();

    private:
        float* m_TriangleVertices;
        int m_Triangles = 0;

        Ref<VertexArray> m_TriangleVAO;
        Ref<VertexBuffer> m_TriangleVBO;
        bool m_UpdateTriangleVAO = false;

        static const int s_MaxTriangles = 1000000;
        static const int s_MaxTriangleVertices = s_MaxTriangles * 6;
    };
}
