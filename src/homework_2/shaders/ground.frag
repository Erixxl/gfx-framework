#version 330


in float rand_value;


layout (location = 0) out vec4 out_color;


void main()
{
	vec3 high_color = vec3(19.0, 109.0, 21.0) / 255.0;
	vec3 low_color = vec3(65.0, 152.0, 10.0) / 255.0;

	vec3 frag_color = mix(high_color, low_color, rand_value);
	out_color = vec4(frag_color, 1.0);
}