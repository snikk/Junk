#version 410

in vec2 uv;

out vec4 colorOut;

uniform sampler2D sampler;

void main() {
    colorOut = texture(sampler, uv);
}

