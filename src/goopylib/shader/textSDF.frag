R""(
#version 330 core

in vec4 Color;
in vec2 TexCoord;
flat in int TexSlot;

uniform sampler2D Texture[16];

const float smoothing = 0.02f;

out vec4 FragColor;

void main() {
    float glyph = texture(Texture[TexSlot], TexCoord).r;

    if (glyph < (0.5f - smoothing)) {
        discard;
    }

    FragColor = Color;
    if (glyph < 0.5f) {
        FragColor.a *= (1.0f / smoothing) * (glyph - 0.5f + smoothing);
    }
}
)"";
