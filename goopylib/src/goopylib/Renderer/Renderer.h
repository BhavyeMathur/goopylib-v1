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

        int32_t count = 0;

        RenderingData(const Ref<VertexArray> &VAO, const Ref<VertexBuffer> &VBO, const Ref<Shader> &shader)
                : VAO(VAO),
                  VBO(VBO),
                  shader(shader),
                  count(0) {
        }
    };

    class Renderer {
    public:
        Renderer();

        ~Renderer();

        void init();

        uint32_t drawTriangle(TriangleVertex v1, TriangleVertex v2, TriangleVertex v3);

        void destroyTriangle(uint32_t ID);

        void updateTriangle(uint32_t ID, TriangleVertex v1, TriangleVertex v2, TriangleVertex v3);

        void flush();

    private:
        std::vector<TriangleVertex> m_TriangleVertices;
        std::vector<uint32_t> m_TriangleIDs;

        int32_t m_Triangles = 0;
        bool m_UpdateTriangleVBO = false;

        std::unordered_map<const char *, RenderingData> m_RenderingObjects;
    };
}
