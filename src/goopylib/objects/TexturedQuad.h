#pragma once

#include "Quad.h"


namespace gp {
    class Bitmap;

    /**
     * An object representing a textured quad with 4 vertices.
     */
    class TexturedQuad : public Quad {

        friend class Renderer;

    public:
        /**
         * An object representing a textured quad with 4 vertices.
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         * @param p3 3rd coordinate (x, y) in world space
         * @param p4 4th coordinate (x, y) in world space
         */
        GPAPI TexturedQuad(const char* texture, Point p1, Point p2, Point p3, Point p4);

        /**
         * An object representing a textured quad with 4 vertices.
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         * @param p3 3rd coordinate (x, y) in world space
         * @param p4 4th coordinate (x, y) in world space
         */
        GPAPI TexturedQuad(const char* texture, const Ref<Bitmap>& bitmap, Point p1, Point p2, Point p3, Point p4);

        GPAPI const char* getTextureName() const;

        GPAPI void setBitmap(const Ref<Bitmap>& bitmap);

        GPAPI virtual Bitmap getBitmap() const;

    protected:
        GPAPI void _update() const override;

    private:
        TextureVertexAttrib m_T1 = {{-1, -1}};
        TextureVertexAttrib m_T2 = {{-1, -1}};
        TextureVertexAttrib m_T3 = {{-1, -1}};
        TextureVertexAttrib m_T4 = {{-1, -1}};

        const char *m_Texture;
        Ref<Bitmap> m_Bitmap = nullptr;

        GPAPI uint32_t _draw(Window *window) const override;

        GPAPI void _destroy() const override;
    };
}
