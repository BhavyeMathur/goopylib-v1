#pragma once

#include "gp.h"

#include "Batch.h"
#include "Camera.h"
#include "src/goopylib/objects/Vertex.h"
#include "src/goopylib/texture/TextureAtlas.h"


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

    class TextureAtlas;

    struct TextureBatch {
        TextureAtlas *atlas;
        Ref<Shader> shader;
        std::vector<Batch<TextureVertex>> batches;
    };

    class Renderer {

        friend class Window;

    public:
        GPAPI ~Renderer();

        GPAPI void init();

        GPAPI void destroy(uint32_t ID);

        GPAPI uint32_t drawLine(Line *object);

        GPAPI uint32_t drawTriangle(Triangle *object);

        GPAPI uint32_t drawQuad(Quad *object);

        GPAPI uint32_t drawEllipse(Ellipse *object);

        GPAPI uint32_t drawTexturedQuad(TexturedQuad *object);

        GPAPI void flush();

    private:
        Batch<SolidVertex> m_LineBatch;
        Batch<SolidVertex> m_TriangleBatch;
        Batch<SolidVertex> m_QuadBatch;
        Batch<EllipseVertex> m_EllipseBatch;

        std::array<TextureBatch, 4> m_TextureBatches;

        std::unordered_map<uint32_t, BatchBase *> m_ToBatch;

        Ref<Shader> m_SolidShader;
        Ref<Shader> m_EllipseShader;

        std::unordered_map<std::string, TextureCoords> m_TexturesCache;

        Camera m_Camera;
        Ref<UniformBuffer> m_ShaderUniform;

        Renderer(float width, float height);

        void _createLineBuffer();

        void _createTriangleBuffer();

        void _createQuadBuffer();

        void _createEllipseBuffer();

        void _createTexturedBuffer();

        void _cacheTexture(const std::string &name, const Ref<Bitmap> &bitmap);
    };
}
