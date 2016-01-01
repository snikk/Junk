#version 410

in vec2 position;
in vec3 color;

uniform mat4 mat;

out vec3 fragColor;

void main() {
    gl_Position = mat * vec4(position, 0.0, 1.0);
}
