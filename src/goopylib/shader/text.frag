R""(
#version 410 core

in vec4 Color;
in vec2 TexCoord;

uniform sampler2D Texture;

out vec4 FragColor;

void main() {
    FragColor = (Color.rgb, Color.a * texture2D(Texture, TexCoord).r);
}
)""
