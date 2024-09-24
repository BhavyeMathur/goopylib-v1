#pragma once

#include "gp.h"
#include "RenderingBatch.h"
#include "texture/TextureAtlas.h"

namespace gp {
    class TexturedQuad;

    class Shader;

    struct TextureVertex;

    struct TextureVertexAttrib;
}

namespace gp {
    class TextureRenderer {
    public:
        TextureRenderer(const Shader &shader);

        void setTextureAtlas(const shared_ptr<TextureAtlas>& textureAtlas);

        void drawObject(uint32_t ID, const shared_ptr<TexturedQuad> &object);

        void destroyObject(uint32_t ID);

        void updateObject(uint32_t ID, const shared_ptr<TexturedQuad> &object);

        void draw();

    private:
        const Shader &m_Shader;

        shared_ptr<TextureAtlas> m_TextureAtlas;

        std::unordered_map<uint32_t, shared_ptr<TexturedQuad>> m_QueuedObjects;

        std::vector<RenderingBatch<TexturedQuad, TextureVertex, TextureVertexAttrib>> m_TexturedQuadBatches{};
        std::unordered_map<uint32_t, uint32_t> m_TexturedQuadToBatch;

        const uint32_t m_Channels = 4;

        void _createTexturedBuffer();

        void _cacheTexture(const shared_ptr<TexturedQuad> &object);

        void _bindTextureBatch(uint32_t offset) const;

        void _processQueuedObjects();
    };
}
