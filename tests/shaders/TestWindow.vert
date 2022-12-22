#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPos.x, aPos.y, 0.0f, 1.0f);
}
