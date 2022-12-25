#pragma once

#include "gp.h"

namespace gp {
    class Texture2D {

        friend class Renderer;

    public:
        ~Texture2D();

    private:
        int32_t m_Width = 0;
        int32_t m_Height = 0;
        int32_t m_Channels = 0;

        const char *m_Path;

        uint32_t m_RendererID = 0;

        Texture2D(const char *path);

        void bind(uint32_t slot) const;

        static void unbind() ;
    };
}
