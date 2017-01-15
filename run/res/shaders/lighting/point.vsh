#version 330 core

precision highp float;

struct PointLight {
	vec3 color;
	vec2 position;
	float drop;
	float end;
	float depth;
};

uniform PointLight light;
uniform vec2 resolution;
uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D info;

layout (location = 0) in vec2 vertexAttribute;

out vec2 vertex;
out vec2 uv;

void main() {
	vertex = (vertexAttribute - vec2(0.5)) * 4 * light.end / resolution;
	vertex += light.position * 2 / resolution - vec2(1);

	uv = (vertex + vec2(1)) / 2;

	gl_Position = vec4(vertex, 0.0, 1.0);
}