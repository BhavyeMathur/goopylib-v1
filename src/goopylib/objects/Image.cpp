#define GP_LOGGING_LEVEL 7
#include "src/goopylib/debug/LogMacros.h"

#include "Image.h"
#include "src/goopylib/texture/Bitmap.h"
#include <stb/stb_image.h>


// Core Methods
namespace gp {
    Image::Image(std::string path, Point position)
            : TexturedRectangle(path, {-0.5, -0.5}, {0.5,  0.5}),
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
            : TexturedRectangle(path, {-0.5, -0.5}, {0.5,  0.5}),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}), {3}, {4})", path, position.x, position.y, width, height);

        scale(width, height);
        m_xScale = 1;
        m_yScale = 1;

        move(position.x, position.y);
    }

    Image::Image(std::string path, Point p1, Point p2)
            : TexturedRectangle(path, p1, p2),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}), ({3}, {4}))", path, p1.x, p1.y, p2.x, p2.y);
    }
}

// Getter & Setter Methods
namespace gp {
    std::string Image::getPath() const {
        GP_CORE_TRACE_ALL("gp::Image::getPath() - '{0}'", m_Path);
        return m_Path;
    }

    Ref<Bitmap> Image::getBitmap() const {
        GP_CORE_TRACE("gp::Image::getBitmap() - '{0}'", m_Path);
        return Ref<Bitmap>(new Bitmap(m_Path.c_str()));
    }
}

#undef GP_LOGGING_LEVEL
