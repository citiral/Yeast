#version 330 core

precision highp float;

layout (location = 0) in vec2 vertexAttribute;

uniform vec2 position;
uniform vec2 origin;
uniform vec2 resolution;
uniform vec2 scale;
uniform vec2 size;
uniform float rotation;


out vec2 vertex;
out vec2 uv;

void main() {
	mat2 rotation = mat2(cos(rotation), sin(rotation), -sin(rotation), cos(rotation));

	uv = vec2(vertexAttribute.x, 1 - vertexAttribute.y);
	
	vertex = ((vertexAttribute - (origin/size)) * (size * scale) * rotation + position) - resolution/2;
    
    gl_Position = vec4(vertex / (resolution/2) , 0., 1.0);
}