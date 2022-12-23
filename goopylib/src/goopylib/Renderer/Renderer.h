#pragma once

#include "pch.h"
#include "Point.h"

#include "src/goopylib/Core/Texture2D.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Core/VertexArray.h"
#include "src/goopylib/Shader/Shader.h"

namespace gp {
    class Image;

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

        friend class RenderableObject;

        friend class Triangle;

        friend class Quad;

        friend class Ellipse;

        friend class Image;

    private:
        std::vector<TriangleVertex> m_TriangleVertices;
        uint32_t m_NextTriangleID = 0;
        std::unordered_map<uint32_t, uint32_t> m_TriangleIDs;

        std::vector<QuadVertex> m_QuadVertices;
        uint32_t m_NextQuadID = 0;
        std::unordered_map<uint32_t, uint32_t> m_QuadIDs;

        std::vector<EllipseVertex> m_EllipseVertices;
        uint32_t m_NextEllipseID = 0;
        std::unordered_map<uint32_t, uint32_t> m_EllipseIDs;

        std::vector<ImageVertex> m_ImageVertices;
        uint32_t m_NextImageID = 0;
        std::vector<uint32_t> m_FreeTextureSlots = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        std::unordered_map<const char *, Ref<Texture2D>> m_Textures;
        std::unordered_map<uint32_t, uint32_t> m_ImageIDs;

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

        uint32_t drawEllipse(EllipseVertex v1, EllipseVertex v2, EllipseVertex v3, EllipseVertex v4);

        void destroyEllipse(uint32_t ID);

        void updateEllipse(uint32_t ID, EllipseVertex v1, EllipseVertex v2, EllipseVertex v3, EllipseVertex v4);

        uint32_t drawImage(Image *image);

        void destroyImage(uint32_t ID);

        void updateImage(uint32_t ID, const Image *image);

        void flush();
    };
}
