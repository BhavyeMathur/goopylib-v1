#pragma once

#include "pch.h"
#include "Point.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Core/VertexArray.h"

namespace gp {
    class Renderer {
    public:
        Renderer();

        ~Renderer();

        void init();

        uint32_t drawTriangle(Point p1, Point p2, Point p3);

        void destroyTriangle(uint32_t ID);

        void flush();

    private:
        std::vector<float> m_TriangleVertices;
        std::vector<uint32_t> m_TriangleIDs;
        int32_t m_Triangles = 0;

        Ref<VertexArray> m_TriangleVAO;
        Ref<VertexBuffer> m_TriangleVBO;
        bool m_UpdateTriangleVBO = false;

        static int32_t s_MaxTriangles;
        static uint32_t s_MaxTriangleIndices;
    };
}
