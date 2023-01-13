#pragma once

#include "gp.h"
#include <unordered_map>

#include "src/goopylib/objects/Vertex.h"
#include "src/goopylib/texture/Texture2D.h"
#include "src/goopylib/scene/Camera.h"
#include "Batch.h"


namespace gp {
    class Line;

    class Triangle;

    class Quad;

    class Ellipse;

    class TexturedQuad;

    class Shader;


    struct TextureData {
        Ref<Texture2D> texture;
        uint32_t index;
    };

    class Renderer {

        friend class Window;

    public:
        GPAPI ~Renderer();

        GPAPI void init();

        GPAPI uint32_t drawLine(Line *object);

        GPAPI void destroyLine(uint32_t ID);

        GPAPI void updateLine(uint32_t ID, const Line *object);

        GPAPI uint32_t drawTriangle(Triangle *object);

        GPAPI void destroyTriangle(uint32_t ID);

        GPAPI void updateTriangle(uint32_t ID, const Triangle *object);

        GPAPI uint32_t drawQuad(Quad *object);

        GPAPI void destroyQuad(uint32_t ID);

        GPAPI void updateQuad(uint32_t ID, const Quad *object);

        GPAPI uint32_t drawEllipse(Ellipse *object);

        GPAPI void destroyEllipse(uint32_t ID);

        GPAPI void updateEllipse(uint32_t ID, const Ellipse *object);

        GPAPI uint32_t drawTexturedQuad(TexturedQuad *object);

        GPAPI void destroyTexturedQuad(uint32_t ID);

        GPAPI void updateTexturedQuad(uint32_t ID, const TexturedQuad *object);

        GPAPI uint32_t drawGlyph(TexturedQuad *object);

        GPAPI void destroyGlyph(uint32_t ID);

        GPAPI void updateGlyph(uint32_t ID, const TexturedQuad *object);

        GPAPI void flush();

    private:
        Batch<SolidVertex> m_LineBatch;

        uint32_t m_NextTriangleID = 0;
        BatchData m_TriangleBatch;
        std::vector<SolidVertex> m_TriangleVertices;
        std::unordered_map<uint32_t, uint32_t> m_TriangleToIndex;

        uint32_t m_NextQuadID = 0;
        BatchData m_QuadBatch;
        std::vector<SolidVertex> m_QuadVertices;
        std::unordered_map<uint32_t, uint32_t> m_QuadToIndex;

        uint32_t m_NextEllipseID = 0;
        BatchData m_EllipseBatch;
        std::vector<EllipseVertex> m_EllipseVertices;
        std::unordered_map<uint32_t, uint32_t> m_EllipseToIndex;

        uint32_t m_NextTexturedQuadID = 0;
        std::vector<BatchData> m_TexturedQuadBatches;
        std::vector<std::vector<TextureVertex>> m_TexturedQuadVertices;
        std::unordered_map<uint32_t, uint32_t> m_TexturedQuadToBatch;
        std::vector<std::unordered_map<uint32_t, uint32_t>> m_TexturedQuadToIndex;

        uint32_t m_NextGlyphID = 0;
        std::vector<BatchData> m_GlyphBatches;
        std::vector<std::vector<TextureVertex>> m_GlyphVertices;
        std::unordered_map<uint32_t, uint32_t> m_GlyphToBatch;
        std::vector<std::unordered_map<uint32_t, uint32_t>> m_GlyphToIndex;

        Ref<Shader> m_SolidShader;
        Ref<Shader> m_EllipseShader;
        Ref<Shader> m_TextureShader;
        Ref<Shader> m_TextBitmapShader;
        Ref<Shader> m_TextSDFShader;

        Camera m_Camera;
        Ref<UniformBuffer> m_ShaderUniform;

        std::vector<Ref<Texture2D>> m_Textures;
        std::unordered_map<std::string, TextureData> m_TexturesCache;

        Renderer(float width, float height);

        void _createLineBuffer();

        void _createTriangleBuffer();

        void _createQuadBuffer();

        void _createEllipseBuffer();

        void _createTexturedBuffer();

        uint32_t _cacheTexture(const std::string &name, const Bitmap &bitmap);

        void _bindTextureBatch(uint32_t offset);

        static void _updateRenderingObjectVBO(BatchData &object);

        static void _updateRenderingObjectEBO(BatchData &object);
    };
}
