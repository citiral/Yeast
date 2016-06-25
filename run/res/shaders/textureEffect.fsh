#version 330 core

precision highp float;

in vec2 vertex;
in vec2 texture_coord;

uniform vec3 color;

uniform sampler2D image;

out vec4 frag_color;

void main() {
    frag_color = texture(image, texture_coord);
}