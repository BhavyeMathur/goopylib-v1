#include "Image.h"

// Core Methods
namespace gp {
    Image::Image(Point position, const char *path)
            : Renderable({0, 0}, {{-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}}),
            m_Path(path) {
        GP_CORE_DEBUG("Initializing Image '{0}' at ({1}, {2})", path, position.x, position.y);

        int width, height;
        stbi_info(path, &width, &height, nullptr);

        m_Width = (float) width;
        m_Height = (float) height;

        scale((float) m_Width, (float) m_Height);
        m_xScale = 1;
        m_yScale = 1;

        move(position.x, position.y);
    }

    Image::Image(Point position, const char *path, float width, float height)
            : Renderable({0, 0}, {{-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}}),
            m_Path(path) {
        GP_CORE_DEBUG("Initializing Image '{0}' at ({1}, {2}), size=({3}, {4})",
                      path, position.x, position.y, width, height);

        scale(m_Width, m_Height);
        m_xScale = 1;
        m_yScale = 1;

        move(position.x, position.y);
    }

    Image::Image(Point p1, Point p2, const char *path)
            : Renderable({{p1.x, p1.y}, {p2.x, p1.y}, {p2.x, p2.y}, {p1.x, p2.y}}),
            m_Path(path) {
        GP_CORE_DEBUG("Initializing Image '{0}' from ({1}, {2}) to ({3}, {4})", path, p1.x, p1.y, p2.x, p2.y);
    }

    uint32_t Image::_draw(Window *window) const {
        return window->m_Renderer.drawImage(const_cast<Image *>(this));
    }

    void Image::_destroy() const {
        m_Window->m_Renderer.destroyImage(m_RendererID);
    }

    void Image::_update() const {
        m_Window->m_Renderer.updateImage(m_RendererID, this);
    }

    bool Image::_contains(float x, float y) const {
        return checkQuadContains({x, y}, m_Points[0], m_Points[1], m_Points[2], m_Points[3]);
    }
}

// Getter & Setter Methods
namespace gp {
    const char *Image::getPath() const {
        return m_Path;
    }

    void Image::setTransparency(float value) {
        setTransparency(value, value, value, value);
    }

    void Image::setTransparency(float v1, float v2, float v3, float v4) {
        m_V1.transparency = v1;
        m_V2.transparency = v2;
        m_V3.transparency = v3;
        m_V4.transparency = v4;

        update();
    }
}
