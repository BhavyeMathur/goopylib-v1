#pragma once

#include "gp.h"

#include "Batch.h"
#include "Camera.h"
#include "src/goopylib/objects/Vertex.h"


namespace gp {
    class Line;

    class Triangle;

    class Quad;

    class Ellipse;

    class TexturedQuad;

    class Shader;

    class Camera;

    class Texture2D;

    class Bitmap;


    struct TextureData {
        Ref<Texture2D> texture;
        uint32_t index;
    };

    class Renderer {

        friend class Window;

    public:
        GPAPI void init();

        GPAPI void destroy(uint32_t ID);

        GPAPI uint32_t drawLine(Line *object);

        GPAPI uint32_t drawTriangle(Triangle *object);

        GPAPI uint32_t drawQuad(Quad *object);

        GPAPI uint32_t drawEllipse(Ellipse *object);

        GPAPI uint32_t drawTexturedQuad(TexturedQuad *object);

        GPAPI uint32_t drawGlyph(TexturedQuad *object);

        GPAPI void flush();

    private:
        Batch<SolidVertex> m_LineBatch;
        Batch<SolidVertex> m_TriangleBatch;
        Batch<SolidVertex> m_QuadBatch;
        Batch<EllipseVertex> m_EllipseBatch;
        std::vector<Batch<TextureVertex>> m_TexturedQuadBatches;
        std::vector<Batch<TextureVertex>> m_GlyphBatches;

        std::unordered_map<uint32_t, BatchBase *> m_ToBatch;

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
    };
}
