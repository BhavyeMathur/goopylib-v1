#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec3 color;
layout (location = 2) in float transparency;

out vec3 Color;
out float Transparency;

void main() {
    gl_Position = vec4(point, 0.0f, 1.0f);
    Color = color;
    Transparency = transparency;
}
