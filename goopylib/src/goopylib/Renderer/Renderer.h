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

        int32_t count;
        void *bufferData;
        bool reallocateBufferData = false;

        RenderingData(const Ref<VertexArray> &VAO, const Ref<VertexBuffer> &VBO, void *bufferData,
                      const Ref<Shader> &shader, int32_t count = 0)
                : VAO(VAO),
                  VBO(VBO),
                  bufferData(bufferData),
                  shader(shader),
                  count(count) {
        }
    };

    class Renderer {

        friend class BaseWindow;
        friend class VertexArray;
        friend class Triangle;

    private:
        std::vector<TriangleVertex> m_TriangleVertices;
        uint32_t m_NextTriangleID = 0;
        std::unordered_map<uint32_t, uint32_t> m_TriangleIDs;

        std::unordered_map<const char *, RenderingData> m_RenderingObjects;

        Renderer();

        ~Renderer();

        void init();

        void drawVertexArray(const Ref<VertexArray> &VAO, const Ref<Shader> &shader, int32_t count = 0);

        uint32_t drawTriangle(TriangleVertex v1, TriangleVertex v2, TriangleVertex v3);

        void destroyTriangle(uint32_t ID);

        void updateTriangle(uint32_t ID, TriangleVertex v1, TriangleVertex v2, TriangleVertex v3);

        void flush();
    };
}
