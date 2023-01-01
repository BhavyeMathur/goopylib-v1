R""(
#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in int texSlot;
layout (location = 3) in float transparency;

layout (std140) uniform Projection {
    mat4 ProjectionViewMatrix;
};

out vec2 TexCoord;
flat out int TexSlot;
out float Transparency;

void main() {
    gl_Position = ProjectionViewMatrix * vec4(point, 0.0f, 1.0f);

    TexCoord = texCoord;
    TexSlot = texSlot;
    Transparency = transparency;
}
)""
