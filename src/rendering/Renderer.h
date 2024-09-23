#pragma once

#include "gp.h"
#include <unordered_map>

#include "RenderingBatch.h"
#include "TextureRenderer.h"
#include "objects/Vertex.h"

namespace gp {
    class Renderable;

    class Triangle;

    class Quad;

    class Ellipse;

    class RenderingManager;

    class GPAPI Renderer {
        friend class Window;

        friend class RenderingManager;

    public:
        Renderer(const Renderer &) = delete;

        Renderer(Renderer &&other) = delete;

        ~Renderer() = default;

        void init();

        void draw(uint32_t ID, const shared_ptr<Renderable>& object);

        void destroy(uint32_t ID, const shared_ptr<Renderable>& object);

        void update(uint32_t ID, const shared_ptr<Renderable>& object);

        void flush();

    private:
        const RenderingManager &m_Window;

        RenderingBatch<Triangle, SolidVertex, SolidVertexAttrib> m_TriangleBatch;
        RenderingBatch<Quad, SolidVertex, SolidVertexAttrib> m_QuadBatch;
        RenderingBatch<Ellipse, EllipseVertex, EllipseVertexAttrib> m_EllipseBatch;
        TextureRenderer m_TextureRenderer;

        Renderer(const RenderingManager &window);
    };
}
