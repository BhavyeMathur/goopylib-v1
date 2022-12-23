#version 330 core

in vec3 Color;
in float Transparency;

out vec4 FragColor;

void main() {
    FragColor = vec4(Color, Transparency);
}
