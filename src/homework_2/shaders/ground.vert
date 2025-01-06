#version 330


layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec3 vert_normal;
layout (location = 2) in vec2 text_coord;
layout (location = 3) in vec3 vert_color;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


out vec3 frag_color;


float random(in vec2 st)
{
	return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}


void main()
{
	vec2 seed = vec2(0.1337, -0.813);
	vec4 new_pos = vec4(vert_position.x, random(seed) * 10, vert_position.z, 1.0);

	frag_color = vert_color;
	gl_Position = Projection * View * Model * new_pos;
}