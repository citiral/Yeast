#version 330 core

precision highp float;

in vec2 vertex;
in vec2 uv;

uniform sampler2D diffuse;
uniform sampler2D normal;
uniform float brightness;
uniform float rotation;

layout(location = 0) out vec4 frag_color;
layout(location = 1) out vec4 normal_color;
layout(location = 2) out vec4 info_color;


void main() {
	mat2 rotation = mat2(cos(rotation), sin(rotation), -sin(rotation), cos(rotation));
	//we convert it to the proper gamma space
    frag_color = vec4(pow(texture(diffuse, uv), vec4(2.2)));

    //we rotate the normal
    vec2 flat_normal = texture(normal, uv).xy - vec2(0.5);
    flat_normal *= rotation;
    flat_normal += vec2(0.5);

    normal_color = vec4(flat_normal, texture(normal, uv).zw) * frag_color.a;
    info_color = vec4(brightness, 0, 0, 1) * frag_color.a;
}