#version 330 core
#define EPS 0.0000001
precision highp float;


in vec2 uv;

uniform sampler2D screen;
uniform vec2 size;

out vec4 frag_color;

void main() {
    // https://www.cs.utah.edu/~reinhard/cdrom/tonemap.pdf equation 4
    vec3 l = texture(screen, gl_FragCoord.xy / size).xyz;
    frag_color = vec4(log(l + EPS), 1);
}