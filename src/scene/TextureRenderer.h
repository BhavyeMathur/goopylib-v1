#pragma once

#include "gp.h"
#include "RenderingBatch.h"

namespace gp {
    class TextureBuffer;

    class TexturedQuad;

    class Bitmap;

    class Shader;

    struct TextureVertex;

    struct TextureVertexAttrib;

    struct TextureData {
        shared_ptr<TextureBuffer> texture;
        uint32_t index;
    };
}

namespace gp {
    class TextureRenderer {
    public:
        TextureRenderer(const Shader &shader);

        void drawObject(uint32_t ID, const shared_ptr<TexturedQuad> &object);

        void destroyObject(uint32_t ID);

        void updateObject(uint32_t ID, const shared_ptr<TexturedQuad>& object);

        void draw();

    private:
        const Shader &m_Shader;

        std::vector<shared_ptr<TextureBuffer> > m_Textures;
        std::unordered_map<std::string, TextureData> m_TexturesCache;

        std::vector<RenderingBatch<TexturedQuad, TextureVertex, TextureVertexAttrib>> m_TexturedQuadBatches{};
        std::unordered_map<uint32_t, uint32_t> m_TexturedQuadToBatch;

        void _createTexturedBuffer();

        [[nodiscard]] uint32_t _cacheTexture(const std::string &name, const Bitmap &bitmap);

        void _bindTextureBatch(uint32_t offset) const;
    };
}
