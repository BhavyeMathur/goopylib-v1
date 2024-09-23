#pragma once

#include "gp.h"
#include "Renderer.h"
#include "window/Camera.h"
#include "color/Color.h"

#include "shader/ShaderFiles.h"

/*
 * The RenderingManager is responsible for a few things:
 *
 * 1. Managing shaders: initialising & compiling each shader & passing it to the Renderer
 *
 * 2. Managing the camera: including updating the Shader Uniform Projection-View matrix each render step. In addition,
 *      it also contains the utility methods toWorld() and toScreen() to convert between coordinate systems.
 *
 * 3. Managing the renderers: specifically, the RenderingManager holds 2 instances: m_Renderer & m_AlphaRenderer
 *      (which is used to renderer transparent objects). It is also responsible for selecting the correct Renderer to
 *      use and creating/destroying the object IDs. When the user draws, destroys, or updates an object, the
 *      RenderingManager is responsible for dispatching calls to the correct Renderer instance.
 *
 *  4. Window background color: including calls to glClearColor() and glClear() in the render loop.
 */

namespace gp {
    class Renderable;

    class GPAPI RenderingManager {
        friend class Renderer;

        friend class Renderable;

    public:
        RenderingManager(int width, int height, std::string title);

        RenderingManager(const RenderingManager &) = delete;

        RenderingManager(RenderingManager &&other) = delete;

        virtual ~RenderingManager() = default;

        void render();

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

        void draw(const shared_ptr<Renderable> &object);

        void destroy(const shared_ptr<Renderable> &object);

    protected:
        int m_Width;
        int m_Height;
        std::string m_Title;  // TODO move title out of RenderingManager

        Color m_Background;

        void init();

    private:
        Camera m_Camera;
        Renderer m_Renderer;
        Renderer m_AlphaRenderer;

        Shader m_SolidShader{solidVertexShader, solidFragmentShader};
        Shader m_EllipseShader{ellipseVertexShader, ellipseFragmentShader};
        Shader m_TextureShader{textureVertexShader, textureFragmentShader};

        shared_ptr<TextureAtlas> m_TextureAtlas;
        unique_ptr<UniformBuffer> m_ShaderUniform;

        uint32_t m_NextObjectID = -1;
        std::unordered_map<uint32_t, shared_ptr<Renderable>> m_IDtoObject;
        std::unordered_map<uint32_t, bool> m_ObjectToIsOpaque;

        void _updateRenderable(uint32_t ID);
    };
}
