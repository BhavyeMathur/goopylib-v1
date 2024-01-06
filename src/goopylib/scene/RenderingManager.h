#pragma once

#include "gp.h"
#include "src/goopylib/scene/Renderer.h"
#include "src/goopylib/scene/Camera.h"
#include "src/goopylib/color/Color.h"

namespace gp {
    class Shader;

    class UniformBuffer;

    class RenderingManager {

        friend class Renderer;

    public:
        GPAPI RenderingManager(const Window&, int width, int height);

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

        GPAPI void destroyLine(uint32_t ID);

        GPAPI void updateLine(uint32_t ID, const Line *object);

        [[nodiscard]] GPAPI uint32_t drawTriangle(Triangle *object);

        GPAPI void destroyTriangle(uint32_t ID);

        GPAPI void updateTriangle(uint32_t ID, const Triangle *object);

        [[nodiscard]] GPAPI uint32_t drawQuad(Quad *object);

        GPAPI void destroyQuad(uint32_t ID);

        GPAPI void updateQuad(uint32_t ID, const Quad *object);

        [[nodiscard]] GPAPI uint32_t drawEllipse(Ellipse *object);

        GPAPI void destroyEllipse(uint32_t ID);

        GPAPI void updateEllipse(uint32_t ID, const Ellipse *object);

        [[nodiscard]] GPAPI uint32_t drawTexturedQuad(TexturedQuad *object);

        GPAPI void destroyTexturedQuad(uint32_t ID);

        GPAPI void updateTexturedQuad(uint32_t ID, const TexturedQuad *object);

    protected:
        int m_Width;
        int m_Height;

        Color m_Background;

        GPAPI void init();

        GPAPI virtual void _updateSize() const = 0;

    private:
        Camera m_Camera;
        Renderer m_Renderer;

        Ref<Shader> m_SolidShader;
        Ref<Shader> m_EllipseShader;
        Ref<Shader> m_TextureShader;  // TODO why are these Ref?

        Ref<UniformBuffer> m_ShaderUniform;

        GPAPI void _updateBackground();
    };
}
