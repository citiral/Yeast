#version 330 core

precision highp float;

uniform sampler2D screen;
uniform vec2 size;

out vec4 frag_color;

void main() {
    frag_color = vec4(pow(texture(screen, gl_FragCoord.xy / size).xyz, vec3(1.0)), 1);
}