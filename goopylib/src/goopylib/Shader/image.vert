#version 330 core

layout (location = 0) in vec2 point;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in int texSlot;

out vec2 TexCoord;
flat out int TexSlot;

void main() {
    gl_Position = vec4(point, 0.0f, 1.0f);
    TexCoord = texCoord;
    TexSlot = texSlot;
}
