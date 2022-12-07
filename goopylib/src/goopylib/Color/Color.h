#pragma once

namespace gp {
    struct RGB;

    class ColorRGB;

    class ColorHex;

    class ColorCMYK;

    class ColorHSV;

    class ColorHSL;
}


namespace gp {
    class Color {
    public:
        Color();

        Color(Color const &color);

        Color(ColorHSV const &color);

        Color(ColorHSL const &color);

        Color(const RGB &color, float alpha);

        ~Color() {
            GP_COLOR_TRACE("Deallocating Color");
        }

        Color(unsigned int red, unsigned int green, unsigned int blue);

        Color(unsigned int red, unsigned int green, unsigned int blue, float alpha);

        virtual std::string toString() const;

        unsigned int getRed() const;

        void setRed(unsigned int red);

        unsigned int getGreen() const;

        void setGreen(unsigned int red);

        unsigned int getBlue() const;

        void setBlue(unsigned int red);

        float getRedf() const;

        float getGreenf() const;

        float getBluef() const;

        float getAlpha() const;

        void setAlpha(float alpha);

    protected:
        unsigned int m_Red;
        unsigned int m_Green;
        unsigned int m_Blue;
        float m_Alpha;

        void fromRGB(unsigned int red, unsigned int green, unsigned blue, float alpha);

        void fromRGB(const RGB &color, float alpha);

        void fromColor(const Color &color);

    private:
        float m_Redf;
        float m_Greenf;
        float m_Bluef;
    };
}

namespace gp {
    class ColorRGB final : public Color {
    public:
        explicit ColorRGB(Color const &color);

        ColorRGB(unsigned int red, unsigned int green, unsigned int blue);

        ColorRGB(unsigned int red, unsigned int green, unsigned int blue, float alpha);

        ~ColorRGB() {
            GP_COLOR_TRACE("Deallocating ColorRGB");
        }

    protected:

    private:

    };
}

namespace gp {
    class ColorHex final : public Color {
    public:
        explicit ColorHex(Color const &color);

        explicit ColorHex(const char *hexstring);

        ColorHex(const char *hexstring, float alpha);

        ~ColorHex() {
            GP_COLOR_TRACE("Deallocating ColorHex");
        }

        std::string toString() const override;

    protected:

    private:
        const char *m_String;
    };
}

namespace gp {
    class ColorCMYK final : public Color {
    public:
        explicit ColorCMYK(Color const &color);

        ColorCMYK(float cyan, float magenta, float yellow, float key);

        ColorCMYK(float cyan, float magenta, float yellow, float key, float alpha);

        ~ColorCMYK() {
            GP_COLOR_TRACE("Deallocating ColorCMYK");
        }

        std::string toString() const override;

        float getCyan() const;

        void setCyan(float value);

        float getMagenta() const;

        void setMagenta(float value);

        float getYellow() const;

        void setYellow(float value);

        float getKey() const;

        void setKey(float value);

    protected:

    private:
        float m_Cyan;
        float m_Magenta;
        float m_Yellow;
        float m_Key;
    };
}

namespace gp {
    class ColorHSV final : public Color {
    public:
        explicit ColorHSV(Color const &color);

        explicit ColorHSV(ColorHSL const &color);

        ColorHSV(unsigned int hue, float saturation, float value);

        ColorHSV(unsigned int hue, float saturation, float value, float alpha);

        ~ColorHSV() {
            GP_COLOR_TRACE("Deallocating ColorHSV");
        }

        std::string toString() const override;

        unsigned int getHue() const;

        void setHue(unsigned int value);

        float getSaturation() const;

        void setSaturation(float value);

        float getValue() const;

        void setValue(float value);

    protected:

    private:
        unsigned int m_Hue;
        float m_Saturation;
        float m_Value;
    };
}

namespace gp {
    class ColorHSL final : public Color {
    public:
        explicit ColorHSL(Color const &color);

        explicit ColorHSL(ColorHSV const &color);

        ColorHSL(unsigned int hue, float saturation, float luminance);

        ColorHSL(unsigned int hue, float saturation, float luminance, float alpha);

        ~ColorHSL() {
            GP_COLOR_TRACE("Deallocating ColorHSL");
        }

        std::string toString() const override;

        unsigned int getHue() const;

        void setHue(unsigned int value);

        float getSaturation() const;

        void setSaturation(float value);

        float getLuminance() const;

        void setLuminance(float value);

    protected:

    private:
        unsigned int m_Hue;
        float m_Saturation;
        float m_Luminance;
    };
}
