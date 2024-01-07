#pragma once

#include "gp.h"
#include "src/goopylib/scene/Renderer.h"
#include "src/goopylib/scene/Camera.h"
#include "src/goopylib/color/Color.h"
#include "src/goopylib/shader/Shader.h"

namespace gp {

    class RenderingManager {

        friend class Renderer;

    public:
        GPAPI RenderingManager(const Window&, int width, int height);

        GPAPI RenderingManager(const RenderingManager &) = delete;

        GPAPI RenderingManager(RenderingManager &&other) = delete;

        GPAPI void render();

        // Width
        /**
         * @param value in screen coordinates
         *
         * @throws std::invalid_argument value must be greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setWidth(int value);

        /**
         * @return in screen coordinates
         */
        [[nodiscard]] GPAPI int getWidth() const;

        // Height
        /**
         * @param value in screen coordinates
         *
         * @throws std::invalid_argument value must be greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setHeight(int value);

        /**
         * @return in screen coordinates
         */
        [[nodiscard]] GPAPI int getHeight() const;

        // Background
        /**
         * The background color of the window.
         *
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setBackground(const Color &value);

        /**
         * @return the background color of the Window
         */
        [[nodiscard]] GPAPI Color &getBackground();

        /**
         * @return the Camera object associated with the Window
         */
        [[nodiscard]] GPAPI Camera &getCamera();

        /**
         * Converts coordinates in screen space to world space.
         * \n\n
         * (0, 0) is the upper-left of the window in screen space\n
         * (width, height) is the lower-right in screen space
         *
         * @param p a struct with (x, y) in screen coordinates
         * @return a struct with (x, y) in world coordinates
         */
        [[nodiscard]] GPAPI Point toWorld(Point p);

        /**
         * Converts coordinates in world space to screen space.
         * \n\n
         * With the default camera projection, (0, 0) is the center in world space.
         *
         * @param p a struct with (x, y) in world coordinates
         * @return a struct with (x, y) in screen coordinates
         */
        [[nodiscard]] GPAPI Point toScreen(Point p);

        [[nodiscard]] GPAPI uint32_t drawLine(Line *object);

        GPAPI void destroyLine(uint32_t ID, const Line *object);

        GPAPI void updateLine(uint32_t ID, const Line *object);

        [[nodiscard]] GPAPI uint32_t drawTriangle(Triangle *object);

        GPAPI void destroyTriangle(uint32_t ID, const Triangle *object);

        GPAPI void updateTriangle(uint32_t ID, const Triangle *object);

        [[nodiscard]] GPAPI uint32_t drawQuad(Quad *object);

        GPAPI void destroyQuad(uint32_t ID, const Quad *object);

        GPAPI void updateQuad(uint32_t ID, const Quad *object);

        [[nodiscard]] GPAPI uint32_t drawEllipse(Ellipse *object);

        GPAPI void destroyEllipse(uint32_t ID, const Ellipse *object);

        GPAPI void updateEllipse(uint32_t ID, const Ellipse *object);

        [[nodiscard]] GPAPI uint32_t drawTexturedQuad(TexturedQuad *object);

        GPAPI void destroyTexturedQuad(uint32_t ID, const TexturedQuad *object);

        GPAPI void updateTexturedQuad(uint32_t ID, TexturedQuad *object);

    protected:
        int m_Width;
        int m_Height;
        const char *m_Title;

        Color m_Background;

        GPAPI void init();

        GPAPI virtual void _updateSize() const = 0;

    private:
        Camera m_Camera;
        Renderer m_Renderer;
        Renderer m_AlphaRenderer;

        Scope<Shader> m_SolidShader;
        Scope<Shader> m_EllipseShader;
        Scope<Shader> m_TextureShader;  // TODO can we make these non-heap allocated?

        Scope<UniformBuffer> m_ShaderUniform;

        uint32_t m_NextObjectID = 0;
        std::unordered_map<uint32_t, bool> m_ObjectToIsOpaque;

        GPAPI void _updateBackground();
    };
}
