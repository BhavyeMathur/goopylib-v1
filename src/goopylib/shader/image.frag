R""(
#version 330 core

in vec2 TexCoord;
flat in int TexSlot;
in float Transparency;

uniform sampler2D Texture[16];

out vec4 FragColor;

void main() {
    vec4 color = texture(Texture[TexSlot], TexCoord);
    FragColor = vec4(color.rgb, color.a * Transparency);
}
)""
