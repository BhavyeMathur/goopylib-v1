#pragma once

#include "pch.h"
#include "Point.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Shader/Shader.h"
#include "src/goopylib/Core/VertexArray.h"

namespace gp {
    struct RenderingData {
        Ref<Shader> shader;
        Ref<VertexArray> VAO;
        Ref<VertexBuffer> VBO;
        Ref<IndexBuffer> EBO;

        int32_t count;
        void *bufferData;
        bool reallocateBufferData = false;
        bool updateBufferData = false;

        DrawMode mode = DrawMode::Triangles;

        RenderingData(const Ref<VertexArray> &VAO, void *bufferData,
                      const Ref<Shader> &shader, int32_t count = 0)
                : VAO(VAO),
                  VBO(VAO->getVertexBuffer()),
                  EBO(VAO->getIndexBuffer()),
                  bufferData(bufferData),
                  shader(shader),
                  count(count) {
        }
    };

    class Renderer {

        friend class BaseWindow;
        friend class Triangle;
        friend class Quad;
        friend class Circle;

    private:
        std::vector<TriangleVertex> m_TriangleVertices;
        uint32_t m_NextTriangleID = 0;
        std::unordered_map<uint32_t, uint32_t> m_TriangleIDs;

        std::vector<QuadVertex> m_QuadVertices;
        uint32_t m_NextQuadID = 0;
        std::unordered_map<uint32_t, uint32_t> m_QuadIDs;

        std::vector<CircleVertex> m_CircleVertices;
        uint32_t m_NextCircleID = 0;
        std::unordered_map<uint32_t, uint32_t> m_CircleIDs;

        std::unordered_map<const char *, RenderingData> m_RenderingObjects;

        Renderer();

        ~Renderer();

        void init();

        uint32_t drawTriangle(TriangleVertex v1, TriangleVertex v2, TriangleVertex v3);

        void destroyTriangle(uint32_t ID);

        void updateTriangle(uint32_t ID, TriangleVertex v1, TriangleVertex v2, TriangleVertex v3);

        uint32_t drawQuad(QuadVertex v1, QuadVertex v2, QuadVertex v3, QuadVertex v4);

        void destroyQuad(uint32_t ID);

        void updateQuad(uint32_t ID, QuadVertex v1, QuadVertex v2, QuadVertex v3, QuadVertex v4);

        uint32_t drawCircle(CircleVertex v1, CircleVertex v2, CircleVertex v3, CircleVertex v4);

        void destroyCircle(uint32_t ID);

        void updateCircle(uint32_t ID, CircleVertex v1, CircleVertex v2, CircleVertex v3, CircleVertex v4);

        void flush();
    };
}
