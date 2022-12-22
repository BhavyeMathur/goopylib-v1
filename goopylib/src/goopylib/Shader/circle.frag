#version 330 core

in vec2 LocalCoord;
in vec3 Color;
out vec4 FragColor;

void main() {

    if (LocalCoord.x * LocalCoord.x + LocalCoord.y * LocalCoord.y > 1)
        discard;

    FragColor = vec4(Color, 1.0f);
}
