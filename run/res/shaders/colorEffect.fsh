#version 330 core

precision highp float;

in vec2 vertex;

uniform vec3 color;

layout(location = 0) out vec3 frag_color;
layout(location = 1) out vec3 normal_color;
layout(location = 2) out vec3 info_color;


void main() {
    frag_color = vec4(color, 1.0);
    normal_color = vec4(0.5, 0.5, 1);
    info_color = vec3(1);
}