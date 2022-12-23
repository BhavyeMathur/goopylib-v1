#include "Image.h"

// Core Methods
namespace gp {
    Image::Image(Point position, const char *path)
            : RenderableObject(position),
            m_V1({{-0.5, -0.5}, {0, 0}, 0}),
            m_V2({{0.5, -0.5}, {1, 0}, 0}),
            m_V3({{0.5, 0.5}, {1, 1}, 0}),
            m_V4({{-0.5, 0.5}, {0, 1}, 0}),
            m_Path(path) {
        GP_CORE_DEBUG("Initializing Image '{0}' at ({1}, {2})", path, position.x, position.y);

        stbi_info(path, &m_Width, &m_Height, nullptr);

        // TODO remove temporary 0.001 scale after a camera system is created
        _scale(0.00109649f * (float) m_Width, 0.00109649f * (float) m_Height);
        _move(position.x, position.y);
    }

    void Image::resetCenter() {
        m_Position.x = (m_V1.point.x + m_V2.point.x + m_V3.point.x + m_V4.point.x) / 4.0f;
        m_Position.y = (m_V1.point.y + m_V2.point.y + m_V3.point.y + m_V4.point.y) / 4.0f;
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

    void Image::_move(float dx, float dy) {
        m_V1.point.x += dx;
        m_V1.point.y += dy;

        m_V2.point.x += dx;
        m_V2.point.y += dy;

        m_V3.point.x += dx;
        m_V3.point.y += dy;

        m_V4.point.x += dx;
        m_V4.point.y += dy;
    }

    void Image::_rotate(float sin, float cos) {
        m_V1.point = {m_V1.point.x * cos + m_V1.point.y * sin,
                      m_V1.point.y * cos - m_V1.point.x * sin};

        m_V2.point = {m_V2.point.x * cos + m_V2.point.y * sin,
                      m_V2.point.y * cos - m_V2.point.x * sin};

        m_V3.point = {m_V3.point.x * cos + m_V3.point.y * sin,
                      m_V3.point.y * cos - m_V3.point.x * sin};

        m_V4.point = {m_V4.point.x * cos + m_V4.point.y * sin,
                      m_V4.point.y * cos - m_V4.point.x * sin};
    }

    void Image::_scale(float xfactor, float yfactor) {
        m_V1.point.x *= xfactor;
        m_V1.point.y *= yfactor;

        m_V2.point.x *= xfactor;
        m_V2.point.y *= yfactor;

        m_V3.point.x *= xfactor;
        m_V3.point.y *= yfactor;

        m_V4.point.x *= xfactor;
        m_V4.point.y *= yfactor;
    }
}

// Getter Methods
namespace gp {
    int32_t Image::getWidth() const {
        return m_Width;
    }

    int32_t Image::getHeight() const {
        return m_Height;
    }

    const char *Image::getPath() const {
        return m_Path;
    }
}
