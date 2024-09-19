#pragma once

#include "gp.h"
#include <unordered_map>

#include "RenderingBatch.h"
#include "objects/Vertex.h"

namespace gp {
    class Renderable;

    class Triangle;

    class Quad;

    class Ellipse;

    class TexturedQuad;

    class Shader;

    class TextureBuffer;

    class Bitmap;

    class RenderingManager;

    struct TextureData {
        shared_ptr<TextureBuffer> texture;
        uint32_t index;
    };

    class GPAPI Renderer {
        friend class Window;

        friend class RenderingManager;

    public:
        Renderer(const Renderer &) = delete;

        Renderer(Renderer &&other) = delete;

        ~Renderer();

        void init();

        void draw(uint32_t ID, const shared_ptr<Renderable>& object);

        void destroy(uint32_t ID, const shared_ptr<Renderable>& object);

        void update(uint32_t ID, const shared_ptr<Renderable>& object);

        void drawTexturedQuad(uint32_t ID, const shared_ptr<TexturedQuad>& object);

        void destroyTexturedQuad(uint32_t ID);

        void updateTexturedQuad(uint32_t ID, const shared_ptr<TexturedQuad>& object);

        void flush();

    private:
        const RenderingManager &m_Window;

        RenderingBatch<Triangle, SolidVertex, SolidVertexAttrib> m_TriangleBatch;
        RenderingBatch<Quad, SolidVertex, SolidVertexAttrib> m_QuadBatch;
        RenderingBatch<Ellipse, EllipseVertex, EllipseVertexAttrib> m_EllipseBatch;

        std::vector<RenderingBatch<TexturedQuad, TextureVertex, TextureVertexAttrib>> m_TexturedQuadBatches;
        std::unordered_map<uint32_t, uint32_t> m_TexturedQuadToBatch;

        std::vector<shared_ptr<TextureBuffer> > m_Textures;
        std::unordered_map<std::string, TextureData> m_TexturesCache;

        Renderer(const RenderingManager &window);

        void _createTexturedBuffer();

        [[nodiscard]] uint32_t _cacheTexture(const std::string &name, const Bitmap &bitmap);

        void _bindTextureBatch(uint32_t offset) const;
    };
}
