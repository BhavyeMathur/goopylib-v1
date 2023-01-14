#include "Renderer.h"

#include "src/goopylib/core/VertexArray.h"
#include "src/goopylib/shader/Shader.h"

#include "src/goopylib/texture/Texture2D.h"
#include "src/goopylib/texture/TextureAtlas.h"

#include "src/goopylib/objects/Line.h"
#include "src/goopylib/objects/Triangle.h"
#include "src/goopylib/objects/Quad.h"
#include "src/goopylib/objects/Ellipse.h"
#include "src/goopylib/objects/TexturedQuad.h"
#include "src/goopylib/objects/text/Text.h"

#include "src/config.h"

#if (GP_LOG_RENDERER != true) and (GP_LOG_RENDERER <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_RENDERER
#endif

#if !GP_VALUE_CHECK_RENDERER
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"

#define GP_GREYSCALE 0
#define GP_RGB 1
#define GP_RGBA 2
#define GP_FONT_SDF 3

const char *solidVertexShader =

        #include "src/goopylib/shader/solid.vert"

const char *solidFragmentShader =

        #include "src/goopylib/shader/solid.frag"

const char *ellipseVertexShader =

        #include "src/goopylib/shader/ellipse.vert"

const char *ellipseFragmentShader =

        #include "src/goopylib/shader/ellipse.frag"

const char *textureVertexShader =

        #include "src/goopylib/shader/texture.vert"

const char *textureFragmentShader =

        #include "src/goopylib/shader/texture.frag"

const char *fontBitmapFragmentShader =

        #include "src/goopylib/shader/text.frag"

const char *fontSDFFragmentShader =

        #include "src/goopylib/shader/textSDF.frag"

namespace gp {
    Renderer::Renderer(float width, float height)
            : m_Camera(-width / 2, width / 2, -height / 2, height / 2) {

    }

    void Renderer::init() {
        GP_CORE_INFO("Rendering::init() initializing Renderer");

        Line::init();
        Texture2D::init();
        TextureAtlas::init();

        GP_CORE_TRACE("Rendering::init() initializing Solid Shader");
        m_SolidShader = CreateRef<Shader>(solidVertexShader, solidFragmentShader);

        GP_CORE_TRACE("Rendering::init() initializing Ellipse Shader");
        m_EllipseShader = CreateRef<Shader>(ellipseVertexShader, ellipseFragmentShader);

        _createLineBuffer();
        _createTriangleBuffer();
        _createQuadBuffer();
        _createEllipseBuffer();

        GP_CORE_TRACE("Rendering::init() initializing texture Shaders");
        auto textureShader = CreateRef<Shader>(textureVertexShader, textureFragmentShader);
        // auto fontBitmapShader = CreateRef<Shader>(textureVertexShader, textBitmapFragmentShader);
        auto fontSDFShader = CreateRef<Shader>(textureVertexShader, fontSDFFragmentShader);

        int32_t samplers[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                                9, 10, 11, 12, 13, 14, 15};

        // fontBitmapShader->set("Texture", Texture2D::getTextureSlots(), samplers);
        fontSDFShader->set("Texture", Texture2D::getTextureSlots(), samplers);
        textureShader->set("Texture", Texture2D::getTextureSlots(), samplers);

        m_ShaderUniform = Ref<UniformBuffer>(new UniformBuffer({{ShaderDataType::Mat4, "PVMatrix"}}));
        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1);

        m_SolidShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
        m_EllipseShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
        textureShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
        // fontBitmapShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
        fontSDFShader->setUniformBlock(m_ShaderUniform, "Projection", 0);

        m_TextureBatches[GP_GREYSCALE] = {new TextureAtlas(1), textureShader};
        m_TextureBatches[GP_RGB] = {new TextureAtlas(3), textureShader};
        m_TextureBatches[GP_RGBA] = {new TextureAtlas(4), textureShader};
        m_TextureBatches[GP_FONT_SDF] = {new TextureAtlas(1), fontSDFShader};
        m_TextureBatches[GP_FONT_SDF].atlas->setTextureType(TextureType::FontSDF);
    }

    Renderer::~Renderer() {
        delete m_TextureBatches[GP_GREYSCALE].atlas;
        delete m_TextureBatches[GP_RGB].atlas;
        delete m_TextureBatches[GP_RGBA].atlas;
        delete m_TextureBatches[GP_FONT_SDF].atlas;
    }

    void Renderer::_createLineBuffer() {
        GP_CORE_TRACE("Renderer::_createLineBuffer()");

        auto VAO = Ref<VertexArray>(new VertexArray());
        auto VBO = Ref<VertexBuffer>(new VertexBuffer());

        VBO->setLayout({{ShaderDataType::Float2, "position"},
                        {ShaderDataType::Float4, "color"}});
        VAO->setVertexBuffer(VBO);

        m_LineBatch = {VAO, 2, 2};
    }

    void Renderer::_createTriangleBuffer() {
        GP_CORE_TRACE("Renderer::_createTriangleBuffer()");

        auto VAO = Ref<VertexArray>(new VertexArray());
        auto VBO = Ref<VertexBuffer>(new VertexBuffer());

        VBO->setLayout({{ShaderDataType::Float2, "position"},
                        {ShaderDataType::Float4, "color"}});
        VAO->setVertexBuffer(VBO);

        m_TriangleBatch = {VAO, 3, 3};
    }

    void Renderer::_createQuadBuffer() {
        GP_CORE_TRACE("Renderer::_createQuadBuffer()");

        auto VAO = Ref<VertexArray>(new VertexArray());
        auto VBO = Ref<VertexBuffer>(new VertexBuffer());

        VBO->setLayout({{ShaderDataType::Float2, "position"},
                        {ShaderDataType::Float4, "color"}});
        VAO->setVertexBuffer(VBO);

        m_QuadBatch = {VAO, 6, 4};
    }

    void Renderer::_createEllipseBuffer() {
        GP_CORE_TRACE("Renderer::_createEllipseBuffer()");

        auto VAO = Ref<VertexArray>(new VertexArray());
        auto VBO = Ref<VertexBuffer>(new VertexBuffer());

        VBO->setLayout({{ShaderDataType::Float2, "position"},
                        {ShaderDataType::Float2, "localCoord"},
                        {ShaderDataType::Float4, "color"}});
        VAO->setVertexBuffer(VBO);

        m_EllipseBatch = {VAO, 6, 4};
    }

    void Renderer::_createTexturedBuffer() {
        GP_CORE_TRACE("Renderer::_createTexturedBuffer() creating Textured buffer");

        BufferLayout layout = {{ShaderDataType::Float2, "position"},
                               {ShaderDataType::Float4, "color"},
                               {ShaderDataType::Float2, "texCoord"},
                               {ShaderDataType::Int,    "texSlot"},};

        for (auto &batch: m_TextureBatches) {
            auto VAO = Ref<VertexArray>(new VertexArray());
            auto VBO = Ref<VertexBuffer>(new VertexBuffer());
            VBO->setLayout(layout);
            VAO->setVertexBuffer(VBO);

            batch.batches.emplace_back(VAO, 6, 4);
        }
    }

    void Renderer::destroy(uint32_t ID) {
        m_ToBatch[ID]->destroyObject(ID);
    }

    uint32_t Renderer::drawLine(Line *object) {
        SolidVertex vertices[2] = {{object->m_Points[0], object->m_V1},
                                   {object->m_Points[1], object->m_V2}};

        if (m_LineBatch.contains(object->getID())) {
            m_LineBatch.updateObject(object->getID(), vertices, object->isHidden());
            return 0;
        }
        else {
            uint32_t ID = m_LineBatch.newObject(vertices, object->isHidden());
            m_ToBatch.insert({ID, &m_LineBatch});
            return ID;
        }
    }

    uint32_t Renderer::drawTriangle(Triangle *object) {
        SolidVertex vertices[3] = {{object->m_Points[0], object->m_V1},
                                   {object->m_Points[1], object->m_V2},
                                   {object->m_Points[2], object->m_V3}};

        if (m_TriangleBatch.contains(object->getID())) {
            m_TriangleBatch.updateObject(object->getID(), vertices, object->isHidden());
            return 0;
        }
        else {
            uint32_t ID = m_TriangleBatch.newObject(vertices, object->isHidden());
            m_ToBatch.insert({ID, &m_TriangleBatch});
            return ID;
        }
    }

    uint32_t Renderer::drawQuad(Quad *object) {
        SolidVertex vertices[4] = {{object->m_Points[0], object->m_V1},
                                   {object->m_Points[1], object->m_V2},
                                   {object->m_Points[2], object->m_V3},
                                   {object->m_Points[3], object->m_V4}};

        if (m_QuadBatch.contains(object->getID())) {
            m_QuadBatch.updateObject(object->getID(), vertices, object->isHidden());
            return 0;
        }
        else {
            uint32_t ID = m_QuadBatch.newObject(vertices, object->isHidden());
            m_ToBatch.insert({ID, &m_QuadBatch});
            return ID;
        }
    }

    uint32_t Renderer::drawEllipse(Ellipse *object) {
        EllipseVertex vertices[4] = {{object->m_Points[0], object->m_V1},
                                     {object->m_Points[1], object->m_V2},
                                     {object->m_Points[2], object->m_V3},
                                     {object->m_Points[3], object->m_V4}};

        if (m_EllipseBatch.contains(object->getID())) {
            m_EllipseBatch.updateObject(object->getID(), vertices, object->isHidden());
            return 0;
        }
        else {
            uint32_t ID = m_EllipseBatch.newObject(vertices, object->isHidden());
            m_ToBatch.insert({ID, &m_EllipseBatch});
            return ID;
        }
    }

    uint32_t Renderer::drawTexturedQuad(TexturedQuad *object) {
        if (m_TexturesCache.find(object->getTextureName()) == m_TexturesCache.end()) {
            GP_CORE_TRACE("gp::Renderer::drawTexturedQuad() - no cached texture '{0}'", object->getTextureName());
            _cacheTexture(object->getTextureName(), object->getBitmap());
        }

        TextureCoords texCoords = m_TexturesCache[object->getTextureName()];
        uint32_t texSlot = texCoords.page % Texture2D::getTextureSlots();
        uint32_t batchIndex = texCoords.page / Texture2D::getTextureSlots();

        object->m_T1.texSlot = texSlot;
        object->m_T2.texSlot = texSlot;
        object->m_T3.texSlot = texSlot;
        object->m_T4.texSlot = texSlot;

        if (texCoords.rotated) {
            object->m_T3.texCoord = {texCoords.p1.x, texCoords.p2.y};
            object->m_T2.texCoord = {texCoords.p2.x, texCoords.p2.y};
            object->m_T1.texCoord = {texCoords.p2.x, texCoords.p1.y};
            object->m_T4.texCoord = {texCoords.p1.x, texCoords.p1.y};
        }
        else {
            object->m_T1.texCoord = {texCoords.p1.x, texCoords.p2.y};
            object->m_T2.texCoord = {texCoords.p2.x, texCoords.p2.y};
            object->m_T3.texCoord = {texCoords.p2.x, texCoords.p1.y};
            object->m_T4.texCoord = {texCoords.p1.x, texCoords.p1.y};
        }

        TextureVertex vertices[4] = {{object->m_Points[0], object->m_V1, object->m_T1},
                                     {object->m_Points[1], object->m_V2, object->m_T2},
                                     {object->m_Points[2], object->m_V3, object->m_T3},
                                     {object->m_Points[3], object->m_V4, object->m_T4}};

        Batch <TextureVertex> *batch;
        switch (texCoords.texture->getTextureType()) {
            case TextureType::Greyscale:
                batch = &m_TextureBatches[GP_GREYSCALE].batches[batchIndex];
                break;

            case TextureType::RGB:
                batch = &m_TextureBatches[GP_RGB].batches[batchIndex];
                break;

            case TextureType::RGBA:
                batch = &m_TextureBatches[GP_RGBA].batches[batchIndex];
                break;

            case TextureType::FontSDF:
                batch = &m_TextureBatches[GP_FONT_SDF].batches[batchIndex];
                break;

            default:
                GP_VALUE_ERROR("Renderer::drawTexturedQuad() invalid texture type");
                return -1;
        }

        if (batch->contains(object->getID())) {
            batch->updateObject(object->getID(), vertices, object->isHidden());
            return 0;
        }
        else {
            uint32_t ID = batch->newObject(vertices, object->isHidden());
            m_ToBatch.insert({ID, batch});
            return ID;
        }
    }

    void Renderer::flush() {
        GP_CORE_TRACE_ALL("gp::Renderer::flush()");

        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1, 0);

        if (!(m_LineBatch.empty() and m_TriangleBatch.empty() and m_QuadBatch.empty())) {
            m_SolidShader->bind();
        }

        m_LineBatch.draw();
        m_TriangleBatch.draw();
        m_QuadBatch.draw();

        if (!m_EllipseBatch.empty()) {
            m_EllipseShader->bind();
            m_EllipseBatch.draw();
        }

        for (auto &textureBatch: m_TextureBatches) {

            uint32_t textureOffset = 0;
            for (uint32_t i = 0; i < textureBatch.batches.size(); i += Texture2D::getTextureSlots()) {
                auto &batch = textureBatch.batches[i];

                if (!batch.empty()) {
                    textureBatch.shader->bind();

                    uint32_t textures = min(textureBatch.atlas->getPages(),
                                            textureOffset + Texture2D::getTextureSlots());
                    textures %= Texture2D::getTextureSlots();
                    for (uint32_t j = 0; j < textures; j++) {
                        textureBatch.atlas->getTextureAt(textureOffset + j)->bind(j);
                    }
                    textureOffset += Texture2D::getTextureSlots();

                    batch.draw();
                }
            }
        }
    }

    void Renderer::_cacheTexture(const std::string &name, const Ref <Bitmap> &bitmap) {
        GP_CORE_DEBUG("gp::Renderer::_cacheTexture('{0}')", name);

        TextureAtlas *atlas;
        switch (bitmap->getTextureType()) {
            case TextureType::Greyscale:
                atlas = m_TextureBatches[GP_GREYSCALE].atlas;
                break;

            case TextureType::RGB:
                atlas = m_TextureBatches[GP_RGB].atlas;
                break;

            case TextureType::RGBA:
                atlas = m_TextureBatches[GP_RGBA].atlas;
                break;

            case TextureType::FontSDF:
                atlas = m_TextureBatches[GP_FONT_SDF].atlas;
                break;

            default:
                GP_VALUE_ERROR("Renderer::_cacheTexture() invalid channels ({0}) in bitmap", bitmap->getChannels());
                return;
        }

        TextureCoords texCoords = atlas->add(bitmap);
        atlas->createTextureAtlas();

        m_TexturesCache.insert({name, texCoords});
        if (texCoords.page % Texture2D::getTextureSlots() == 0) {
            _createTexturedBuffer();
        }
    }
}
