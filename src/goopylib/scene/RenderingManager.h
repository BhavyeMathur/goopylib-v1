#pragma once

#include "gp.h"
#include "src/goopylib/scene/Renderer.h"
#include "src/goopylib/scene/Camera.h"
#include "src/goopylib/color/Color.h"

#include "src/goopylib/shader/ShaderFiles.h"

namespace gp {

    class Renderable;

    class RenderingManager {

        friend class Renderer;

        friend class Renderable;

    public:
        GPAPI RenderingManager(const Window &, int width, int height, const char *title);

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
        [[nodiscard]] GPAPI Point toWorld(Point p) const;

        /**
         * Converts coordinates in world space to screen space.
         * \n\n
         * With the default camera projection, (0, 0) is the center in world space.
         *
         * @param p a struct with (x, y) in world coordinates
         * @return a struct with (x, y) in screen coordinates
         */
        [[nodiscard]] GPAPI Point toScreen(Point p) const;

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

        Shader m_SolidShader{solidVertexShader, solidFragmentShader};
        Shader m_EllipseShader{ellipseVertexShader, ellipseFragmentShader};
        Shader m_TextureShader{textureVertexShader, textureFragmentShader};

        unique_ptr<UniformBuffer> m_ShaderUniform;

        uint32_t m_NextObjectID = 0;
        std::unordered_map<uint32_t, bool> m_ObjectToIsOpaque;

        GPAPI void _updateBackground();

        GPAPI static void _enableDepthWriting();

        GPAPI static void _disableDepthWriting();

        GPAPI uint32_t _drawRenderable(Renderable *object);

        GPAPI void _undrawRenderable(Renderable *object);

        GPAPI void _updateRenderable(Renderable *object);
    };
}
