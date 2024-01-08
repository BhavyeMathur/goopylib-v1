R""(
#version 330 core

in vec4 Color;
in vec2 TexCoord;
flat in int TexSlot;

uniform sampler2D Texture[16];

out vec4 FragColor;

void main() {
    FragColor = Color * texture(Texture[TexSlot], TexCoord);

    if ((FragColor.a) == 0) {
        discard;
    }
}
)"";
