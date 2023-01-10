R""(
#version 330 core

in vec2 TexCoord;
flat in int TexSlot;
in vec4 Color;

uniform sampler2D Texture[16];

out vec4 FragColor;

void main() {
    FragColor = Color * texture(Texture[TexSlot], TexCoord);
}
)"";
