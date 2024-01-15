#pragma once

#include "gp.h"
#include <unordered_map>

#include "src/goopylib/objects/Vertex.h"
#include "src/goopylib/core/VertexArray.h"

#if __APPLE__

#include <OpenGL/gl.h>

#endif

#if GP_USING_GLAD
#include <glad/glad.h>
#endif


namespace gp {
    class Line;

    class Triangle;

    class Quad;

    class Ellipse;

    class TexturedQuad;

    class Shader;

    class Texture2D;

    class Bitmap;

    class VertexArray;

    class Window;


    struct TextureData {
        shared_ptr<Texture2D> texture;
        uint32_t index;
    };

    struct RenderingBatch {
        VertexArray VAO;

        int32_t indices = 0;
        int32_t vertices = 0;
        void *bufferData = nullptr;
        bool reallocateBufferData = false;
        bool updateBufferData = false;

        int32_t mode;

        RenderingBatch(const BufferLayout &layout, int32_t mode = GP_DRAW_MODE_TRIANGLES)
                : VAO(layout),
                  mode(mode) {
        }
    };

    class Renderer {

        friend class Window;

        friend class RenderingManager;

    public:
        GPAPI Renderer(const Renderer &) = delete;

        GPAPI Renderer(Renderer &&other) = delete;

        GPAPI ~Renderer();

        GPAPI void init();

        GPAPI void drawLine(uint32_t ID, const Line *object);

        GPAPI void destroyLine(uint32_t ID);

        GPAPI void updateLine(uint32_t ID, const Line *object);

        GPAPI void drawTriangle(uint32_t ID, const Triangle *object);

        GPAPI void destroyTriangle(uint32_t ID);

        GPAPI void updateTriangle(uint32_t ID, const Triangle *object);

        GPAPI void drawQuad(uint32_t ID, const Quad *object);

        GPAPI void destroyQuad(uint32_t ID);

        GPAPI void updateQuad(uint32_t ID, const Quad *object);

        GPAPI void drawEllipse(uint32_t ID, const Ellipse *object);

        GPAPI void destroyEllipse(uint32_t ID);

        GPAPI void updateEllipse(uint32_t ID, const Ellipse *object);

        GPAPI void drawTexturedQuad(uint32_t ID, TexturedQuad *object);

        GPAPI void destroyTexturedQuad(uint32_t ID);

        GPAPI void updateTexturedQuad(uint32_t ID, const TexturedQuad *object);

        GPAPI void flush();

    private:
        RenderingBatch m_LineBatch{{{ShaderDataType::Float2, "position"},
                                    {ShaderDataType::Float, "z"},
                                    {ShaderDataType::Float4, "color"}}, GP_DRAW_MODE_LINES};
        std::vector<SolidVertex> m_LineVertices;
        std::unordered_map<uint32_t, uint32_t> m_LineToIndex;

        RenderingBatch m_TriangleBatch{{{ShaderDataType::Float2, "position"},
                                        {ShaderDataType::Float, "z"},
                                        {ShaderDataType::Float4, "color"}}};
        std::vector<SolidVertex> m_TriangleVertices;
        std::unordered_map<uint32_t, uint32_t> m_TriangleToIndex;

        RenderingBatch m_QuadBatch{{{ShaderDataType::Float2, "position"},
                                    {ShaderDataType::Float, "z"},
                                    {ShaderDataType::Float4, "color"}}};
        std::vector<SolidVertex> m_QuadVertices;
        std::unordered_map<uint32_t, uint32_t> m_QuadToIndex;

        RenderingBatch m_EllipseBatch{{{ShaderDataType::Float2, "position"},
                                       {ShaderDataType::Float, "z"},
                                       {ShaderDataType::Float2, "localCoord"},
                                       {ShaderDataType::Float4, "color"}}};
        std::vector<EllipseVertex> m_EllipseVertices;
        std::unordered_map<uint32_t, uint32_t> m_EllipseToIndex;

        std::vector<RenderingBatch> m_TexturedQuadBatches;
        std::vector<std::vector<TextureVertex>> m_TexturedQuadVertices;
        std::unordered_map<uint32_t, uint32_t> m_TexturedQuadToBatch;
        std::vector<std::unordered_map<uint32_t, uint32_t>> m_TexturedQuadToIndex;

        std::vector<shared_ptr<Texture2D>> m_Textures;
        std::unordered_map<std::string, TextureData> m_TexturesCache;

        const Window &m_Window;

        GPAPI Renderer(const Window &window);

        GPAPI void _createLineBuffer();

        GPAPI void _createTriangleBuffer();

        GPAPI void _createQuadBuffer();

        GPAPI void _createEllipseBuffer();

        GPAPI void _createTexturedBuffer();

        [[nodiscard]] GPAPI uint32_t _cacheTexture(const std::string &name, const Bitmap &bitmap);

        GPAPI void _bindTextureBatch(uint32_t offset);

        GPAPI static void _updateRenderingObjectVBO(RenderingBatch &object);

        GPAPI static void _updateRenderingObjectEBO(RenderingBatch &object);
    };
}
