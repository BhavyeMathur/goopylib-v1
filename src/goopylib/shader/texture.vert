R""(
#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in float z;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 texCoord;
layout (location = 4) in int texSlot;

layout (std140) uniform Projection {
    mat4 ProjectionViewMatrix;
};

out vec4 Color;
out vec2 TexCoord;
flat out int TexSlot;

void main() {
    vec4 position = ProjectionViewMatrix * vec4(point, 0.0f, 1.0f);
    gl_Position = vec4(position.xy, z, 1.0f);

    Color = color;
    TexCoord = texCoord;
    TexSlot = texSlot;
}
)"";
