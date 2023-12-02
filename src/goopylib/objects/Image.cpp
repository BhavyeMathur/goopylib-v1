#include "Image.h"
#include "src/goopylib/texture/Bitmap.h"
#include <stb/stb_image.h>

#include "src/config.h"

#if (GP_LOG_IMAGE != true) and (GP_LOG_IMAGE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_IMAGE
#endif

#if !GP_VALUE_CHECK_IMAGE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"


// Core Methods
namespace gp {
    Image::Image(const char *path, Point position)
            : TexturedRectangle(path, {-0.5, -0.5}, {0.5,  0.5}),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}))", path, position.x, position.y);

        int width, height;
        stbi_info(path, &width, &height, nullptr);

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

    Image::Image(const char *path, Point position, float width, float height)
            : TexturedRectangle(path, {-0.5, -0.5}, {0.5,  0.5}),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}), {3}, {4})", path, position.x, position.y, width, height);

        scale(width, height);
        m_xScale = 1;
        m_yScale = 1;

        move(position.x, position.y);
    }

    Image::Image(const char *path, Point p1, Point p2)
            : TexturedRectangle(path, p1, p2),
              m_Path(path) {
        GP_CORE_INFO("gp::Image::Image('{0}', ({1}, {2}), ({3}, {4}))", path, p1.x, p1.y, p2.x, p2.y);
    }
}

// Getter & Setter Methods
namespace gp {
    const char *Image::getPath() const {
        GP_CORE_TRACE_ALL("gp::Image::getPath() - '{0}'", m_Path);
        return m_Path;
    }

    Ref<Bitmap> Image::getBitmap() const {
        return Ref<Bitmap>(new Bitmap(m_Path));
    }
}
