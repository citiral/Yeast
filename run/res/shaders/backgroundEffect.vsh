#version 330 core

precision highp float;

layout (location = 0) in vec2 vertexAttribute;

uniform vec2 position;
uniform vec2 resolution;
uniform vec2 scale;
uniform vec2 size;
uniform float rotation;


out vec2 vertex;
out vec2 uv;

void main() {
	uv = vec2(vertexAttribute.x, 1 - vertexAttribute.y);
	uv *= resolution/size;

	vertex = vertexAttribute * 2 - vec2(1);
	//vertex = (vertexAttribute * (size * scale)) - resolution/2;
    
    gl_Position = vec4(vertex, 0., 1.0);
}