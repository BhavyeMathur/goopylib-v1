#pragma once

#include "pch.h"
#include "Point.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Shader/Shader.h"
#include "src/goopylib/Core/VertexArray.h"

namespace gp {
    struct RenderingData {
        Ref<VertexArray> VAO;
        Ref<VertexBuffer> VBO;
        Ref<Shader> shader;

        int32_t count;

    };

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
        bool m_UpdateTriangleVBO = false;

        std::unordered_map<const char *, RenderingData> m_RenderingObjects;

        static const int32_t s_MaxTriangles = 1000000;
        static const uint32_t s_MaxTriangleIndices = s_MaxTriangles * 3;
    };
}
