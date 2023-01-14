R""(
#version 330 core

in vec4 Color;
in vec2 TexCoord;
flat in int TexSlot;

uniform sampler2D Texture[16];

const float smoothing = 0.02f;

out vec4 FragColor;

void main() {
    vec2 TextureSize = textureSize(Texture[TexSlot], 0);
    vec2 ScaledTexCoord = TexCoord / TextureSize;

    FragColor = vec4(ScaledTexCoord, 0, 1);

    float glyph = texture(Texture[TexSlot], ScaledTexCoord).r;

    if (glyph < (0.5f - smoothing)) {
        discard;
    }

    FragColor = Color;
    if (glyph < 0.5f) {
        FragColor.a *= (1.0f / smoothing) * (glyph - 0.5f + smoothing);
    }
}
)"";
