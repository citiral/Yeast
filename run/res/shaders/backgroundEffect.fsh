#version 330 core

precision highp float;

in vec2 vertex;
in vec2 uv;

uniform sampler2D diffuse;
uniform sampler2D normal;

layout(location = 0) out vec4 frag_color;
layout(location = 1) out vec4 normal_color;
layout(location = 2) out vec4 info_color;


void main() {

	//we convert it to the proper gamma space
    frag_color = vec4(pow(texture(diffuse, uv), vec4(2.2)));
    normal_color = vec4(texture(normal, uv)) * frag_color.a;
    info_color = vec4(1);
}