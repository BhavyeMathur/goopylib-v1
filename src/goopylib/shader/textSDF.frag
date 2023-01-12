R""(
#version 330 core

in vec4 Color;
in vec2 TexCoord;
flat in int TexSlot;

uniform sampler2D Texture[16];

const float threshold = 0.48f;
const float smoothing = 0.03f;

out vec4 FragColor;

void main() {
    float glyph = texture(Texture[TexSlot], TexCoord).r;

    if (glyph < threshold) {
        discard;
    }

    FragColor = Color;
    if (glyph < threshold + smoothing) {
        FragColor.a *= (1.0f / smoothing) * (glyph - threshold);
    }
}
)"";
