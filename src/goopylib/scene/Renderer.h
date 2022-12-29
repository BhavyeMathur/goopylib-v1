#pragma once

#include "gp.h"
#include <unordered_map>

#include "goopylib/objects/Point.h"
#include "goopylib/core/Texture2D.h"
#include "goopylib/core/VertexArray.h"
#include "goopylib/scene/Camera.h"


#define LINES 0
#define TRIANGLES 1
#define QUADS 2
#define ELLIPSES 3
#define IMAGES 4

namespace gp {
    class Line;

    class Triangle;

    class Quad;

    class Ellipse;

    class Image;

    class Shader;


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
                  shader(shader),
                  bufferData(bufferData),
                  mode(mode) {
        }
    };

    class Renderer {

        friend class Window;

        friend class Renderable;

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

        Ref<UniformBuffer> m_ShaderUniform;

        std::vector<Ref<Texture2D>> m_Textures;
        std::unordered_map<std::string, TextureData> m_TexturesCache;

        std::vector<RenderingData> m_RenderingObjects;
        Camera m_Camera;

        const unsigned int s_TextureSlots = 16;

        Renderer(float width, float height);

        ~Renderer();

        void init();

        uint32_t drawLine(Line *object);

        void destroyLine(uint32_t ID);

        void updateLine(uint32_t ID, const Line *object);

        uint32_t drawTriangle(Triangle *object);

        void destroyTriangle(uint32_t ID);

        void updateTriangle(uint32_t ID, const Triangle *object);

        uint32_t drawQuad(Quad *object);

        void destroyQuad(uint32_t ID);

        void updateQuad(uint32_t ID, const Quad *object);

        uint32_t drawEllipse(Ellipse *object);

        void destroyEllipse(uint32_t ID);

        void updateEllipse(uint32_t ID, const Ellipse *object);

        uint32_t drawImage(Image *object);

        void destroyImage(uint32_t ID);

        void updateImage(uint32_t ID, const Image *object);

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
