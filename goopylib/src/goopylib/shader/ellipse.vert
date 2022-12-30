R""(
#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec2 localCoord;
layout (location = 2) in vec4 color;

layout (std140) uniform Projection {
    mat4 ProjectionViewMatrix;
};

out vec4 Color;
out vec2 LocalCoord;

void main() {
    gl_Position = ProjectionViewMatrix * vec4(point.x, point.y, 0.0f, 1.0f);
    Color = color;
    LocalCoord = localCoord;
}
)""
