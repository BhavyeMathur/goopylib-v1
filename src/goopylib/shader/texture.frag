R""(
#version 330 core

in vec4 Color;
in vec2 TexCoord;
flat in int TexSlot;

uniform sampler2D Texture[16];

out vec4 FragColor;

void main() {
    vec2 TextureSize = textureSize(Texture[TexSlot], 0);
    vec2 ScaledTexCoord = TexCoord / TextureSize;

    FragColor = Color * texture(Texture[TexSlot], ScaledTexCoord);
}
)"";
