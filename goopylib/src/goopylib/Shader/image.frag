#version 330 core

in vec2 TexCoord;
flat in int TexIndex;

uniform sampler2D Texture[16];

out vec4 FragColor;

void main() {
    FragColor = texture(Texture[TexIndex], TexCoord);
}
