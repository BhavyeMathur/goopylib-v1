#include "Glyph.h"

#include "src/config.h"
#include "src/goopylib/texture/Bitmap.h"

#if (GP_LOG_GLYPH != true) and (GP_LOG_GLYPH <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_GLYPH
#endif

#if !GP_VALUE_CHECK_GLYPH
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

//#include "src/goopylib/debug/LogMacros.h"
//#include "src/goopylib/debug/Error.h"

namespace gp {
    Glyph::Glyph(float xAdvance, float yAdvance, float xOffset, float yOffset, uint32_t code, const Ref<Bitmap> &bitmap)
            : xAdvance(xAdvance),
              yAdvance(yAdvance),
              xOffset(xOffset),
              yOffset(yOffset),
              width(bitmap->getWidth()),
              height(bitmap->getHeight()),
              codepoint(code),
              bitmap(bitmap) {

    }
}
