#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec2 localCoord;
layout (location = 2) in vec3 color;
layout (location = 3) in float transparency;

out vec3 Color;
out vec2 LocalCoord;
out float Transparency;

void main() {
    gl_Position = vec4(point.x, point.y, 0.0f, 1.0f);
    Color = color;
    LocalCoord = localCoord;
    Transparency = transparency;
}
