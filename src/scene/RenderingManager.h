#pragma once

#include "gp.h"
#include "scene/Renderer.h"
#include "scene/Camera.h"
#include "color/Color.h"

#include "shader/ShaderFiles.h"

namespace gp {

    class Renderable;

    class GPAPI RenderingManager {

        friend class Renderer;

        friend class Renderable;

    public:
        RenderingManager(const Window &, int width, int height, const char *title);

        RenderingManager(const RenderingManager &) = delete;

        RenderingManager(RenderingManager &&other) = delete;

        void render();

        // Width
        /**
         * @param value in screen coordinates
         *
         * @throws std::invalid_argument value must be greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        void setWidth(int value);

        /**
         * @return in screen coordinates
         */
        [[nodiscard]] int getWidth() const;

        // Height
        /**
         * @param value in screen coordinates
         *
         * @throws std::invalid_argument value must be greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        void setHeight(int value);

        /**
         * @return in screen coordinates
         */
        [[nodiscard]] int getHeight() const;

        // Background
        /**
         * The background color of the window.
         *
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        void setBackground(const Color &value);

        /**
         * @return the background color of the Window
         */
        [[nodiscard]] Color &getBackground();

        /**
         * @return the Camera object associated with the Window
         */
        [[nodiscard]] Camera &getCamera();

        /**
         * Converts coordinates in screen space to world space.
         * \n\n
         * (0, 0) is the upper-left of the window in screen space\n
         * (width, height) is the lower-right in screen space
         *
         * @param p a struct with (x, y) in screen coordinates
         * @return a struct with (x, y) in world coordinates
         */
        [[nodiscard]] Point toWorld(Point p) const;

        /**
         * Converts coordinates in world space to screen space.
         * \n\n
         * With the default camera projection, (0, 0) is the center in world space.
         *
         * @param p a struct with (x, y) in world coordinates
         * @return a struct with (x, y) in screen coordinates
         */
        [[nodiscard]] Point toScreen(Point p) const;

    protected:
        int m_Width;
        int m_Height;
        const char *m_Title;

        Color m_Background;

        void init();

        virtual void _updateSize() const = 0;

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

        void _updateBackground();

        static void _enableDepthWriting();

        static void _disableDepthWriting();

        uint32_t _drawRenderable(Renderable *object);

        void _undrawRenderable(Renderable *object);

        void _updateRenderable(Renderable *object);
    };
}
