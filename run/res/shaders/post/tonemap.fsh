#version 330 core

precision highp float;

//in vec4 gl_FragCoord;

uniform sampler2D screen;
uniform sampler2D avg_buffer;
uniform sampler2D max_buffer;
uniform vec2 size;
uniform float lwhite;
uniform float a;

out vec4 frag_color;

void main() {
    // https://www.cs.utah.edu/~reinhard/cdrom/tonemap.pdf equation 4
    vec3 avg = textureLod(avg_buffer, vec2(0.5, 0.5), 10.0).rgb;
    float lavg = exp(0.299*avg.r + 0.587*avg.r + 0.114*avg.b);
    vec3 l = (a / lavg) * texture(screen, gl_FragCoord.xy / size).xyz;
    frag_color = vec4(l * (1 + (1 / (lwhite*lwhite))) / (1 + lwhite), 1);
}