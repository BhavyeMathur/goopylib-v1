#pragma once

#include "pch.h"
#include "Point.h"

#include "src/goopylib/Core/Texture2D.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Core/VertexArray.h"
#include "src/goopylib/Shader/Shader.h"

#define LINES 0
#define TRIANGLES 1
#define QUADS 2
#define ELLIPSES 3
#define IMAGES 4

namespace gp {
    class Image;

    struct TextureData {
        Ref<Texture2D> texture;
        uint32_t index;
    };

    struct RenderingData {
        Ref<Shader> shader;
        Ref<VertexArray> VAO;

        int32_t indices = 0;
        int32_t vertices = 0;
        void *bufferData;
        bool reallocateBufferData = false;
        bool updateBufferData = false;

        int32_t mode;

        RenderingData(const Ref<VertexArray> &VAO, void *bufferData,
                      const Ref<Shader> &shader, int32_t mode = GP_DRAW_MODE_TRIANGLES)
                : VAO(VAO),
                bufferData(bufferData),
                shader(shader),
                mode(mode) {
        }
    };

    class Renderer {

        friend class Window;

        friend class RenderableObject;

        friend class Line;

        friend class Triangle;

        friend class Quad;

        friend class Ellipse;

        friend class Image;

    private:
        std::vector<LineVertex> m_LineVertices;
        uint32_t m_NextLineID = 0;
        std::unordered_map<uint32_t, uint32_t> m_LineIDs;

        std::vector<TriangleVertex> m_TriangleVertices;
        uint32_t m_NextTriangleID = 0;
        std::unordered_map<uint32_t, uint32_t> m_TriangleIDs;

        std::vector<QuadVertex> m_QuadVertices;
        uint32_t m_NextQuadID = 0;
        std::unordered_map<uint32_t, uint32_t> m_QuadIDs;

        std::vector<EllipseVertex> m_EllipseVertices;
        uint32_t m_NextEllipseID = 0;
        std::unordered_map<uint32_t, uint32_t> m_EllipseIDs;

        std::vector<std::vector<ImageVertex>> m_ImageVertices;
        uint32_t m_NextImageID = 0;
        std::unordered_map<uint32_t, uint32_t> m_ImageBatches;
        std::vector<std::unordered_map<uint32_t, uint32_t>> m_ImageIDs;

        Ref<Shader> m_LineShader;
        Ref<Shader> m_PolygonShader;
        Ref<Shader> m_EllipseShader;
        Ref<Shader> m_ImageShader;

        std::vector<Ref<Texture2D>> m_Textures;
        std::unordered_map<const char *, TextureData> m_TexturesCache;
        std::vector<RenderingData> m_RenderingObjects;

        const unsigned int s_TextureSlots = 16;

        Renderer();

        ~Renderer();

        void init();

        uint32_t drawLine(LineVertex v1, LineVertex v2);

        void destroyLine(uint32_t ID);

        void updateLine(uint32_t ID, LineVertex v1, LineVertex v2);

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

    private:
        void _createLineBuffer();

        void _createTriangleBuffer();

        void _createQuadBuffer();

        void _createEllipseBuffer();

        void _newImageBuffer();

        uint32_t _cacheTexture(const char *path);

        void _bindTextureBatch(uint32_t batch);

        static void _updateRenderingObjectVBO(RenderingData &object);

        static void _updateRenderingObjectEBO(RenderingData &object);
    };
}
