#pragma once

#include "gp.h"
#include <unordered_map>

#include "src/goopylib/objects/Vertex.h"
#include "src/goopylib/texture/Texture2D.h"
#include "src/goopylib/core/VertexArray.h"
#include "src/goopylib/scene/Camera.h"


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

    struct RenderingBatch {
        Ref<VertexArray> VAO;

        int32_t indices = 0;
        int32_t vertices = 0;
        void *bufferData;
        bool reallocateBufferData = false;
        bool updateBufferData = false;

        int32_t mode;

        RenderingBatch(const Ref<VertexArray> &VAO = nullptr,
                       void *bufferData = nullptr,
                       int32_t mode = GP_DRAW_MODE_TRIANGLES)
                : VAO(VAO),
                  bufferData(bufferData),
                  mode(mode) {
        }
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

        GPAPI void flush();

    private:
        uint32_t m_NextLineID = 0;
        RenderingBatch m_LineBatch;
        std::vector<SolidVertex> m_LineVertices;
        std::unordered_map<uint32_t, uint32_t> m_LineToIndex;

        uint32_t m_NextTriangleID = 0;
        RenderingBatch m_TriangleBatch;
        std::vector<SolidVertex> m_TriangleVertices;
        std::unordered_map<uint32_t, uint32_t> m_TriangleToIndex;

        uint32_t m_NextQuadID = 0;
        RenderingBatch m_QuadBatch;
        std::vector<SolidVertex> m_QuadVertices;
        std::unordered_map<uint32_t, uint32_t> m_QuadToIndex;

        uint32_t m_NextEllipseID = 0;
        RenderingBatch m_EllipseBatch;
        std::vector<EllipseVertex> m_EllipseVertices;
        std::unordered_map<uint32_t, uint32_t> m_EllipseToIndex;

        uint32_t m_NextTexturedQuadID = 0;
        std::vector<RenderingBatch> m_TexturedQuadBatches;
        std::vector<std::vector<TextureVertex>> m_TexturedQuadVertices;
        std::unordered_map<uint32_t, uint32_t> m_TexturedQuadToBatch;
        std::vector<std::unordered_map<uint32_t, uint32_t>> m_TexturedQuadToIndex;

        Ref<Shader> m_SolidShader;
        Ref<Shader> m_EllipseShader;
        Ref<Shader> m_TextureShader;

        Camera m_Camera;
        Ref<UniformBuffer> m_ShaderUniform;

        std::vector<Ref<Texture2D>> m_Textures;
        std::unordered_map<std::string, TextureData> m_TexturesCache;

        Renderer(float width, float height);

        GPAPI Renderer (const Renderer&) = delete;

        void _createLineBuffer();

        void _createTriangleBuffer();

        void _createQuadBuffer();

        void _createEllipseBuffer();

        void _createTexturedBuffer();
        
        uint32_t _cacheTexture(const std::string& name, const Bitmap& bitmap);

        void _bindTextureBatch(uint32_t offset);

        static void _updateRenderingObjectVBO(RenderingBatch &object);

        static void _updateRenderingObjectEBO(RenderingBatch &object);
    };
}
