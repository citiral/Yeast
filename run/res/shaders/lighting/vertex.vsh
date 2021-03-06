#version 330 core

precision highp float;

layout (location = 0) in vec2 vertexAttribute;

out vec2 vertex;
out vec2 uv;

void main() {
	uv = vertexAttribute;

	vertex = (vertexAttribute - vec2(0.5)) * 2;

	gl_Position = vec4(vertex, 0.0, 1.0);
}