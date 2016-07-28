#version 330 core
#define EPS 0.0000001
precision highp float;

in vec2 uv;

uniform sampler2D screen;
uniform vec2 size;
uniform int mipmap;

out vec4 frag_color;

void main() {
    vec3 c =   texelFetch(screen, 2*ivec2(uv) + ivec2(0, 0), mipmap).xyz;
    c = max(c, texelFetch(screen, 2*ivec2(uv) + ivec2(1, 0), mipmap).xyz);
    c = max(c, texelFetch(screen, 2*ivec2(uv) + ivec2(0, 1), mipmap).xyz);
    c = max(c, texelFetch(screen, 2*ivec2(uv) + ivec2(1, 1), mipmap).xyz);

    frag_color = vec4(c, 1);
}