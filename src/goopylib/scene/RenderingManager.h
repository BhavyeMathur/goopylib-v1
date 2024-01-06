#pragma once

#include "gp.h"
#include "src/goopylib/scene/Renderer.h"


namespace gp {
    class Shader;

    class RenderingManager {

        friend class Renderer;

    public:
        GPAPI RenderingManager(const Window&, int width, int height);

        GPAPI void render();

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

    protected:
        Camera m_Camera;

        GPAPI void init();

    private:
        Renderer m_Renderer;

        Ref<Shader> m_SolidShader;
        Ref<Shader> m_EllipseShader;
        Ref<Shader> m_TextureShader;  // TODO why are these Ref?

        Ref<UniformBuffer> m_ShaderUniform;
    };
}
