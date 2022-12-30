R""(
#version 410 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec4 color;

layout (std140) uniform Projection {
    mat4 ProjectionViewMatrix;
};

out vec4 Color;

void main() {
    gl_Position = ProjectionViewMatrix * vec4(point, 0.0f, 1.0f);
    Color = color;
}
)""
