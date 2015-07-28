#version 410

in vec2 position;
in vec2 texture;

uniform mat4 mat;

out vec2 uv;

void main() {
    gl_Position = mat * vec4(position, 0.0, 1.0);

    uv = texture;
}
