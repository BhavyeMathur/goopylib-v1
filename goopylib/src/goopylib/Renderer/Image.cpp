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

        int width, height;
        stbi_info(path, &width, &height, nullptr);

        m_Width = (float) width;
        m_Height = (float) height;

        _scale((float) m_Width, (float) m_Height);
        _move(position.x, position.y);
    }

    Image::Image(Point position, const char *path, float width, float height)
            : RenderableObject(position),
            m_V1({{-0.5, -0.5}, {0, 0}, 0}),
            m_V2({{0.5, -0.5}, {1, 0}, 0}),
            m_V3({{0.5, 0.5}, {1, 1}, 0}),
            m_V4({{-0.5, 0.5}, {0, 1}, 0}),
            m_Path(path),
            m_Width(width),
            m_Height(height) {
        GP_CORE_DEBUG("Initializing Image '{0}' at ({1}, {2}), size=({3}, {4})",
                      path, position.x, position.y, width, height);

        _scale(m_Width, m_Height);
        _move(position.x, position.y);
    }

    Image::Image(Point p1, Point p2, const char *path)
            : RenderableObject({(p1.x + p2.x) / 2.0f,
                                (p1.y + p2.y) / 2.0f}),
            m_V1({{p1.x, p1.y}, {0, 0}, 0}),
            m_V2({{p2.x, p1.y}, {1, 0}, 0}),
            m_V3({{p2.x,  p2.y}, {1, 1}, 0}),
            m_V4({{p1.x, p2.y}, {0, 1}, 0}),
            m_Path(path),
            m_Width(abs(p2.x - p1.x)),
            m_Height(abs(p2.y - p1.y)) {
        GP_CORE_DEBUG("Initializing Image '{0}' from ({1}, {2}) to ({3}, {4})", path, p1.x, p1.y, p2.x, p2.y);
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

// Getter & Setter Methods
namespace gp {
    void Image::setWidth(float width) {
        scale(width / m_Width, 1);
        m_Width = width;
    }

    float Image::getWidth() const {
        return m_Width;
    }

    void Image::setHeight(float height) {
        scale(1, height / m_Height);
        m_Height = height;
    }

    float Image::getHeight() const {
        return m_Height;
    }

    void Image::setSize(float width, float height) {
        scale(width / m_Width, height / m_Height);
        m_Width = width;
        m_Height = height;
    }

    const char *Image::getPath() const {
        return m_Path;
    }
}
