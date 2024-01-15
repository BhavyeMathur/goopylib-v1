#define GP_LOGGING_LEVEL 3

#include "Image.h"
#include "src/goopylib/texture/Bitmap.h"
#include <stb/stb_image.h>

#include <utility>


// Core Methods
namespace gp {
    Image::Image(std::string path, Point position)
            : Quad({-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}),
              TexturedRectangle(path),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}))", path, position.x, position.y);

        int width, height;
        stbi_info(path.c_str(), &width, &height, nullptr);

        #if GP_ERROR_CHECKING
        if (width == 0 and height == 0) {
            GP_FILENOTFOUND_ERROR("Image::Image() file '{0}' not found", path);
        }
        #endif

        scale((float) width, (float) height);
        m_xScale = 1;
        m_yScale = 1;

        move(position.x, position.y);
    }

    Image::Image(std::string path, Point position, float width, float height)
            : Quad({-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}),
              TexturedRectangle(path),
              m_Path(std::move(path)) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}), {3}, {4})", path, position.x, position.y, width, height);

        scale(width, height);
        m_xScale = 1;
        m_yScale = 1;

        move(position.x, position.y);
    }

    Image::Image(std::string path, Point p1, Point p2)
            : Quad(p1, {p2.x, p1.y}, p2, {p1.x, p2.y}),
              TexturedRectangle(path),
              m_Path(std::move(path)) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}), ({3}, {4}))", path, p1.x, p1.y, p2.x, p2.y);
    }

    std::string Image::toString() const {
        return strformat("Image('%s', (%g, %g))", m_Path.c_str(), m_Position.x, m_Position.y);
    }
}

// Getter & Setter Methods
namespace gp {
    std::string Image::getPath() const {
        GP_CORE_TRACE_ALL("gp::Image::getPath() - '{0}'", m_Path);
        return m_Path;
    }

    shared_ptr<Bitmap> Image::getBitmap() const {
        GP_CORE_TRACE("gp::Image::getBitmap() - '{0}'", m_Path);
        return shared_ptr<Bitmap>(new Bitmap(m_Path.c_str()));
    }
}
