#version 330 core

precision highp float;

struct PointLight {
	vec3 color;
	vec2 position;
	float drop;
	float end;
	float depth;
};

in vec2 vertex;
in vec2 uv;

uniform PointLight light;
uniform vec2 resolution;
uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D info;

out vec4 frag_color;

void main() {
	vec3 light_pos = vec3((light.position ), light.depth);
	vec3 light_dir = normalize(light_pos - vec3(uv * resolution, 0));
	vec3 pixel_to_light = light_pos - vec3(uv * resolution, 0);
	pixel_to_light.z = 0;

	vec3 normal_direction = normalize((texture(normal, uv).rgb - vec3(0.5)) * 2);

	//calculate the angle of incidense
	float angle = dot(normal_direction, light_dir);

	//and the attenuation (the light.size is an extremely raw approximation of the size of the light in pixels)
	float attenuation = 1.0  - smoothstep(light.drop, light.end, length(pixel_to_light));//1.0;// / (1.0 + falloff * pow(, 2));

	vec3 diffuse_lighting = texture(diffuse, uv).xyz * light.color * max(angle, 0) * attenuation * angle;

	//if the a of the diffuse (lit) is 0, we don't render, we leave that to the fullbright light
    frag_color = vec4(diffuse_lighting * texture(info, uv).x, texture(info, uv).x);
    //frag_color = vec4(1);
}