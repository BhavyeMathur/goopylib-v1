#include "Image.h"
#include <stb/stb_image.h>

#if (GP_LOG_IMAGE != true) and (GP_LOG_IMAGE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_IMAGE
#endif

#if !GP_VALUE_CHECK_IMAGE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"


// Core Methods
namespace gp {
    Image::Image(const char *path, Point position)
            : Renderable({0, 0},
                         {{-0.5, -0.5},
                          {0.5,  -0.5},
                          {0.5,  0.5},
                          {-0.5, 0.5}}),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}))", path, position.x, position.y);

        int width, height;
        stbi_info(path, &width, &height, nullptr);

        #if GP_ERROR_CHECKING
        if (width == 0 and height == 0) {
            GP_FILENOTFOUND_ERROR("File '{0}' not found", path);
        }
        #endif

        scale((float) width, (float) height);
        m_xScale = 1;
        m_yScale = 1;

        move(position.x, position.y);
    }

    Image::Image(const char *path, Point position, float width, float height)
            : Renderable({0, 0},
                         {{-0.5, -0.5},
                          {0.5,  -0.5},
                          {0.5,  0.5},
                          {-0.5, 0.5}}),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}), {3}, {4})", path, position.x, position.y, width, height);

        scale(width, height);
        m_xScale = 1;
        m_yScale = 1;

        move(position.x, position.y);
    }

    Image::Image(const char *path, Point p1, Point p2)
            : Renderable({{p1.x, p1.y},
                          {p2.x, p1.y},
                          {p2.x, p2.y},
                          {p1.x, p2.y}}),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}), ({3}, {4}))", path, p1.x, p1.y, p2.x, p2.y);
    }

    uint32_t Image::_draw(Window *window) const {
        GP_CORE_DEBUG("gp::Image::draw('{1}') - '{0}'", m_Path, window->m_Title);
        return window->m_Renderer.drawImage(const_cast<Image *>(this));
    }

    void Image::_destroy() const {
        GP_CORE_DEBUG("gp::Image::destroy() - '{0}'", m_Path);
        m_Window->m_Renderer.destroyImage(m_RendererID);
    }

    void Image::_update() const {
        GP_CORE_TRACE_ALL("gp::Image::update() - '{0}'", m_Path);
        m_Window->m_Renderer.updateImage(m_RendererID, this);
    }

    bool Image::_contains(float x, float y) const {
        GP_CORE_TRACE_ALL("gp::Image::destroy() - '{0}'", m_Path);
        return checkQuadContains({x, y}, m_Points[0], m_Points[1], m_Points[2], m_Points[3]);
    }
}

// Getter & Setter Methods
namespace gp {
    const char *Image::getPath() const {
        GP_CORE_TRACE_ALL("gp::Image::getPath() - '{0}'", m_Path);
        return m_Path;
    }

    void Image::setTransparency(float value) {
        GP_CORE_TRACE("gp::Image::setTransparency({1}) - '{0}'", value, m_Path);
        setTransparency(value, value, value, value);
    }

    void Image::setTransparency(float v1, float v2, float v3, float v4) {
        GP_CORE_TRACE("gp::Image::setTransparency({1}, {2}, {3}, {4}) - '{0}'", v1, v2, v3, v4, m_Path);

        m_V1.transparency = v1;
        m_V2.transparency = v2;
        m_V3.transparency = v3;
        m_V4.transparency = v4;

        update();
    }
}
