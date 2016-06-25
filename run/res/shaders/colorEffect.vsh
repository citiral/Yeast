#version 330 core

precision highp float;

layout (location = 0) in vec2 vertexAttribute;

uniform vec2 position;
uniform vec2 resolution;
uniform vec2 scale;
uniform vec2 size;
uniform float rotation;

out vec2 vertex;

void main() {
	vertex = (vertexAttribute * (size * scale) + position) - resolution/2;
    
    gl_Position = vec4(vertex / (resolution/2) , 0., 1.0);
}