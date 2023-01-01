R""(
#version 330 core

in vec2 LocalCoord;
in vec4 Color;

out vec4 FragColor;

void main() {

    if (LocalCoord.x * LocalCoord.x + LocalCoord.y * LocalCoord.y > 1)
        discard;

    FragColor = Color;
}
)""
