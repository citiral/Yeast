#version 330 core

precision highp float;

struct AmbientLight {
	vec3 color;
};

in vec2 uv;

uniform AmbientLight light;
uniform vec2 resolution;
uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D info;

out vec4 frag_color;

void main() {
    frag_color = vec4(texture(diffuse, uv).xyz * light.color * texture(info, uv).x, 1);
}